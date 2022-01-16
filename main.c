#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define STR_LEN 30

typedef struct {
    char firstName[11];
    char surname[15];
    char dob[11];
    char vacDate[11];
    char vacVendor[21];
    enum Vendor {
        Astra_Zeneca = 1, Pfizer, Janssen, Moderna, Unvaccinated
    } vaccine;
    bool isVaccinated;
    char underCondition[21];
    char id[11];
} Record;

typedef struct {
    unsigned long n;
    void *record;
} arrSize;

Record tempRecord;

const char *printVendor(enum Vendor);

void displayMenu();

void viewAllRecords(Record *, int);

void addRecord(Record *);

void editRecord(Record *, int);

void editStudentNum(int num);

void percentNonVac(Record *, int);

Record *loadData(int *);

void sortVacByName(Record *recordArray, int recordCount);

void swapStructs(Record *, Record *);

void sortNonVacByName(Record *recordArray, int recordCount);

void sortVacByDate(Record *recordArray, int recordCount);

void viewSeniorHealthCond(Record *, int);

bool dateIsInOrder(char *, char *);

void writeToFile(Record *, int);

void bubbleSort(char [][STR_LEN], size_t);

void swapStrings(char *, char *);

bool isInOrder(char *a, char *b);

void swapChars(char *, char *);

void reformatDate(char *);

void removeSpecial(char *, int);

int calculateAge(char *);

int main() {
    int menuItem;
    int recordCount = 0;

    Record *recordArray = loadData(&recordCount);
    printf("Read: %d records\n", recordCount);
/*
    // printf("New date: %ld\n", removeSpecial(recordArray[0].firstName));

    // printf("\tThe first character of my surname is: %c\n", recordArray[0].surname[0]);
    //  printf("\tThe first number in my date of birth is: %c\n", recordArray[0].dob[0]);

     if (recordArray[0].surname[0] > recordArray[1].surname[0]) {
        printf("True.\n");
    }
    else {
        printf("False.\n");
    }


    // The below function is working to an extent - It is at least targeting the correct elements
    // swap function is not quite correct.
    // Once this is done, it should be easy to do ALL the bubble sort algorithms.
    // The function is still breaking when run, but seems to be closer than before.

    for (int pass = 1; pass < recordCount; pass++) {
        // printf("Pass: %d", pass);
        for (int rows = 0; rows < recordCount; rows++) {
            // printf("Row: %d", rows);
            for (int string = 0; string < sizeof(recordArray->surname); string++) {
                // printf("Comparing: %s with %s", &recordArray[rows].surname[string], &recordArray[rows + 1].surname[string]);
                if (recordArray[rows].surname[string] > recordArray[rows + 1].surname[string]) {
                    /*
                       // Swapping individual characters
                       char hold;
                       hold = recordArray[rows + 1].surname[string];
                       recordArray[rows + 1].surname[string] = recordArray[rows].surname[string];
                       recordArray[rows].surname[string] = hold;

                    // Swapping strings - I think this is the way to do it. Find out more!!
                    char holdString[15];
                    strcpy(holdString, recordArray[rows + 1].surname);
                    strcpy(recordArray[rows + 1].surname, recordArray[rows].surname);
                    strcpy(recordArray[rows + 1].surname, holdString);
                    // printf("Swapped %c with %c.\n", recordArray[rows].surname[string], recordArray[rows + 1].surname[string]);
                }
            }
        }
    }
    for (int i = 0; i < recordCount; i++) {
        printf("%s %s %s %s %s %s %s\n", recordArray[i].firstName, recordArray[i].surname, recordArray[i].dob,
               printVendor(recordArray[i].vaccine), recordArray[i].vacDate, recordArray[i].underCondition,
               recordArray[i].id);
    }

*/
    do {
        displayMenu();
        menuItem = 0;
        while (menuItem < 1 || menuItem > 9) {
            printf("Choose an option from 1 - 9\n");
            scanf("%d", &menuItem);
        }
        switch (menuItem) {
            case 1:
                addRecord(recordArray);
                break;
            case 2:
                viewAllRecords(recordArray, recordCount);
                break;
            case 3:
                editRecord(recordArray, recordCount);
                break;
            case 4:
                sortVacByName(recordArray, recordCount);
                break;
            case 5:
                sortNonVacByName(recordArray, recordCount);
                break;
            case 6:
                sortVacByDate(recordArray, recordCount);
                break;
            case 7:
                percentNonVac(recordArray, recordCount);
                break;
            case 8:
                viewSeniorHealthCond(recordArray, recordCount);
                break;
            case 9:
                writeToFile(recordArray, recordCount);
                printf("Goodbye!\n");
                menuItem = 10;
                break;
            default:
                break;
        }
    } while (menuItem != 10);

    // free(recordArray);

    return 0;
}

Record *loadData(int *countAddress) {
    FILE *fPtr = fopen("records.txt", "r");

    if (fPtr != NULL) {
        printf("File opened successfully.\n");
    } else {
        fPtr = fopen("records.txt", "w");
        if (fPtr != NULL) {
            printf("New file created successfully.\n");
        } else {
            printf("Unable to create file.\n");
        }
    }

    char buffer[200];
    fgets(buffer, 200, fPtr);

    int i = 0;
    Record *recordArray = (Record *) malloc(sizeof(*recordArray));
    // recordArray = (Record *)malloc(sizeof(Record) * (i + 1));
    while (!feof(fPtr)) {
        Record *record = recordArray + i;
        sscanf(buffer, "%s%s%s%s%s%s%s", record->firstName, record->surname, record->dob, record->vacVendor,
               record->vacDate, record->underCondition, record->id);
        if (strcmp("(none)", recordArray[i].vacDate) == false) {
            record->isVaccinated = false;
        } else {
            record->isVaccinated = true;
        }
        i++;
        fgets(buffer, 200, fPtr);
    }

    *countAddress = i;
    fclose(fPtr);
    return recordArray;
    // viewAllRecords(recordArray, i);
}

void viewAllRecords(Record *recordArray, int recordCount) {
    // Display array in record format
    printf("%10s%14s%14s%20s%20s%25s%22s%10s\n", "First name", "Surname", "D.O.B", "Vaccine vendor",
           "Vaccination date", "Underlying condition", "Student/Staff ID", "Is vaccinated?");
    for (int i = 0; i < recordCount; i++) {
        char *isVaccinated = " ";
        if (recordArray[i].isVaccinated) {
            isVaccinated = "*";
        }
        printf("%10s%14s%14s%20s%20s%25s%22s%10s\n", recordArray[i].firstName, recordArray[i].surname,
               recordArray[i].dob,
               recordArray[i].vacVendor, recordArray[i].vacDate, recordArray[i].underCondition, recordArray[i].id,
               isVaccinated);
    }
}


void addRecord(Record *recordArray) {
    // Add new record accepts all inputs but doesn't store to array.
    Record *rPtr = realloc(&rPtr, 2 * sizeof(Record));
    // Record *record = recordArray + i;
    printf("Enter first name:\n");
    scanf("%s", rPtr->firstName);

    printf("Enter surname:\n");
    scanf("%s", rPtr->surname);

    printf("Enter date of birth:\n");
    scanf("%s", rPtr->dob);

    printf("Select vendor of person's vaccine:\n");
    printf("\t1. Astra Zeneca\n");
    printf("\t2. Pfizer\n");
    printf("\t3. Janssen\n");
    printf("\t4. Moderna\n");
    printf("\t5. Unvaccinated\n");

    int menuItem;
    scanf("%d", &menuItem);
    // Program breaking at switch statement
    switch (menuItem) {
        case 1:
            rPtr->vaccine = Astra_Zeneca;
            break;
        case 2:
            rPtr->vaccine = Pfizer;
            break;
        case 3:
            rPtr->vaccine = Janssen;
            break;
        case 4:
            rPtr->vaccine = Moderna;
            break;
        case 5:
            rPtr->vaccine = Unvaccinated;
        default:
            break;
    }
    if (rPtr->vaccine != Unvaccinated) {
        printf("Enter date of vaccination:\n");
        scanf("%s", rPtr->vacDate);
    }
    printf("Enter underlying health conditions:\n");
    scanf("%s", rPtr->underCondition);
    printf("Enter student/staff ID:\n");
    scanf("%s", rPtr->id);

    for (int i = 0; i < 1; i++) {
        printf("%10s%14s%14s%20s%20s%25s%22s\n", rPtr->firstName, rPtr->surname, rPtr->dob,
               rPtr->vacVendor, rPtr->vacDate, rPtr->underCondition, rPtr->id);
    }
}


void editRecord(Record *recordArray, int recordCount) {
    int count = 0, toEdit;

    FILE *fPtr = fopen("records.txt", "r");

    do {
        fscanf(fPtr, "%s%s%s%s%s%s%s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
               tempRecord.vacVendor, tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);
        if (!feof(fPtr)) {
            count++;
        }
    } while (!feof(fPtr));

    fclose(fPtr);

    if (count > 0) {
        toEdit = 0;
        while (toEdit < 1 || toEdit > count) {
            printf("Student no. to edit? Enter number between 1 and %d:\n", count);
            scanf("%d", &toEdit);
        }
        editStudentNum(toEdit);
    } else {
        printf("Nothing to edit.\n");
    }
    fclose(fPtr);
}

void editStudentNum(int num) {
    int i, fileEnd;
    char tempString[50];

    FILE *fPtr = fopen("records.txt", "r");
    FILE *fPtr2 = fopen("temp.txt", "w");

    for (i = 1; i < num; i++) {
        fscanf(fPtr, "%s%s%s%s%s%s%s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
               tempRecord.vacVendor, tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);
        fprintf(fPtr2, "\n%s %s %s %s %s %s %s\n",
                tempRecord.firstName, tempRecord.surname, tempRecord.dob, printVendor(tempRecord.vaccine),
                tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);
    }

    fscanf(fPtr, "%s%s%s%s%s%s%s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
           tempRecord.vacVendor, tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);

    printf("\nCurrent details in record %d:\n", num);
    printf("%10s%14s%14s%20s%20s%25s%22s", "First name", "Surname", "D.O.B", "Vaccine vendor",
           "Vaccination date", "Underlying condition", "Student/Staff ID");
    printf("\n%10s%14s%14s%20s%20s%25s%22s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
           tempRecord.vacVendor, tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);

    // Create menu and switch statement to improve usability of this section
    printf("\n\n** Press enter if you do not wish to edit selected data. **\n");
    printf("\t\nFirst name: \n");
    gets(tempString);
    gets(tempString);
    if (strlen(tempString) > 0) {
        strcpy(tempRecord.firstName, tempString);
    }
    printf("\tSurname: \n");
    gets(tempString);
    if (strlen(tempString) > 0) {
        strcpy(tempRecord.surname, tempString);
    }

    printf("\tD.O.B: \n");
    gets(tempString);
    if (strlen(tempString) > 0) {
        strcpy(tempRecord.dob, tempString);
    }

    printf("\tVaccine vendor:\n");
    gets(tempString);
    if (strlen(tempString) > 0) {
        strcpy(tempRecord.vacVendor, tempString);
    }

    printf("\tVaccination Date: \n");
    gets(tempString);
    if (strlen(tempString) > 0) {
        strcpy(tempRecord.vacDate, tempString);
    }

    printf("\tUnderlying condition: \n");
    gets(tempString);
    if (strlen(tempString) > 0) {
        strcpy(tempRecord.underCondition, tempString);
    }

    printf("\tStudent/Staff ID: \n");
    gets(tempString);
    if (strlen(tempString) > 0) {
        strcpy(tempRecord.id, tempString);
    }

    fprintf(fPtr2, "\n%s %s %s %s %s %s %s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
            printVendor(tempRecord.vaccine), tempRecord.vacDate, tempRecord.underCondition,
            tempRecord.id);
    do {
        fileEnd = fscanf(fPtr, "%s%s%s%s%s%s%s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
                         tempRecord.vacVendor, tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);
        if (fileEnd != EOF) {
            fprintf(fPtr2, "\n%s %s %s %s %s %s %s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
                    printVendor(tempRecord.vaccine), tempRecord.vacDate, tempRecord.underCondition,
                    tempRecord.id);
        }
    } while (fileEnd != EOF);

    fclose(fPtr);
    fclose(fPtr2);

    remove("records.txt");
    rename("temp.txt", "records.txt");
}

void displayMenu() {
    printf("\n1. Add a new person\n");
    printf("2. View vaccination status for all students and staff\n");
    printf("3. Modify existing record\n");
    printf("4. Sort vaccinated people by name\n");
    printf("5. Sort non-vaccinated people by name\n");
    printf("6. Sort vaccinated people by date\n");
    printf("7. Display percentage of non-vaccinated people\n");
    printf("8. Display a list of people with an underlying condition over the age of 65\n");
    printf("9. Exit and save to file\n");
}

void sortVacByName(Record *recordArray, int recordCount) {

    for (int pass = 0; pass < recordCount - 1; pass++) {
        for (int i = 0; i < recordCount - pass - 1; i++) {
            if (!isInOrder(recordArray[i].surname, recordArray[i + 1].surname)) {
                swapStructs(&recordArray[i], &recordArray[i + 1]);
            }
        }
    }
    for (int i = 0; i < recordCount; i++) {
        if (recordArray[i].isVaccinated) {
            printf("%10s%14s%14s%20s%20s%25s%22s%10i\n", recordArray[i].firstName, recordArray[i].surname,
                   recordArray[i].dob, recordArray[i].vacVendor, recordArray[i].vacDate, recordArray[i].underCondition,
                   recordArray[i].id, recordArray[i].isVaccinated);
        }
    }
}

void sortNonVacByName(Record *recordArray, int recordCount) {

    for (int pass = 0; pass < recordCount - 1; pass++) {
        for (int i = 0; i < recordCount - pass - 1; i++) {
            if (!isInOrder(recordArray[i].surname, recordArray[i + 1].surname)) {
                swapStructs(&recordArray[i], &recordArray[i + 1]);
            }
        }
    }
    for (int i = 0; i < recordCount; i++) {
        if (!recordArray[i].isVaccinated) {
            printf("%10s%14s%14s%20s%20s%25s%22s%10i\n", recordArray[i].firstName, recordArray[i].surname,
                   recordArray[i].dob, recordArray[i].vacVendor, recordArray[i].vacDate, recordArray[i].underCondition,
                   recordArray[i].id, recordArray[i].isVaccinated);
        }
    }
}

void sortVacByDate(Record *recordArray, int recordCount) {

    for (int pass = 0; pass < recordCount - 1; pass++) {
        for (int i = 0; i < recordCount - pass - 1; i++) {
            char a[11], b[11];
            strcpy(a, recordArray[i].dob);
            strcpy(b, recordArray[i + 1].dob);
            removeSpecial(a, sizeof(a));
            removeSpecial(b, sizeof(b));
            reformatDate(a);
            reformatDate(b);
            if (!dateIsInOrder(a, b)) {
                swapStructs(&recordArray[i], &recordArray[i + 1]);
            }
        }
    }

    for (int i = 0; i < recordCount; i++) {
        if (recordArray[i].isVaccinated) {
            printf("%10s%14s%14s%20s%20s%25s%22s%10i\n", recordArray[i].firstName, recordArray[i].surname,
                   recordArray[i].dob, recordArray[i].vacVendor, recordArray[i].vacDate, recordArray[i].underCondition,
                   recordArray[i].id, recordArray[i].isVaccinated);
        }
    }
}

bool isInOrder(char *a, char *b) {
    for (size_t j = 0; j < 15; j++) {
        if (a[j] < b[j]) {
            return true;
        }
        if (a[j] > b[j]) {
            return false;
        }
    }
    return true;
}

bool dateIsInOrder(char *a, char *b) {
    for (size_t j = 0; j < 8; j++) {
        if (a[j] < b[j]) {
            return true;
        }
        if (a[j] > b[j]) {
            return false;
        }
    }
    return true;
}

void removeSpecial(char *dob, int size) {
    for (size_t i = 0; i < size; i++) {
        if (ispunct((dob[i]))) {
            for (size_t j = i; j < size; j++) {
                dob[j] = dob[j + 1];
            }
            i--;
            size--;
        }
    }
}

void reformatDate(char *dob) {
    swapChars(&dob[0], &dob[6]);
    swapChars(&dob[1], &dob[7]);
    swapChars(&dob[2], &dob[4]);
    swapChars(&dob[3], &dob[5]);
    swapChars(&dob[0], &dob[2]);
    swapChars(&dob[1], &dob[3]);
}

void swapChars(char *elem1Ptr, char *elem2Ptr) {
    char hold;
    hold = *elem1Ptr;
    *elem1Ptr = *elem2Ptr;
    *elem2Ptr = hold;
}


void swapStructs(Record *structPtr1, Record *structPtr2) {
    swapStrings(structPtr1->firstName, structPtr2->firstName);
    swapStrings(structPtr1->surname, structPtr2->surname);
    swapStrings(structPtr1->dob, structPtr2->dob);
    swapStrings(structPtr1->vacVendor, structPtr2->vacVendor);
    swapStrings(structPtr1->vacDate, structPtr2->vacDate);
    swapStrings(structPtr1->underCondition, structPtr2->underCondition);
    swapStrings(structPtr1->id, structPtr2->id);
    bool hold = NULL;
    hold = structPtr1->isVaccinated;
    structPtr1->isVaccinated = structPtr2->isVaccinated;
    structPtr2->isVaccinated = hold;
}

void swapStrings(char *elemPtr1, char *elemPtr2) {
    char hold[30];
    strcpy(hold, elemPtr1);
    strcpy(elemPtr1, elemPtr2);
    strcpy(elemPtr2, hold);
}

const char *printVendor(enum Vendor vaccine) {
    switch (vaccine) {
        case Astra_Zeneca:
            return "Astra-Zeneca";
        case Pfizer:
            return "Pfizer";
        case Janssen:
            return "Janssen";
        case Moderna:
            return "Moderna";
        case Unvaccinated:
            return "Unvaccinated";
        default:
            break;
    }
}

void percentNonVac(Record *recordArray, int recordCount) {
    int noVax = 0;
    for (int i = 0; i < recordCount; i++) {
        if (!recordArray[i].isVaccinated) {
            noVax++;
        }
    }
    float percentNoVax = (float) noVax / (float) recordCount * 100;
    printf("\t\n** Percentage of unvaccinated people: %.2f%% **\n", percentNoVax);
}

void viewSeniorHealthCond(Record *recordArray, int recordCount) {
    printf("%10s%14s%14s%20s%20s%25s%22s\n", "First name", "Surname", "D.O.B", "Vaccine vendor",
           "Vaccination date", "Underlying condition", "Student/Staff ID");
    for (int i = 0; i < recordCount; i++) {
        if ((strcmp("None", recordArray[i].underCondition) != false) && (calculateAge(recordArray[i].dob) >= 65)) {
            printf("%10s%14s%14s%20s%20s%25s%22s\n", recordArray[i].firstName, recordArray[i].surname,
                   recordArray[i].dob,
                   recordArray[i].vacVendor, recordArray[i].vacDate, recordArray[i].underCondition, recordArray[i].id);
        }
    }
}

void writeToFile(Record *recordArray, int recordCount) {
    FILE *fPtr = fopen("records.txt", "w");

    for (int i = 0; i < recordCount; i++) {
        fprintf(fPtr, "%s %s %s %s %s %s %s\n", recordArray[i].firstName, recordArray[i].surname, recordArray[i].dob,
                recordArray[i].vacVendor, recordArray[i].vacDate, recordArray[i].underCondition, recordArray[i].id);
    }
    fclose(fPtr);
    printf("** Successfully wrote %d records to file. **\n", recordCount);
}

int calculateAge(char *dob) {
    time_t t;
    int currentYear, currentMonth, currentDay;
    struct tm *timeFormat;
    time(&t);
    timeFormat = localtime(&t);
    currentYear = timeFormat->tm_year + 1900;
    currentMonth = timeFormat->tm_mon + 1;
    currentDay = timeFormat->tm_mday;

    // printf("Current year: %d\n", currentYear);

    int birthDay, birthMonth, birthYear;
    sscanf(dob, "%2d/%2d/%4d", &birthDay, &birthMonth, &birthYear);
    int age = currentYear - birthYear;
    if (currentMonth < birthMonth) {
        age--;
    }
    if (currentMonth == birthMonth) {
        if (currentDay < birthDay) {
            age--;
        }
    }
    return age;
}

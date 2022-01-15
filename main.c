#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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
} Patient;

typedef struct {
    unsigned long n;
    void *record;
} arrSize;

Patient tempRecord;

const char *printVendor(enum Vendor);

void displayMenu();

void viewAllRecords();

void addRecord();

void editRecord();

void editStudentNum(int num);

void percentNonVac();

Patient *loadData(int *);

void sortVacByName();

void sortNonVacByName();

void sortVacByDate();

void viewSeniorHealthCond();

void writeToFile(Patient *, int);

void bubbleSort(char [][STR_LEN], size_t);

void swapStrings(char *, char *);

void swapChars(char *, char *);

void reformatDate(char *);

void removeSpecial(char *, size_t);

int main() {
    int menuItem;
    int recordCount = 0;

    Patient *recordArray = loadData(&recordCount);
    printf("Read: %d records\n", recordCount);

    do {
        displayMenu();
        menuItem = 0;
        while (menuItem < 1 || menuItem > 9) {
            printf("Choose an option from 1 - 9\n");
            scanf("%d", &menuItem);
        }
        switch (menuItem) {
            case 1:
                addRecord();
                break;
            case 2:
                viewAllRecords(recordArray, recordCount);
                break;
            case 3:
                editRecord();
                break;
            case 4:
                sortVacByName();
                break;
            case 5:
                printf("Sort non-vaccinated people by name\n");
                // sortNonVaxName();
            case 6:
                sortVacByDate();
                break;
            case 7:
                percentNonVac(recordArray, recordCount);
                break;
            case 8:
                viewSeniorHealthCond();
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

Patient *loadData(int *countAddress) {
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
    Patient *recordArray = (Patient *) malloc(sizeof(*recordArray));
    // recordArray = (Patient *)malloc(sizeof(Patient) * (i + 1));
    char str1[] = "(none)";
    while (!feof(fPtr)) {
        Patient *record = recordArray + i;
        sscanf(buffer, "%s%s%s%s%s%s%s", record->firstName, record->surname, record->dob, record->vacVendor,
               record->vacDate, record->underCondition, record->id);
        if (strcmp(str1, recordArray[i].vacDate) == false) {
            record->isVaccinated = false;
        }
        else {
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

void viewAllRecords(Patient *recordArray, int recordCount) {
    // Display array in record format
    printf("%10s%14s%14s%20s%20s%25s%22s%10s\n", "First name", "Surname", "D.O.B", "Vaccine vendor",
           "Vaccination date", "Underlying condition", "Student/Staff ID", "Is vaccinated?");
    for (int i = 0; i < recordCount; i++) {
        char* isVaccinated = " ";
        if (recordArray[i].isVaccinated) {
            isVaccinated = "*";
        }
        printf("%10s%14s%14s%20s%20s%25s%22s%10s\n", recordArray[i].firstName, recordArray[i].surname, recordArray[i].dob,
               recordArray[i].vacVendor, recordArray[i].vacDate, recordArray[i].underCondition, recordArray[i].id, isVaccinated);
    }
}


void addRecord(Patient *recordArray) {
    int count;
    printf("How many records would you like to add?\n");
    scanf("%d", &count);
    // Add new record accepts all inputs but doesn't store to array.
    // Have tried all the below and none have worked so far.
    // recordArray[i].firstName || record[i]->firstName || record->firstName || recordArray->firstName
    Patient *record = malloc(sizeof(Patient));
    for (int i = 0; i < count; i++) {
        // Patient *record = recordArray + i;
        printf("Enter first name:\n");
        scanf("%s", tempRecord.firstName);
        strcpy(record->firstName, tempRecord.firstName);
        printf("%s", record->firstName);
        printf("Enter surname:\n");
        scanf("%s", tempRecord.surname);
        strcpy(record->surname, tempRecord.surname);
        printf("%s", record->surname);
        printf("Enter date of birth:\n");
        scanf("%s", tempRecord.dob);
        strcpy(record->dob, tempRecord.dob);
        printf("%s", record->dob);
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
                record->vaccine = Astra_Zeneca;
                break;
            case 2:
                record->vaccine = Pfizer;
                break;
            case 3:
                record->vaccine = Janssen;
                break;
            case 4:
                record->vaccine = Moderna;
                break;
            case 5:
                record->vaccine = Unvaccinated;
            default:
                break;
        }
        if (record->vaccine != Unvaccinated) {
            printf("Enter date of vaccination:\n");
            scanf("%s", tempRecord.vacDate);
            strcpy(record->vacDate, tempRecord.vacDate);
        }
        printf("Enter underlying health conditions:\n");
        scanf("%s", tempRecord.underCondition);
        strcpy(record->underCondition, tempRecord.underCondition);
        printf("Enter student/staff ID:\n");
        scanf("%s", tempRecord.id);
        strcpy(record->id, tempRecord.id);
    }

    for (int i = 0; i < 1; i++) {
        printf("%10s%14s%14s%20s%20s%25s%22s\n", record->firstName, record->surname, record->dob,
               record->vacVendor, record->vacDate, record->underCondition, record->id);
    }
}

/*
if (record->vaccine != Unvaccinated) {
    fprintf(fPtr,
            "\n%s %s %s %s %s %s %s",
            record->firstName, record->surname, record->dob, printVendor(record->vaccine),
            record->vacDate, record->underCondition, record->id);
} else {
    fprintf(fPtr, "\n%s %s %s %s (none) %s %s",
            record->firstName, record->surname, record->dob, printVendor(record->vaccine),
            record->underCondition, record->id);
}
}
fclose(fPtr);
 */


void editRecord(Patient *recordArray) {
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

void sortVacByName() {
    FILE *fPtr = fopen("records.txt", "r");

    char buffer[200];
    fgets(buffer, 200, fPtr);

    int i = 0;
    // Patient* pArray = (Patient*)malloc(sizeof(*pArray));
    Patient *pArray = (Patient *) malloc(sizeof(Patient));

    while (!feof(fPtr)) {
        Patient *p = pArray + i;
        sscanf(buffer, "%s%s%s%s%s%s%s", p->firstName, p->surname, p->dob, p->vacVendor,
               p->vacDate, p->underCondition, p->id);
        fgets(buffer, 200, fPtr);
        i++;
    }


    for (int pass = 1; pass < 10; pass++) {
        for (size_t j = 0; j < 10 - pass; ++j) {
            for (size_t k = 0; k < 11; ++k) {
                if (&pArray[j].surname[k] < &pArray[j + 1].surname[k]) {
                    break;
                }
                if (&pArray[j].surname[k] > &pArray[j + 1].surname[k]) {
                    swapStrings(&pArray[j].surname[k], &pArray[j + 1].surname[k]);
                    break;
                }
            }
        }
    }
    int n = i;
    printf("%10s%14s%14s%20s%20s%25s%22s\n", "First name", "Surname", "D.O.B", "Vaccine vendor",
           "Vaccination date", "Underlying condition", "Student/Staff ID");
    for (i = 0; i < n; i++) {
        printf("%10s%14s%14s%20s%20s%25s%22s\n", pArray[i].firstName, pArray[i].surname, pArray[i].dob,
               printVendor(pArray[i].vaccine), pArray[i].vacDate, pArray[i].underCondition, pArray[i].id);
    }
}


// void sortNonVacByName();

void sortVacByDate() {
    FILE *fPtr = fopen("records.txt", "r");

    char buffer[200];
    fgets(buffer, 200, fPtr);

    int i = 0;
    // Patient* pArray = (Patient*)malloc(sizeof(*pArray));
    Patient *pArray = (Patient *) malloc(sizeof(Patient));

    while (!feof(fPtr)) {
        // Patient *p = pArray + i;
        Patient *p = &pArray[i];
        sscanf(buffer, "%s%s%s%s%s%s%s", p->firstName, p->surname, p->dob, p->vacVendor,
               p->vacDate, p->underCondition, p->id);
        fgets(buffer, 200, fPtr);
        i++;
    }

    fclose(fPtr);

    for (int j = 1; j < 17; j++) {
        removeSpecial(pArray[j].dob, 11);
        reformatDate(pArray[j].dob);
    }

    /*
    // For Loop is causing problems with the DOBs
    for (int pass = 1; pass < 10; pass++) {
        for (size_t j = 0; j < 10 - pass; ++j) {
            for (size_t k = 0; k < 11; ++k) {
                printf("\t\t\nComparing: %c and %c\n", pArray[j].dob[k], pArray[j + 1].dob[k]);
                if (pArray[j].dob[k] < pArray[j + 1].dob[k]) {
                    break;
                }
                if (pArray[j].dob[k] > pArray[j + 1].dob[k]) {
                    swapStrings(pArray[j].dob, pArray[j + 1].dob);
                    break;
                }
            }
        }
    }
     */
    int n = i;
    printf("%10s%14s%14s%20s%20s%25s%22s\n", "First name", "Surname", "D.O.B", "Vaccine vendor",
           "Vaccination date", "Underlying condition", "Student/Staff ID");
    for (i = 0; i < n; i++) {
        printf("%10s%14s%14s%20s%20s%25s%22s\n", pArray[i].firstName, pArray[i].surname, pArray[i].dob,
               printVendor(pArray[i].vaccine), pArray[i].vacDate, pArray[i].underCondition, pArray[i].id);
    }
}

void removeSpecial(char *pArray, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (ispunct(pArray[i])) {
            for (size_t j = i; j < size; j++) {
                pArray[j] = pArray[j + 1];
            }
            i--;
            size--;
        }
    }
}

void reformatDate(char *pArray) {
    swapChars(&pArray[0], &pArray[6]);
    swapChars(&pArray[1], &pArray[7]);
    swapChars(&pArray[2], &pArray[4]);
    swapChars(&pArray[3], &pArray[5]);
    swapChars(&pArray[0], &pArray[2]);
    swapChars(&pArray[1], &pArray[3]);
}

void swapChars(char *elem1Ptr, char *elem2Ptr) {
    char hold;
    hold = *elem1Ptr;
    *elem1Ptr = *elem2Ptr;
    *elem2Ptr = hold;
}

void swapStrings(char *elemPtr1, char *elemPtr2) {
    char hold[STR_LEN];
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

void percentNonVac(Patient *recordArray, int recordCount) {
    int noVax = 0;
    for (int i = 0; i < recordCount; i++) {
        if (!recordArray[i].isVaccinated) {
            noVax++;
        }
    }
    float percentNoVax = (float) noVax / (float) recordCount * 100;
    printf("\t\n** Percentage of unvaccinated people: %.2f%% **\n", percentNoVax);
}

void viewSeniorHealthCond() {
    int fileEnd = 0;

    FILE *fPtr = fopen("records.txt", "r");

    printf("%10s%14s%14s%20s%20s%25s%22s\n", "First name", "Surname", "D.O.B", "Vaccine vendor",
           "Vaccination date", "Underlying condition", "Student/Staff ID");

    while (fileEnd != EOF) {
        fileEnd = fscanf(fPtr, "%s%s%s%s%s%s%s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
                         tempRecord.vacVendor, tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);
        char str1[] = "None";
        if (strcmp(str1, tempRecord.underCondition) != false) {
            printf("%10s%14s%14s%20s%20s%25s%22s\n", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
                   tempRecord.vacVendor, tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);
        }
    }
}

void writeToFile(Patient *recordArray, int recordCount) {
    FILE *fPtr = fopen("records.txt", "w");

    for (int i = 0; i < recordCount; i++) {
        fprintf(fPtr, "%s %s %s %s %s %s %s\n", recordArray[i].firstName, recordArray[i].surname, recordArray[i].dob,
                recordArray[i].vacVendor, recordArray[i].vacDate, recordArray[i].underCondition, recordArray[i].id);
    }
    fclose(fPtr);
    printf("** Successfully wrote %d records to file. **\n", recordCount);
}

/*
How to allocate memory dynamically using malloc
  int *arr = (int *) malloc(count * sizeof(int));

  for (int i = 0; i < count; i++) {
      arr[i] = 1;
  }

  showAll(arr, count);
  free(arr);
*/
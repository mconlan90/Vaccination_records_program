#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ARRAY_SIZE = sizeof(Patient);

typedef struct {
    char firstName[11];
    char surname[11];
    char dob[11];
    char vacDate[11];
    char vacVendor[21];
    char underCondition[21];
    char id[11];
} Patient;

Patient tempRecord;

void displayMenu();

void viewAllRecords();

void addRecord();

void editRecord();

void editStudentNum(int num);

void loadData();

int main() {
    int menuItem;
    loadData();

    do {
        displayMenu();
        menuItem = 0;
        while (menuItem < 1 || menuItem > 9) {
            printf("Choose an option from 1 - 9\n");
            scanf("%d", &menuItem);
        }
        switch (menuItem) {
            case 1:
                // printf("Add new record:\n");
                addRecord();
                break;
            case 2:
                // printf("View all records\n");
                viewAllRecords();
                break;
            case 3:
                printf("Modify existing record\n");
                editRecord();
                break;
            case 4:
                printf("Sort vaccinated people by name\n");
                // sortVaxName();
                break;
            case 5:
                printf("Sort non-vaccinated people by name\n");
                // sortNonVaxName();
            case 6:
                printf("Sort vaccinated people by date\n");
                break;
                // sortVaxDate();
            case 7:
                printf("Display percentage of non-vaccinated people.\n");
                break;
                // displayPercentNonVax();
            case 8:
                printf("Display over 65s with health condition\n");
                break;
                // viewSeniorHealthCond();
            case 9:
                printf("Exit and save to file\n");
                // writeToFile();
                break;
            default:
                break;
        }
    } while (menuItem != 10);

    // free(pArray);

    return 0;
}

void viewAllRecords() {
    int fileEnd;
    FILE *fPtr = fopen("records.txt", "r");
    printf("%10s%10s%14s%20s%20s%25s%22s", "First name", "Surname", "D.O.B", "Vaccine vendor",
           "Vaccination date", "Underlying condition", "Student/Staff ID");
    do {
        fileEnd = fscanf(fPtr, "%s%s%s%s%s%s%s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
                         tempRecord.vacVendor,
                         tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);
        if (fileEnd != EOF) {
            printf("\n%10s%10s%14s%20s%20s%25s%22s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
                   tempRecord.vacVendor, tempRecord.vacDate, tempRecord.underCondition,
                   tempRecord.id);
        }
    } while (fileEnd != EOF);

    fclose(fPtr);
}

void addRecord() {
    int count;
    Patient *pArray = (Patient *) malloc(sizeof(Patient));
    printf("How many records would you like to add?\n");
    scanf("%d", &count);

    FILE *fPtr = fopen("records.txt", "a+");
    /*
    strcpy(tempRecord.firstName, "<First Name>");
    strcpy(tempRecord.surname, "<Surname>");
    strcpy(tempRecord.vacVendor, "<Vaccine Vendor>");
    strcpy(tempRecord.vacDate, "<Vaccination Date>");
    strcpy(tempRecord.dob, "<Date of Birth>");
    strcpy(tempRecord.underCondition, "<Underlying Condition>");
    strcpy(tempRecord.id, "<Staff/Student ID>");
    */
    for (int i = 0; i < count; i++) {
        Patient *record = pArray + i;
        printf("Enter first name:\n");
        scanf("%s", record->firstName);
        printf("Enter surname:\n");
        scanf("%s", record->surname);
        printf("Enter date of birth:\n");
        scanf("%s", record->dob);
        printf("Enter name of vaccine vendor:\n");
        scanf("%s", record->vacVendor);
        printf("Enter date of vaccination:\n");
        scanf("%s", record->vacDate);
        printf("Enter underlying health conditions:\n");
        scanf("%s", record->underCondition);
        printf("Enter student/staff ID:\n");
        scanf("%s", record->id);

        fprintf(fPtr, "\n%s %s %s %s %s %s %s",
                record->firstName, record->surname, record->dob, record->vacVendor,
                record->vacDate, record->underCondition, record->id);
    }
    fclose(fPtr);
}

void editRecord() {
    int count = 0, toEdit;

    FILE *fPtr = fopen("records.txt", "r");

    do {
        fscanf(fPtr, "%s%s%s%s%s%s%s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
               tempRecord.vacVendor,
               tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);
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
                tempRecord.firstName, tempRecord.surname, tempRecord.dob, tempRecord.vacVendor,
                tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);
    }

    fscanf(fPtr, "%s%s%s%s%s%s%s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
           tempRecord.vacVendor, tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);
    printf("\nCurrent details in record %d:\n", num);
    printf("%10s%10s%14s%20s%20s%25s%22s", "First name", "Surname", "D.O.B", "Vaccine vendor",
           "Vaccination date", "Underlying condition", "Student/Staff ID");

    printf("\n%10s%10s%14s%20s%20s%25s%22s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
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
    printf("\tVaccine Vendor: \n");
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
            tempRecord.vacVendor, tempRecord.vacDate, tempRecord.underCondition,
            tempRecord.id);
    do {
        fileEnd = fscanf(fPtr, "%s%s%s%s%s%s%s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
                         tempRecord.vacVendor,
                         tempRecord.vacDate, tempRecord.underCondition, tempRecord.id);
        if (fileEnd != EOF) {
            fprintf(fPtr2, "\n%s %s %s %s %s %s %s", tempRecord.firstName, tempRecord.surname, tempRecord.dob,
                    tempRecord.vacVendor, tempRecord.vacDate, tempRecord.underCondition,
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


void loadData() {
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
    // Patient* pArray = (Patient*)malloc(sizeof(*pArray));
    Patient *pArray = (Patient *) malloc(sizeof(Patient));

    while (!feof(fPtr)) {
        Patient *p = pArray + i;
        sscanf(buffer, "%s%s%s%s%s%s%s", p->firstName, p->surname, p->dob, p->vacVendor,
               p->vacDate, p->underCondition, p->id);
        fgets(buffer, 200, fPtr);
        i++;
    }

    /*
    int n = i;
    printf("%10s%10s%14s%20s%20s%25s%22s\n", "First name", "Surname", "D.O.B", "Vaccine vendor",
           "Vaccination date", "Underlying condition", "Student/Staff ID");
    for (i = 0; i < n; i++) {
        printf("%10s%10s%14s%20s%20s%25s%22s\n", pArray[i].firstName, pArray[i].surname, pArray[i].dob,
               pArray[i].vacVendor, pArray[i].vacDate, pArray[i].underCondition, pArray[i].id);
    }
     */
    fclose(fPtr);
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
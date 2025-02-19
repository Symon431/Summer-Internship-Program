#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct internship {
    char studentName[50];
    char studentSurname[50];
    int departmentCode;
    int semester;
    float score;
    char letterGrade[5];

};


struct internship *Load_InternshipDataTable(char *, int *);

void Display_InternshipDataTable(struct internship *, int);

int search(struct internship *internshipDataTable, int, char *, char *);

void statistics(struct internship *, int);

void menu();

void swap(struct internship *, struct internship *);

void Sort(struct internship *, int);

int main(int argc, char *argv[]) {

    int numStudents = 0;
    struct internship *InternshipDataTable;
    InternshipDataTable = Load_InternshipDataTable(argv[1], &numStudents);

    Display_InternshipDataTable(InternshipDataTable, numStudents);

    int operation, outputSearch;
    do {
    menu();
    scanf("%d", &operation);

    switch (operation) {
        case 1: {
            char fullName[100];
            char *searchName, *searchSurname;
            fflush(stdin);
            printf("Please enter the name of the student: ");
            gets(fullName);

//the name is taken as 1 string. This part is splitting it to name and surname, if 2 names were entered by the user
            searchName = strtok(fullName, " ");
            searchSurname = strtok(NULL, " ");

            outputSearch = search(InternshipDataTable, numStudents, searchName, searchSurname);

            if (outputSearch == -1)
                printf("This student is not in our records!\n");
            else {
                printf("name: %s\n", InternshipDataTable[outputSearch].studentName);
                printf("surname: %s\n", InternshipDataTable[outputSearch].studentSurname);
                printf("department: %d\n", InternshipDataTable[outputSearch].departmentCode);
                printf("semester: %d\n", InternshipDataTable[outputSearch].semester);
                printf("score: %.1f\n", InternshipDataTable[outputSearch].score);
                printf("grade: %s\n", InternshipDataTable[outputSearch].letterGrade);
            }
            break;
        }

        case 2: {
            Sort(InternshipDataTable, numStudents);
            break;
        }

        case 3: {
            statistics(InternshipDataTable, numStudents);
            break;
        }
        case 4:{
            printf(" Byee\n");
            break;
        }
        default:
            printf("Invalid option");
            menu();
            scanf("%d", &operation);
    }

}while(operation != 4);
    return 0;
}

struct internship *Load_InternshipDataTable(char *fileName, int *numStudents) {
    FILE *file;
    file = fopen(fileName, "r");

    while (file == NULL) {
        printf("The file does not exist. Please enter again: ");
        scanf("%s", fileName);
        file = fopen(fileName, "r");
    }
    printf("The students record file (%s) has been successfully loaded!\n", fileName);

    char header[100], countLines[100];
    int count = 0;

//    counting the number of lines in the file
    while (fgets(countLines, sizeof(countLines), file) != NULL)
        count++;

//    excluding the first line from the count
    count -= 1;

    printf("The count is: %d\n", count);

//    excluding the header from the total count
    rewind(file);
    fgets(header, sizeof(header), file);


    struct internship *internshipDataTable;
    internshipDataTable = (struct internship *) malloc(count * sizeof(struct internship));

    if (internshipDataTable == NULL) {
        printf("Error! Cannot allocate memory to the internshipDataTable.\n");
        exit(1);
    }


    int i = 0;
    while (fscanf(file, "%s %s %d %d %f", internshipDataTable[i].studentName,
                  internshipDataTable[i].studentSurname,
                  &internshipDataTable[i].departmentCode,
                  &internshipDataTable[i].semester,
                  &internshipDataTable[i].score) != EOF) {

        if (internshipDataTable[i].score >= 70)
            strcpy(internshipDataTable[i].letterGrade, "S");
        else
            strcpy(internshipDataTable[i].letterGrade, "U");
        i++;
    }

// update the number of students
    *numStudents = count;

fclose(file);
    return internshipDataTable;

}

void Display_InternshipDataTable(struct internship *internshipDataTable, int numStudents) {
    if (internshipDataTable == NULL || numStudents == 0) {
        printf("Sorry. Cannot display the InternshipDataTable since its empty.!\n");
    } else {
        printf(" %-20s %-20s %-20s %-20s %-20s %-20s\t\n", "name", "surname", "departmentCode", "semester", "score",
               "letterGrade");
        for (int i = 0; i < numStudents; ++i) {
            printf("%-20s %-20s %-20d %-20d %-20.1f %-20s\t", internshipDataTable[i].studentName,
                   internshipDataTable[i].studentSurname, internshipDataTable[i].departmentCode,
                   internshipDataTable[i].semester, internshipDataTable[i].score, internshipDataTable[i].letterGrade);
            printf("\n");
        }
    }
}

int search(struct internship *internshipDataTable, int size, char *Name, char *Surname) {
    for (int i = 0; i < size; i++) {
        if (!stricmp(Name, internshipDataTable[i].studentName) &&
            !stricmp(Surname, internshipDataTable[i].studentSurname)) {
            return i;
        } else if (Surname == NULL) {
            if (!stricmp(Name, internshipDataTable[i].studentName))
                return i;
        }
    }
        return -1;

    }

    void statistics(struct internship *internshipDataTable, int size) {

        int totalFail = 0, totalPass = 0;
        for (int i = 0; i < size; ++i) {
            if (!stricmp(internshipDataTable[i].letterGrade, "S"))
                totalPass++;
            else
                totalFail++;
        }
        int *pass, *fail;


        int numDepartments = 4;
        pass = (int *) calloc(numDepartments, sizeof(int));
        fail = (int *) calloc(numDepartments, sizeof(int));
        if (pass == NULL || fail == NULL) {
            printf("Error allocating memory for the pass or fail array.\n");
            exit(1);
        }

        for (int i = 0; i < size; ++i) {
            if (internshipDataTable[i].departmentCode == 355) {
                if (!stricmp(internshipDataTable[i].letterGrade, "S"))
                    pass[0] += 1;
                else
                    fail[0] += 1;
            }
            if (internshipDataTable[i].departmentCode == 356) {
                if (!stricmp(internshipDataTable[i].letterGrade, "S"))
                    pass[1]++;
                else
                    fail[1] += 1;
            }

            if (internshipDataTable[i].departmentCode == 365) {
                if (!stricmp(internshipDataTable[i].letterGrade, "S"))
                    pass[2] += 1;
                else
                    fail[2] += 1;
            }
            if (internshipDataTable[i].departmentCode == 384) {
                if (!stricmp(internshipDataTable[i].letterGrade, "S"))
                    pass[3] += 1;
                else
                    fail[3] += 1;
            }
        }

        printf("Overall: %d student(s) passed and %d student(s) failed!\n", totalPass, totalFail);
        printf("Department: 355, %d student(s) passed and %d student(s) failed!\n", pass[0], fail[0]);
        printf("Department: 356, %d student(s) passed and %d student(s) failed!\n", pass[1], fail[1]);
        printf("Department: 365, %d student(s) passed and %d student(s) failed!\n", pass[2], fail[2]);
        printf("Department: 384, %d student(s) passed and %d student(s) failed!\n", pass[3], fail[3]);
    }

    void menu() {
        printf(" \nWhat would you like to do?\n"
               "1 - search\n"
               "2 - sort\n"
               "3 - statistics\n"
               "4 - exit\n"
               "Enter your choice: ");
    }

//    the function is used in the sort function to swap the
    void swap(struct internship *a, struct internship *b) {
        struct internship temp = *a;
        *a = *b;
        *b = temp;
    }

    void Sort(struct internship arr[], int n) {

        int column;
        printf("Which column (1: score, 2: letter grade)?: ");
        scanf("%d", &column);

        while (column != 1 && column != 2) {
            printf("Invalid choice!\n");

            printf("Which column (1: score, 2: letter grade)?: ");
            scanf("%d", &column);

        }
//algorithm used is the bubble sort array.
//The first value in the arr[0] which is the first index is first compared the all the other 9 values.
//if the value is larger than another value in the array. The swap function is called and the values are swapped.
//After is done comparing the first value. It moves the second value and compares it with the other 8 values excluding the first one since it's already the smallest.
        if (column == 1) {
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (arr[i].score > arr[j].score) {
                        swap(&arr[i], &arr[j]);
                    }
                }
            }
            printf("\n");
            Display_InternshipDataTable(arr, n);

//It's basically the same as the algorithm as the one sort with value uses.
//The only difference is the comparison of the smallest and greatest.
//by using stricmp() we check if it returns a number greater than 0, and call the swap function since it will be greater, and they swap.
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (stricmp(arr[i].letterGrade, arr[j].letterGrade) > 0) {
                        swap(&arr[i], &arr[j]);
                    }
                }
            }
            printf("\n");
            Display_InternshipDataTable(arr, n);
        }
    }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASS_MARK 40

typedef struct {
    char name[100];
    int roll;
    float marks;
} Student;

Student *students = NULL;
int count = 0;

// Function Prototypes
void addStudent();
void displayStudents();
void modifyStudent();
void removeStudent();
void searchStudent();
void calculateAverage();
void sortStudents(int ascending);
void saveToFile();
void loadFromFile();

int main() {
    char userName[100];

    printf("=====================================\n");
    printf("  WELCOME TO STUDENT RECORD SYSTEM\n");
    printf("=====================================\n");

    printf("Enter your name: ");
    fgets(userName, sizeof(userName), stdin);
    userName[strcspn(userName, "\n")] = '\0';

    printf("Hello, %s! Let's manage student records.\n\n", userName);

    int choice;

    do {
        printf("\n====== MENU ======\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Modify Student\n");
        printf("4. Remove Student\n");
        printf("5. Search Student\n");
        printf("6. Calculate Average Marks\n");
        printf("7. Sort Students (Ascending)\n");
        printf("8. Sort Students (Descending)\n");
        printf("9. Save to File\n");
        printf("10. Load from File\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: modifyStudent(); break;
            case 4: removeStudent(); break;
            case 5: searchStudent(); break;
            case 6: calculateAverage(); break;
            case 7: sortStudents(1); break;
            case 8: sortStudents(0); break;
            case 9: saveToFile(); break;
            case 10: loadFromFile(); break;
            case 0: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while(choice != 0);

    free(students);
    return 0;
}

// Add Student
void addStudent() {
    students = realloc(students, (count + 1) * sizeof(Student));

    printf("Enter Name: ");
    getchar();
    fgets(students[count].name, 100, stdin);
    students[count].name[strcspn(students[count].name, "\n")] = '\0';

    printf("Enter Roll Number: ");
    scanf("%d", &students[count].roll);

    printf("Enter Marks: ");
    scanf("%f", &students[count].marks);

    if(students[count].marks >= PASS_MARK)
        printf("Status: PASS\n");
    else
        printf("Status: FAIL\n");

    count++;
}

// Display Students
void displayStudents() {
    if(count == 0) {
        printf("No records available.\n");
        return;
    }

    for(int i = 0; i < count; i++) {
        printf("\nStudent %d\n", i + 1);
        printf("Name: %s\n", students[i].name);
        printf("Roll: %d\n", students[i].roll);
        printf("Marks: %.2f\n", students[i].marks);
        printf("Status: %s\n",
               students[i].marks >= PASS_MARK ? "PASS" : "FAIL");
    }
}

// Modify Student
void modifyStudent() {
    int roll, found = 0;

    printf("Enter Roll Number to modify: ");
    scanf("%d", &roll);

    for(int i = 0; i < count; i++) {
        if(students[i].roll == roll) {
            printf("Enter New Marks: ");
            scanf("%f", &students[i].marks);
            found = 1;
            printf("Record Updated!\n");
            break;
        }
    }

    if(!found)
        printf("Student not found.\n");
}

// Remove Student
void removeStudent() {
    int roll, found = 0;

    printf("Enter Roll Number to remove: ");
    scanf("%d", &roll);

    for(int i = 0; i < count; i++) {
        if(students[i].roll == roll) {
            for(int j = i; j < count - 1; j++)
                students[j] = students[j + 1];

            count--;
            students = realloc(students, count * sizeof(Student));
            found = 1;
            printf("Record Removed!\n");
            break;
        }
    }

    if(!found)
        printf("Student not found.\n");
}

// Search Student
void searchStudent() {
    int roll, found = 0;

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    for(int i = 0; i < count; i++) {
        if(students[i].roll == roll) {
            printf("\nName: %s\n", students[i].name);
            printf("Marks: %.2f\n", students[i].marks);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Student not found.\n");
}

// Calculate Average
void calculateAverage() {
    if(count == 0) {
        printf("No records available.\n");
        return;
    }

    float total = 0;
    for(int i = 0; i < count; i++)
        total += students[i].marks;

    printf("Average Marks: %.2f\n", total / count);
}

// Sort Students
void sortStudents(int ascending) {
    for(int i = 0; i < count - 1; i++) {
        for(int j = i + 1; j < count; j++) {
            if((ascending && students[i].marks > students[j].marks) ||
               (!ascending && students[i].marks < students[j].marks)) {

                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("Students sorted successfully.\n");
}

// Save to File
void saveToFile() {
    FILE *file = fopen("students.txt", "w");

    if(file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for(int i = 0; i < count; i++) {
        fprintf(file, "%s %d %.2f\n",
                students[i].name,
                students[i].roll,
                students[i].marks);
    }

    fclose(file);
    printf("Records saved to file.\n");
}

// Load from File
void loadFromFile() {
    FILE *file = fopen("students.txt", "r");

    if(file == NULL) {
        printf("No file found.\n");
        return;
    }

    count = 0;
    free(students);
    students = NULL;

    Student temp;

    while(fscanf(file, "%s %d %f",
                 temp.name,
                 &temp.roll,
                 &temp.marks) == 3) {

        students = realloc(students, (count + 1) * sizeof(Student));
        students[count++] = temp;
    }

    fclose(file);
    printf("Records loaded from file.\n");
}
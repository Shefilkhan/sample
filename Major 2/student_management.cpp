/*
* FILE : student_management.c
* PROJECT : SENG1005 - Assignment Major #2
* PROGRAMMER : Shefilkhan Pathan
* FIRST VERSION : 2024-12-11
* DESCRIPTION :This assignment requires you to develop a C program that simulates a student management system,
* using pointers, strings, structures, and file I/O to manage and store student data.
*/
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for Student
typedef struct {
    char name[50]; //name of the student 
    int id;        //Student ID
    float grades[5];//Array of grades for 5 subjects 
    float average;//Average grade 
} Student;

// Function prototypes
void addStudent(Student* students, int* count);
void searchStudent(Student* students, int count);
void modifyGrades(Student* students, int count);
void saveToFile(Student* students, int count);
void loadFromFile(Student* students, int* count);
void calculateAverage(Student* student);
void sortStudents(Student* students, int count);
void displayStudents(Student* students, int count);

int main(void) {
    Student students[30]; //This array is to store upto 30 students 
    int count = 0;  //Variable to track the current number of students 
    int choice; //users menu choice 

    do {
        //This functions display options for user to choose an operation 
        printf("\nStudent Management System\n");
        printf("1. Add a new student\n");
        printf("2. Search for a student by name\n");
        printf("3. Modify a student's grades\n");
        printf("4. Display all students\n");
        printf("5. Save data to a file\n");
        printf("6. Load data from a file\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        //this functions switch statement to handle user's choice 
        switch (choice) {
        case 1:
            addStudent(students, &count);//add a new student 
            break;
        case 2:
            searchStudent(students, count);//search for a student by their name 
            break;
        case 3:
            modifyGrades(students, count);//modify grades for a student 
            break;
        case 4:
            sortStudents(students, count);//sort students by average grades 
            displayStudents(students, count);//display all students detail
            break;
        case 5:
            saveToFile(students, count);//save student data in file 
            break;
        case 6:
            loadFromFile(students, &count);//load student data from file 
            break;
        case 7:
            printf("Exiting the program. Goodbye!\n");//exit from ths message 
            break;
        default:
            printf("Invalid choice. Please try again.\n");//this is for  invalid option choice 
        }
    } while (choice != 7);//this function allows to repeat until users choose to exit 

    return 0;
}

// FUNCTION : addstudent
// DESCRIPTION : This function allow to add a new student to the file,
// including their name,ID,and grades for 5 subjects 
// PARAMETERS : Student* students : pointer to an array of Student structs
// int* count : pointer to the total number of students in the system
// RETURNS : No return value 
void addStudent(Student* students, int* count) {
    if (*count >= 30) {
        printf("Cannot add more students. Maximum capacity reached.\n");
        return;
    }

    printf("Enter student name: ");
    getchar(); // Clear newline
    fgets(students[*count].name, 50, stdin);
    students[*count].name[strcspn(students[*count].name, "\n")] = '\0'; // Remove newline

    printf("Enter student ID: ");
    scanf("%d", &students[*count].id);

    printf("Enter grades for 5 subjects: ");
    for (int i = 0; i < 5; i++) {
        scanf("%f", &students[*count].grades[i]);
    }

    calculateAverage(&students[*count]);
    (*count)++;

    printf("Student added successfully!\n");
}

// FUNCTION : searchstudent 
// DESCRIPTION : This function allow to search for a student by their name exist in file and 
// display their information if found
// PARAMETERS :// Student* students : pointer to an array of Student structs
// int count : total number of students in the system
// RETURNS : No return value 
void searchStudent(Student* students, int count) {
    char name[50];
    printf("Enter the name of the student to search: ");
    getchar(); // Clear newline
    fgets(name, 50, stdin);
    name[strlen(name)] = '\0'; // Remove newline

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Student found:\n");
            printf("Name: %s, ID: %d, Average: %.2f\n", students[i].name, students[i].id, students[i].average);
            return;
        }
    }

    printf("Student not found.\n");
}

// FUNCTION : modifygrades
// DESCRIPTION : This function allows to modify of a student's grades based on their details. 
// PARAMETERS : Student* students : pointer to an array of Student structs
// int count : total number of students in the system
// RETURNS : No return value 
void modifyGrades(Student* students, int count) {
    char name[50];
    printf("Enter the name of the student to modify grades: ");
    getchar(); // Clear newline
    fgets(name, 50, stdin);
    name[strlen(name)] = '\0'; // Remove newline

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Enter new grades for 5 subjects: ");
            for (int j = 0; j < 5; j++) {
                scanf("%f", &students[i].grades[j]);
            }

            calculateAverage(&students[i]);
            printf("Grades updated successfully!\n");
            return;
        }
    }

    printf("Student not found.\n");
}

// FUNCTION : calculateaverage 
// DESCRIPTION : This function allows to calculate average gardes for individual students based on thier grades in 5 different subjects.
// PARAMETERS : Student* student : pointer to a Student struct containing the student's grades
// RETURNS : No return value 
void calculateAverage(Student* student) {
    float sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += student->grades[i];
    }
    student->average = sum / 5;
}

// FUNCTION : sortstudents  
// DESCRIPTION : This function This function sorts the students by their average grade in descending order.
// It uses a simple sorting algorithm to arrange the students.
// PARAMETERS : Student* students : pointer to an array of Student structs
// int count : total number of students in the system
// RETURNS : No return value 
void sortStudents(Student* students, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (students[i].average < students[j].average) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

// FUNCTION : displaystudents 
// DESCRIPTION : This function allows to display a list of students, according to name, student ID, and grades. 
// PARAMETERS : Student* students : pointer to an array of Student structs
// int count : total number of students in the system
// RETURNS : No return value 
void displayStudents(Student* students, int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nStudents:\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s, ID: %d, Grades: ", students[i].name, students[i].id);
        for (int j = 0; j < 5; j++) {
            printf("%.2f ", students[i].grades[j]);
        }
        printf(", Average: %.2f\n", students[i].average);
    }
}

// FUNCTION : savetofiles  
// DESCRIPTION : This function saves the student data to a file called "input.txt" 
// PARAMETERS : Student* students : pointer to an array of Student structs
// int count : total number of students in the system
// RETURNS : No return value 
void saveToFile(Student* students, int count) {
    FILE* file = fopen("student.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%d,", students[i].name, students[i].id);
        for (int j = 0; j < 5; j++) {
            fprintf(file, "%.2f", students[i].grades[j]);
            if (j < 4) fprintf(file, ",");
        }
        fprintf(file, ",%.2f\n", students[i].average);
    }

    fclose(file);
    printf("Data saved successfully to student.txt\n");
}

// FUNCTION : loadfromfile 
// DESCRIPTION : This function loads student data from a file called "input.txt".
// PARAMETERS :Student* students : pointer to an array of Student structs
// int* count : pointer to the total number of students in the system
// RETURNS : No return value 
void loadFromFile(Student* students, int* count) {
    FILE* file = fopen("student.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    *count = 0;//reset the student count 
    while (fscanf(file, "%[^,],%d,", students[*count].name, &students[*count].id) == 2) {
        for (int i = 0; i < 5; i++) {
            fscanf(file, "%f,", &students[*count].grades[i]);
        }
        fscanf(file, "%f\n", &students[*count].average);
        (*count)++;//increment the cout of students 
    }

    fclose(file);//this function close file 
    printf("Data loaded successfully from students.txt\n");
}

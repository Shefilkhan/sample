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
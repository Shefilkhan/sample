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

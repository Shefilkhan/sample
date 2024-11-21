/*
* FILE : file_io_structs.cpp
* PROJECT : PROG1345 - Focused Assignment #6
* PROGRAMMER : Shefilkhan student
* FIRST VERSION : 2024-11-20
* DESCRIPTION :
* This program demonstrates file I/O operations in C. It reads student data from an input file,
* organizes, and computes averages for the data before writing the results to an output file.
* Structs are used by the application to manage student records effectively.
*/
#define _CRT_SECURE_NO_WARNINGS //this function is used to disable warnings about using "insecure" standard library functions


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
int readData(FILE* fp, struct Student* students, int maxStudents);
void calculateClassAverage(const struct Student* students, int count);
void sortRecords(struct Student* students, int count);
void filterRecords(const struct Student* students, int count, int threshold);
void writeDataToFile(const char* filepath, const struct Student* students, int count);

//These are Constants for program configuration
#define MAX_STUDENTS 30    // Maximum number of students
#define MAX_NAME_LENGTH 50    // Maximum length for student names
#define BUFFER_SIZE 100       // Buffer size for reading lines from files

// This is a struct to hold student information
struct Student {
    int id; // Holds Unique ID for a student
    char name[MAX_NAME_LENGTH];// Define name of the students 
    int grade;//define grade of the students 
};

int main(void) {
    FILE* inputFile;
    struct Student students[MAX_STUDENTS];//this function holds student records
    int studentCount = 0; //this function counts the number of students from the file
    int choice;//this is users choice
    int gradeThreshold = 85;//this holda the default limit for record filters

    // This function open the input .txt file in reading mode
    errno_t err = fopen_s(&inputFile, "input.txt", "r");
    if (err != 0) {
        perror("Error opening input file");//this function print erro if the file is not exist
        return 0;
    }

    // This function allow to read the student data from input file 
    studentCount = readData(inputFile, students, MAX_STUDENTS);
    fclose(inputFile);//this function close the input file after reading

    //Options system for usres operations 
    do {
        printf("\nMenu:\n");
        printf("1. Calculate Class Average\n");
        printf("2. Sort Records by Grade\n");
        printf("3. Filter Records by Grade Threshold\n");
        printf("4. Write Data to Output File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        //this function read users choice 
        if (scanf_s("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            choice = 0;//this function stops unexpected actions, reset the choice
            continue;
        }
               // this function performs operations beased on users input
        switch (choice) {
        case 1:
            calculateClassAverage(students, studentCount);
            break;
        case 2:
            sortRecords(students, studentCount);
            printf("Records sorted by grade.\n");
            break;
        case 3:
            printf("Enter grade threshold: ");
            if (scanf_s("%d", &gradeThreshold) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n'); // Clear input buffer
                continue;
            }
            filterRecords(students, studentCount, gradeThreshold);
            break;
        case 4:
            writeDataToFile("output.txt", students, studentCount);
            printf("Data written to output file.\n");
            break;
        case 5:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);// this function continues until the users select to exit 

    return EXIT_SUCCESS;
}
// this function reads data from an input data and displays an array of students records
int readData(FILE* fp, struct Student* students, int maxStudents) {
    char buffer[BUFFER_SIZE];//this function is for temporary buffer for reading files
    int i = 0;

    while (i < maxStudents && fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf_s(buffer, "%d", &students[i].id) != 1) break; //this function analyze students ID

        //this function read and store students name
        if (!fgets(buffer, sizeof(buffer), fp)) break;
        buffer[strcspn(buffer, "\n")] = '\0';  // this function removes newline character
        strncpy_s(students[i].name, sizeof(students[i].name), buffer, _TRUNCATE);

        // this function read and store students grade
        if (!fgets(buffer, sizeof(buffer), fp)) break;
        if (sscanf_s(buffer, "%d", &students[i].grade) != 1) break;

        i++;//this is increment for the record count 
    }
    return i;//this function returns the number of records read 
}
// this function calculates and display the class average
void calculateClassAverage(const struct Student* students, int count) {
    int sum = 0;//this function is collector for grades 
    for (int i = 0; i < count; i++) {
        sum += students[i].grade;
    }
    printf("Class Average: %.2f\n", count > 0 ? (float)sum / count : 0.0);
}

// this function is to sort records by grade in ascending order
void sortRecords(struct Student* students, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (students[i].grade > students[j].grade) {
                struct Student temp = students[i];//this is temporary variable for swapping
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

// this function is to filter and display records above a grade threshold
void filterRecords(const struct Student* students, int count, int threshold) {
    printf("Records with grades above %d:\n", threshold);
    for (int i = 0; i < count; i++) {
        if (students[i].grade > threshold) {
            printf("%d %s %d\n", students[i].id, students[i].name, students[i].grade);
        }
    }
}

// this function is to write students records for a specific output file
void writeDataToFile(const char* filepath, const struct Student* students, int count) {
    FILE* file;
    file = fopen("input.txt", "w");//this function opens file in the mentioned path
    if (file == NULL) {
        perror("Error opening file");//this function handle file error
        return;
    }

    //this function write each students details 
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %d\n", students[i].id, students[i].name, students[i].grade);
    }
    //this function close the file after writing 
    fclose(file);
    printf("Data successfully written to %s.\n", filepath);
}
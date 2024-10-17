/*
* FILE : string_operation.c
* PROJECT : SENG1005 - Focused Assignment #4
* PROGRAMMER : Shefilkhan Pathan
* FIRST VERSION : 2024-10-15
* DESCRIPTION : The program that prompts the user to input a string, processes the string
* to count the number of vowels, and then reverses the string before displaying it.
*/
#include <stdio.h> 
#include <string.h>  // Functions are provided by this header file for control settings

//
// FUNCTION : countVowels
// DESCRIPTION :
// This function counts vowels in the provided string
// PARAMETERS :
// int count: count the total number of vowels both uppercase and lowercase
//

int countVowels(char str[])  //to count the vowels in a string this function is used

{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        // checks whether the charactes is a vowel or not (lower or uppercase)
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' ||
            str[i] == 'o' || str[i] == 'u' ||
            str[i] == 'A' || str[i] == 'E' || str[i] == 'I' ||
            str[i] == 'O' || str[i] == 'U') {
            count++;
        }
    }
    return count;  // the total number of vowel is returned over here
}
//
// FUNCTION : reverse string
// DESCRIPTION :
// This function reverse the provided string
// PARAMETERS :
// int length: holds the length of string
// char temp: hold character of string for temporary period
//
void reverseString(char str[])  // a reverse string is held here 
{
    int length = strlen(str);  // this would hold the lenght of the string 
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i]; // the positions of the characters are switched at the beginning and at the end of the string 
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    } 
}

int main(void) {
    char input[100];  // the input string is stored in the array

    // Ask the user to enter a string
    printf("Enter a string (upto 99 characters): ");
    fgets(input, sizeof(input), stdin); // input is read including the spaces

    // if the new line exists the newline character is removed
    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

    // function is called to count the vowels and the result is printed
    int vowels = countVowels(input);
    printf("Number of vowels in the string: %d\n", vowels);

    // the string is reversed and the result is printed
    reverseString(input);
    printf("The reversed string is: %s\n", input);

    return 0;
}

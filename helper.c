#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#include "helper.h"


//Get text from file and return it
char * getTextFromFile(char* filename){
    FILE* f = fopen(filename, "rb");
    if(f == NULL){
        printf("Warning: File is busy. Exiting...");
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);
    rewind(f);
    char* text = malloc(fileSize + 1);
    fread(text, 1, fileSize, f);
    fclose(f);
    return (char*) text;
}


//Convert char array to bit array
int convertCharArrToBitArr(char* charArray, int* bitArray){
    for (int i = 0; i < 8; i++)
        bitArray[i] = charArray[i] - '0';
    return 0;
}


//Convert an integer to an array of chars
char* intToCharArray(int num){
    int copy = num;
    int len = 1;
    while (copy){
        len++;
        copy /= 10;
    }
    char* numInChar = malloc(len);
    for (int i = 0; i < len; i++){
        numInChar[len-2-i] = num % 10 + '0';
        num = num/10;
    }
    numInChar[len-1] = '\0';
    return (char*) numInChar;
}


//Convert an array of integers representing a binary number to a decimal number
int binaryToDecimal(int* bitArray){
    int sum = 0;
    for (int i = 7; i >= 0; i--)
        sum += bitArray[i] * pow(2, 7-i);
    return sum;    
}


//Convert a decimal number to an array of integers representing a binary number
int decimalToBinary(int decimal, int* bitArray){
    for (int i = 0; i < 8; i++){
        bitArray[7-i] = decimal % 2 + 48;
        decimal = decimal/2;
    }
    return 0;    
}
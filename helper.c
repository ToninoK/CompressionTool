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

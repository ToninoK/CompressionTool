#include<string.h>


//This function takes in a string and counts occurences of each character in the string
//This is done with an integer array where the position represents the ascii value of character
//and the value represents the number of occurences
int getOccurences(char* buffer, int* occurences){
    for(int i = 0; i < strlen(buffer); i++)
        occurences[(int)buffer[i]] += 1;
    return 0;
}

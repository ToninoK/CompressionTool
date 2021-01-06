#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "helper.h"
#include "huffman.h"

//Build Huffman tree from queue
Node buildHuffmanTree(QueueNode head){
    while(head->next != NULL && head->next->next !=NULL){
        Node element1 = peek(head);
        dequeue(head);
        Node element2 = peek(head);
        dequeue(head);

        Node subtree = createSubTree(element1, element2);
        QueueNode newQElement = createNewQElement(subtree);
        enqueue(newQElement, head);
    }
    
    return head->next->element;
}

//Recursively go through huffman tree and store codes in a string array passed by address
int storeHuffmanCodes(Node root, char codeArray[127][8], char code[8], int position){
    if(root->left){
        code[position] = '0';

        //This is done since every change in left branch of tree
        //will affect the codes for the right branch of the tree
        //because they are "binded" by address
        char leftCodeCopy[8];
        for (int i = 0; i < 8; i++)
            leftCodeCopy[i] = code[i];

        storeHuffmanCodes(root->left, codeArray, leftCodeCopy, position + 1);
    }
    if(root->right){
        code[position] = '1';
        storeHuffmanCodes(root->right, codeArray, code, position + 1);
    }
    if(root->right == NULL && root->left == NULL){
        printf("%c  %s\n", root->character, code);
        strcpy(codeArray[root->character], code);
    }

    return 0;
}


//Set header in string for latter posibility to decode
int setHeader(int* occurences, char* codedString){
    int position = 0;
    for(int i = 0; i < 127; i++){
        if (occurences[i] == 0)
            continue;
        int bitArray[8];
        decimalToBinary(i, bitArray);
        for (int i = 0; i < 8; i++)
            codedString[position++] = (char) bitArray[i];
        
        codedString[position++] = '-';
        char* stringNum = intToCharArray(occurences[i]);
        strcat(codedString, stringNum);
        position += strlen(stringNum);
        free(stringNum);
        codedString[position++] = ',';
    }
    position--;
    codedString[position++] = '\n';
    return position;
}


Node readHeader(char* source){
    char* token = strtok(source, ",");
    char original[8];
    int occurences[127];
    int occ;
    while (token!=NULL)
    {
        int bitArr[8];
        sscanf("%s-%d", original, occ);
        convertCharToBitArray(original, bitArr);
        int symbol = binaryToDecimal(bitArr);
        occurences[symbol] = occ;
        token = strtok(NULL, ",");
    }
    QueueNode head = createNewQElement(NULL);
    convertToPriorityQueue(occurences, head);
    Node root = buildHuffmanTree(head);
    return root;
}

 //REWRITE THIS SHITCODE                       
//Translate original string to huffman coding
int encodeStringToHuffman(char* originalString, char* codedString, char codeArray[127][8], int* occurences){
    int currLen = 0;
    char newSymbol[8], blank[8];
    int position = setHeader(occurences, codedString);

    for(int i = 0; i < strlen(originalString); i++){
        for(int j = 0; j < 8; j++){
            if ((int)codeArray[originalString[i]][j] == 0)
                break;
            newSymbol[currLen] = codeArray[originalString[i]][j];
            currLen++;
            if(currLen == 8){
                int bitArr[8];
                convertCharToBitArray(newSymbol, bitArr);
                int asciiVal = binaryToDecimal(bitArr);
                codedString[position] = (char)asciiVal;
                position++;
                currLen = 0;
                strcpy(newSymbol, blank);
            }
        }
    }

    if (currLen != 0){
        for (int i = 0; i < 8-currLen; i++)
            blank[i] = newSymbol[i-currLen+1];
        for (int i = 8-currLen; i < 0; i++)
            blank[i] = '0';
        int bitArr[8];
        convertCharToBitArray(blank, bitArr);
        int asciiVal = binaryToDecimal(bitArr);
        codedString[position] = (char)asciiVal;
    }
    codedString[position+1] = '\0';
    FILE* f = fopen("encoded.bin", "wb");
    fwrite(codedString, strlen(codedString), 1, f);
    fclose(f);
    return 0;
}


int decodeFromHuffman(char* filename){
    FILE* encoded = fopen(filename, "rb");
    int counter = 0;
    while (fgetc(encoded)!='\n')
        counter++;
    rewind(encoded);
    char* header = malloc(counter);
    fgets(header, counter, encoded);
    Node root = readHeader(header);
    free(header);
    FILE* f = fopen("decoded.txt", "w");
    Node rootCpy = root;
    while (!feof(encoded)){
        char c = fgetc(encoded);
        int bitArr[8];
        decimalToBinary(c, bitArr);
        for (int i = 0; i < 8; i++){
            if (bitArr[i] == 0)
                root = root->left;
            if (bitArr[i] == 1)
                root = root->right;
            if (root->left == NULL && root->right == NULL){
                fputc(root->character, f);
                root = rootCpy;
            }
        }
    }
    fclose(f);
    fclose(encoded);
    return 0;
}


int convertCharToBitArray(char* charArray, int* bitArray){
    for (int i = 0; i < 8; i++)
        bitArray[i] = charArray[i] - '0';
    return 0;
}

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

int binaryToDecimal(int* bitArray){
    int sum = 0;
    for (int i = 7; i >= 0; i--)
        sum += bitArray[i] * pow(2, 7-i);
    return sum;    
}

int decimalToBinary(int decimal, int* bitArray){
    for (int i = 0; i < 8; i++){
        bitArray[7-i] = decimal % 2 + 48;
        decimal = decimal/2;
    }
    return 0;    
}

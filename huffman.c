#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"

//Build Huffman tree from queue
Node buildHuffmanTree(QueueNode head){
    if (head->next == NULL)
        return NULL;
    
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
int storeHuffmanCodes(Node root, char codeArray[127][127], char code[127], int position){
    if(root->left){
        code[position] = '0';

        //This is done since every change to the variable in one branching
        //will affect the codes for the other branching of the tree
        //because they are "binded" by address
        char leftCodeCopy[127];
        for (int i = 0; i < 127; i++)
            leftCodeCopy[i] = code[i];

        storeHuffmanCodes(root->left, codeArray, leftCodeCopy, position + 1);
    }
    if(root->right){
        code[position] = '1';
        storeHuffmanCodes(root->right, codeArray, code, position + 1);
    }
    if(root->right == NULL && root->left == NULL)
        strcpy(codeArray[root->character], code);

    return 0;
}


//Set header in string for latter posibility to decode
char* setHeader(int* occurences, int *size){
    for (int i = 0; i < 127; i++)
        if (occurences[i]!=0)
            *size += (10 + strlen(intToCharArray(occurences[i])));

    char * headerString = malloc(*size * sizeof(char));
    int position = 0;
    for(int i = 0; i < 127; i++){
        if (occurences[i] == 0)
            continue;
        int bitArray[8];
        decimalToBinary(i, bitArray);
        for (int i = 0; i < 8; i++)
            headerString[position++] = (char) bitArray[i];
        
        headerString[position++] = '-';
        char* stringNum = intToCharArray(occurences[i]);
        strcat(headerString, stringNum);
        position += strlen(stringNum);
        free(stringNum);
        headerString[position++] = ',';
    }
    position--;
    headerString[position++] = '\n';
    return (char*)headerString;
}


//Read a header and convert it to a huffman tree used for decoding
Node readHeader(char* source){
    char* token = strtok(source, ",");
    char original[9];
    int occurences[127] = {0};
    int occ;
    while (token!=NULL){
        int bitArr[8];
        sscanf(token, "%[0-1]-%d", original, &occ);
        convertCharArrToBitArr(original, bitArr);
        int symbol = binaryToDecimal(bitArr);
        occurences[symbol] = occ;
        token = strtok(NULL, ",");
    }
    QueueNode head = createNewQElement(NULL);
    convertToPriorityQueue(occurences, head);
    Node root = buildHuffmanTree(head);
    free(head->next);
    free(head);
    return root;
}


//Encode the input string using the huffman coding method
int encodeStringToHuffman(char* plainTextString, char* codedString, char codeArray[127][127], int* occurences){
    FILE* f = fopen("encoded.bin", "wb");
    uint8_t buffer = 0;
    int fullness = 0;
    int size = 0;
    char* header = setHeader(occurences, &size);
    fwrite(header, size, 1, f);
    free(header);

    for(int i = 0; i < strlen(plainTextString); i++){
        for (int j = 0; j < 127; j++){
            if ((int)codeArray[plainTextString[i]][j] == 0)
                break;
            int bit = codeArray[plainTextString[i]][j] - '0';
            buffer |= bit << (7-fullness);
            fullness++;
            if (fullness==8){
                fputc(buffer, f);
                fullness = 0;
                buffer = 0;
            }
        }
    }
    if (fullness != 0){
        for (int i = 7-fullness; i >= 0; i--)
            buffer |= 0 << i;
        fputc(buffer, f);
    }
    fclose(f);
    return 0;
}


//Decode binary file which is encoded in huffman code
int decodeFromHuffman(char* filename){
    FILE* encoded = fopen(filename, "rb");
    int counter = 1;
    while (fgetc(encoded)!='\n')
        counter++;

    rewind(encoded);
    char* header = malloc(counter);
    fgets(header, counter, encoded);
    fgetc(encoded);
    Node root = readHeader(header);
    free(header);
    FILE* decoded = fopen("decoded.txt", "w");
    Node rootCpy = root;
    int len = 0;
    getLen(root, &len);
    while (!feof(encoded)){
        char c = fgetc(encoded);
        for(int i = 7; i>=0; i--){
		    int a = (c >> i) & 1;
            if(len == 0)
                break;

            if (a == 0)
                root = root->left;
            if (a == 1)
                root = root->right;
            if (root->left == NULL && root->right == NULL){
                fputc(root->character, decoded);
                len--;
                root = rootCpy;
            }
    	}
    }
    deallocate(root);
    fclose(decoded);
    fclose(encoded);
    return 0;
}


//Get the length of the encoded string
int getLen(Node root, int* sum){
    if(root==NULL)
        return 0;
    if(root->left == NULL && root->right == NULL)
        *sum += root->occurences;
    getLen(root->left, sum);
    getLen(root->right, sum);
    return 0;
}


//Free all the memory taken up by the huffman tree
int deallocate(Node root){
    if(root == NULL)
        return 0;
    deallocate(root->left);
    deallocate(root->right);
    free(root);
    return 0;
}

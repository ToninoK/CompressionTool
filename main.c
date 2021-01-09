#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "huffman.h"


//Abstract the process of compressing to just one function
int compress(char* text){
    int occ[127] = {0};
    char codeArray[127][127] = {0}, code[127];
    printf("\nCalculating frequencies of letters...");
    int fileSize = getOccurences(text, occ);
    printf("\nFile to start with is %d bytes in size.", fileSize);
    printf("\nCreating Huffman tree...");
    QueueNode head = createNewQElement(NULL);
    if(head == NULL){
        printf("Error: Memory allocation failed.");
        return -1;
    }
    convertToPriorityQueue(occ, head);
    Node root = buildHuffmanTree(head);
    if(root == NULL){
        printf("Warning: No data. Exiting");
        return 1;
    }
    storeHuffmanCodes(root, codeArray, code, 0);
    char* encoded = malloc(strlen(text));
    printf("\nEncoding data...");
    int endFileSize = encodeStringToHuffman(text, encoded, codeArray, occ);
    printf("\nEncoded file is %d bytes in size.", endFileSize);
    printf("\nFreeing up taken memory...");
    deallocate(root);
    free(head->next);
    free(head);
    return 0;
}


int main(){
    int occ[127] = {0};
    int selection;
    char codeArray[127][127] = {0}, code[127];
    char filename[50]; 

    printf("\nSelect an option:\n");
    printf("\n1) Compression\n2) Decompression\nType 1 or 2 and hit enter (be gentle): ");
    scanf(" %d", &selection);
    
    printf("\nEnter filename: ");
    scanf("%s", filename);

    switch (selection){
        case 1:
            {
                char* text = getTextFromFile(filename);
                int result = compress(text);
                if(result == 0)
                    printf("\nSuccess!\nData is encoded in the file encoded.bin.\nFeel free to rename it since I didn't feel like implementing it.\n");
                else
                    printf("\nError occurred");
                break;
            }
        case 2:
            {
                decodeFromHuffman(filename);
                printf("\nDecoded file.\nData is decoded in the file decoded.txt.\nFeel free to rename it since i didn't feel like implementing it :).\n");
            }
            break;
    default:
        printf("You can't follow simple instructions, can you? bye.");
        break;
    }

    return 0;
}
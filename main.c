#include<stdio.h>
#include<stdlib.h>

#include "helper.h"
#include "huffman.h"


int main(){
    char* start = "aaaaabbbbbbbbbccccccccccccdddddddddddddeeeeeeeeeeeeeeeefffffffffffffffffffffffffffffffffffffffffffff";
    int occ[256] = {0};
    getOccurences(start, occ);
    QueueNode head = createNewQElement(NULL);
    convertToPriorityQueue(occ, head);
    Node root = buildHuffmanTree(head);
    char codeArray[256][8], code[8];
    storeHuffmanCodes(root, codeArray, code, 0);
    for(int i = 0; i < 256; i++){
        printf("%c\t", (char)i);
        for(int j = 0; j < 8; j++)
            printf("%c", codeArray[i][j]);
        printf("\n");
    }
    return 0;
}
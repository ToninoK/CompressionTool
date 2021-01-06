#include <string.h>
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
int storeHuffmanCodes(Node root, char codeArray[256][8], char code[8], int position){
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
        strcpy(codeArray[root->character], code);
    }

    return 0;
}


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "helper.h"
#include "huffman.h"


void padding ( char ch, int n )
{
  int i;

  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void structure ( Node root, int level )
{
  int i;

  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  }
  else {
    structure ( root->right, level + 1 );
    padding ( '\t', level );
    printf ( "%c %d\n", root->character, root->occurences );
    structure ( root->left, level + 1 );
  }
}

int main(){
    char* start = "Ovo je random poruka koju sam ja napisao.";
    int occ[127] = {0};
    getOccurences(start, occ);
    
    QueueNode head = createNewQElement(NULL);
    convertToPriorityQueue(occ, head);
    Node root = buildHuffmanTree(head);
    char codeArray[127][8] = {0}, code[8];
    storeHuffmanCodes(root, codeArray, code, 0);
    char new[100];
    encodeStringToHuffman(start, new, codeArray, occ);
    decodeFromHuffman("encoded.bin");
    printf("%s", new);
    // for (int i = 0; i < strlen(new); i++)
        // printf("%c %d\n", new[i], new[i]);
    
    return 0;
}
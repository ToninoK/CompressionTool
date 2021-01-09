#include "helper.h"
#include "queue.h"

Node buildHuffmanTree(QueueNode);
int storeHuffmanCodes(Node, char[127][127], char[8], int);
char* setHeader(int*, int*);
int encodeStringToHuffman(char*, char*, char[127][127], int*);
Node readHeader(char*);
int getLen(Node, int*);
int deallocate(Node);
int decodeFromHuffman(char*);

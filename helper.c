#include<string.h>
#include<stdlib.h>

#include "helper.h"

//Create new tree node (leaf)
Node createNewElement(char character, int number){
    Node new = malloc(sizeof(Element));
    if(new == NULL)
        return NULL;
    new->character = character;
    new->number = number;
    new->left = NULL;
    new->right = NULL;
    return new;
}

//Create new queue node
QueueNode createNewQElement(Node element){
    QueueNode new = malloc(sizeof(QueueElement));
    if(new == NULL)
        return NULL;
    new->element = element;
    new->next = NULL;
    return new;
}

//Add to priority queue
int enqueue(QueueNode new, QueueNode head){
    if(head->next == NULL){
        head->next = new;
        return 0;
    }
    while(head->next!=NULL && head->next->element->occurences >= new->element->occurences)
        head = head->next;
    new->next = head->next;
    head->next = new;
    return 0;
}

//Remove front of priority queue
int dequeue(Node head){
    Node temp = head->next;
    head->next = temp->next;
    free(temp->element);
    free(temp);
}

//Get the front of priority queue
Node peek(Node head){
    if(head->next == NULL)
        return NULL;
    return head->next->element;
}


//Takes in a string and counts occurences of each character in the string
//This is done with an integer array where the position represents the ascii value of character
//and the value represents the number of occurences
int getOccurences(char* buffer, int* occurences){
    for(int i = 0; i < strlen(buffer); i++)
        occurences[(int)buffer[i]] += 1;
    return 0;
}


//Takes an int array of character occurences and converts it to a priority queue
int convertToPriorityQueue(int* occurences, QueueNode head){
    for(int i = 0; i < 256; i++){
        Node newElement = createNewNode((char) i, occurences[i]);
        Node newQElement = createNewQNode(newElement);
        enqueue(newQElement, head);
    }
    return 0;
}

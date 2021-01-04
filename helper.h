
typdef struct Element* Node;
typdef struct QueueElement* QueueNode;


typedef struct element{
    char character;
    int occurences;
    Node left;
    Node right;
}Element;

typedef struct queueElement{
    QueueElement element;
    QueueNode next;
}QueueElement;


int createNewQElement(Node);   
int createNewElement(char, int);   
int dequeue(Node);
int enqueue(QueueNode, QueueNode);
Node peek(Node);
int getOccurences(char*, int*);
int convertToPriorityQueue(int*, QueueNode);

typedef struct element* Node;
typedef struct queueElement* QueueNode;


typedef struct element{
    char character;
    int occurences;
    Node left;
    Node right;
}Element;

typedef struct queueElement{
    Node element;
    QueueNode next;
}QueueElement;


QueueNode createNewQElement(Node);   
Node createNewElement(char, int);   
int dequeue(QueueNode);
int enqueue(QueueNode, QueueNode);
Node peek(QueueNode);
int getOccurences(char*, int*);
Node createSubTree(Node, Node);
int convertToPriorityQueue(int*, QueueNode);
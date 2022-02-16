
/*-----------------------
Riverse binary tree

  7
 6   9
3 5 2 1

    7
  9   6
1 2  5 3

-------------------------
Riverse singly link list

Head ->1->2->3->4->5-> NULL
Head ->5->4->3->2->1-> NULL
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int nodeData;
    struct Node* nextNode;
};


typedef struct Node Node;

Node* listHead = NULL;;

void InsertData(int data)
{
    Node* tempNode = listHead;
    Node* newNode = (Node*) malloc (sizeof(Node));
    newNode->nodeData = data;
    newNode->nextNode = NULL;
    
    if(listHead == NULL)
    {
        listHead = newNode;
        return;
    }
    
    while(tempNode->nextNode != NULL)
        tempNode = tempNode->nextNode;
        
    tempNode->nextNode = newNode;
}

void PrintList()
{
    Node* tempNode = listHead;
    while(tempNode != NULL)
    {
        printf("%d->", tempNode->nodeData);
        tempNode=tempNode->nextNode;
    }
    printf("NULL\n");    
}

void ReverseList()
{
    Node* tempNode = listHead;
    
    int listSize = 0;
    
    while(tempNode != NULL)
    {
        listSize++;
        tempNode = tempNode->nextNode;
    }
    
    Node* nodeList[listSize];
    
    tempNode = listHead;
    
    for(int i = 0 ; i < listSize ; ++i)
    {
        nodeList[i] = tempNode;
        tempNode = tempNode->nextNode;
    }
    
    listHead = nodeList[listSize-1];
    tempNode = listHead;
    for(int i = listSize-2 ; i >= 0 ; --i)
    {
        tempNode->nextNode = nodeList[i];
        tempNode = tempNode->nextNode;
    }
    tempNode->nextNode = NULL;
}

void ReverseList2()
{
    Node *currentNode = listHead, *prevNode = NULL, *nextNode = NULL;
    while(currentNode!=NULL)
    {
        nextNode              = currentNode->nextNode;
        currentNode->nextNode = prevNode;;
        prevNode              = currentNode;
        currentNode           = nextNode;
    }
    listHead = prevNode;
}

void FreeList()
{
    Node* tempNode = listHead;
    while(tempNode != NULL)
    {
        Node* currentNode = tempNode;
        tempNode = tempNode->nextNode;
        free(currentNode);
        currentNode = NULL;
    }
}

int main()
{
    for(int i = 1 ; i <= 5 ; ++i)
        InsertData(i);

    PrintList();
    
    ReverseList2();
    
    PrintList();
    
    FreeList();
    
    return 0;
}
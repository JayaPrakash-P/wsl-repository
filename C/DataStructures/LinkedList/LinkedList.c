#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATASETSIZE 10

struct SNode{
    int nodeData;
    struct SNode* nextNode;
};

typedef struct SNode SNode;

struct LinkedList{
    SNode* listHead;
    int* listData;
};

typedef struct LinkedList LList;

LList list;


void InsertAtEnd(int data)
{
    SNode *tempNode = list.listHead;
    
    SNode* newNode      = (SNode*)malloc(sizeof(SNode));
    newNode->nodeData   = data;
    newNode->nextNode   = NULL;
    
    if(tempNode == NULL)
    {
        list.listHead = newNode;
    }
    else
    {
        while( tempNode->nextNode != NULL )
            tempNode = tempNode->nextNode;
        tempNode->nextNode = newNode;
    } 
}

void InsertAtBeginning(int data)
{
    SNode *tempNode = list.listHead;
    
    SNode* newNode      = (SNode*)malloc(sizeof(SNode));
    newNode->nodeData   = data;
    newNode->nextNode   = NULL;
    
    if(tempNode == NULL)
    {
        list.listHead = newNode;
    }
    else
    {
        newNode->nextNode   = tempNode;
        list.listHead       = newNode;
    } 
}

void DisplayList()
{
    SNode *tempNode = list.listHead;
    while(tempNode!=NULL)
    {
        printf("%d ", tempNode->nodeData);
        tempNode = tempNode->nextNode;
    }
    printf("\n");
}

void GenerateRandomData(int* randomData)
{
    srand(time(NULL));
    for(int i = 0 ; i < DATASETSIZE ; ++i)
    {    
        randomData[i] = rand() % (DATASETSIZE*10);
        printf("%d ", randomData[i]);
    }
    printf("\n");
}

void DisplayandomData(int* randomData)
{
    for(int i = 0 ; i < DATASETSIZE ; ++i)
        printf("%d ", randomData[i]);
    printf("\n");
}

void RemoveNodes(SNode** headNode, int data)
{
    SNode* temp = *headNode;
    SNode* prevNode = temp;

    while( (temp != NULL) && (temp->nodeData == data))
    {
        *headNode = temp->nextNode;
        free(temp);
        temp = *headNode;
    }

    while(temp != NULL)
    {
        if(temp->nodeData == data)
        {
            prevNode->nextNode = temp->nextNode;
            free(temp);
            temp = prevNode;
        }
        else
        {
            prevNode = temp;
        }
        temp = temp->nextNode;
    }
}

void main()
{
    list.listHead=NULL;
    list.listData=NULL;
    int* randomData = (int*) calloc(DATASETSIZE,sizeof(int));
    GenerateRandomData(randomData);
    DisplayandomData(randomData);
    for(int i = 0 ; i < DATASETSIZE ; ++i)
    {
        InsertAtEnd(randomData[i]);
        InsertAtBeginning(randomData[i]);
    }
    printf("\n");
    DisplayList();
    printf("Enter node data to remove:");
    int data;
    scanf("%d",&data);
    RemoveNodes(&list.listHead, data);
    DisplayList();
}
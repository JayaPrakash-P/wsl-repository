#include <stdio.h>
#include <stdlib.h>

struct BTNode
{
    int data;
    struct BTNode* leftNode;
    struct BTNode* rightNode;
};

typedef struct BTNode* BTNodePtr;

BTNodePtr Insert(BTNodePtr rootNode, int data)
{
    if(!rootNode)
    {
        rootNode = (BTNodePtr) malloc(sizeof(*rootNode));
        rootNode->data = data;
        rootNode->leftNode = NULL;
        rootNode->rightNode = NULL;
    }
    else if (data < rootNode->data)
    {
        rootNode->leftNode = Insert(rootNode->leftNode,data);
    }
    else
    {
        rootNode->rightNode = Insert(rootNode->rightNode,data);
    }
    return rootNode;
}

void InOrder(BTNodePtr rootNode)
{
    if(!rootNode)
    {
        //printf("[N]");
        return;
    }
    InOrder(rootNode->leftNode);
    printf("[%d]",rootNode->data);
    InOrder(rootNode->rightNode);
}

void Reverse(BTNodePtr rootNode)
{
    if(!rootNode)
        return;
    
    Reverse(rootNode->leftNode);
    Reverse(rootNode->rightNode);

    BTNodePtr tempNode = NULL;
    tempNode = rootNode->leftNode;
    rootNode->leftNode = rootNode->rightNode;
    rootNode->rightNode = tempNode;
}

void FreeTree(BTNodePtr rootNode)
{
    if(!rootNode)
        return;
    
    FreeTree(rootNode->leftNode);
    FreeTree(rootNode->rightNode);

    free(rootNode);
    rootNode = NULL;

}

int main()
{
    BTNodePtr bsTree = NULL;
    bsTree = Insert(bsTree,6);
    bsTree = Insert(bsTree,5);
    bsTree = Insert(bsTree,9);
    bsTree = Insert(bsTree,8);
    bsTree = Insert(bsTree,4);
    bsTree = Insert(bsTree,3);
    bsTree = Insert(bsTree,7);
    InOrder(bsTree);
    Reverse(bsTree);
    printf("\n");
    InOrder(bsTree);
    printf("\n");
    //FreeTree(bsTree);
}
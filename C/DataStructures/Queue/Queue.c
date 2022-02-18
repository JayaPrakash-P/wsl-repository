#include <stdio.h>
#include <stdlib.h>

struct CircularArray
{
    int enqIndex;
    int deqIndex;
    int cArraySize;
    int* cArray;
};

typedef struct CircularArray CircularArray;

void Init(CircularArray *myArray)
{
    myArray->enqIndex = -1;
    myArray->deqIndex = -1;
    myArray->cArray = (int*)calloc(myArray->cArraySize, sizeof(int));
}

int Enqueue(CircularArray* myArray, int data)
{
    int ret = -1;
    if(myArray->enqIndex !=  myArray->cArraySize)
    {
        myArray->cArray[++(myArray->enqIndex)] = data;
        ret = 0;
    }

    //printf("myArray->deqIndex:%d", (myArray->deqIndex));
    //printf("myArray->enqIndex:%d", (myArray->enqIndex));

    return ret;
}

int Dequeue(CircularArray* myArray)
{
    int data = -1;
    if(myArray->deqIndex != myArray->enqIndex )
        data = myArray->cArray[++(myArray->deqIndex)];
    return data;
}

int main()
{
    CircularArray myArray;
    printf("Enter Size :\n");
    scanf("%d", &(myArray.cArraySize));
    printf("myArray.cArraySize:%d\n",myArray.cArraySize);
    Init(&myArray);
    for(int i = 1 ; i <= (myArray.cArraySize+2) ; ++i)
        printf("Enqueue returned : %d\n", Enqueue(&myArray, i));
    for(int i = 1 ; i <= 3 ; ++i)
        printf("Dequeue returned : %d\n", Dequeue(&myArray));
}
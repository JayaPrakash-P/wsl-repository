#include <stdio.h>
#include <stdlib.h>

typedef struct CircularBuffer
{
    int* valuePtr;
    int bufHead;
    int bufTail;
    int bufSize;
    int bufCapacity;
} CircularBuffer;

bool Empty(CircularBuffer* buffer)
{
    return (buffer->bufSize == 0);
}

bool Full(CircularBuffer* buffer)
{
    return (buffer->bufSize == buffer->bufCapacity);
}

void Init(CircularBuffer* buffer, int bufCapacity)
{
    buffer->valuePtr = (int*) malloc(sizeof(int) * bufCapacity);
    buffer->bufCapacity = bufCapacity;
    buffer->bufHead = 0;
    buffer->bufTail = 0;
    buffer->bufSize = 0;
}

bool Enqueue(CircularBuffer* buffer, int data)
{
    if(Full(buffer))
        return false;
    
    buffer->valuePtr[buffer->bufTail] = data;
    buffer->bufTail = (buffer->bufTail + 1) % (buffer->bufCapacity);
    buffer->bufSize++;
    return true;
}

int Dequeue(CircularBuffer* buffer)
{
    if(Empty(buffer))
        return 0;
    
    int data = buffer->valuePtr[buffer->bufHead];
    buffer->bufHead = (buffer->bufHead + 1) % (buffer->bufCapacity);
    buffer->bufSize--;
    return data;
}

int Peek(CircularBuffer* buffer)
{
    if(Empty(buffer))
        return 0;
    
    int data = buffer->valuePtr[buffer->bufHead];
    return data;
}

void Destroy(CircularBuffer* buffer)
{
    free(buffer->valuePtr);
    buffer->valuePtr = NULL;
}

void Display(CircularBuffer* buffer)
{
    int bufSize = buffer->bufSize;
    for(int i = 0 ;  i < bufSize ; ++i)
    {
        int data = Dequeue(buffer);
        printf("[%d]", data);
    }
    printf("\n");
}
int main()
{
    CircularBuffer cirBuf;
    Init(&cirBuf, 5);
    Enqueue(&cirBuf, 1);
    Enqueue(&cirBuf, 3);
    Enqueue(&cirBuf, 2);
    Display(&cirBuf);
    Enqueue(&cirBuf, 4);
    Enqueue(&cirBuf, 6);
    Enqueue(&cirBuf, 5);
    Display(&cirBuf);
    Enqueue(&cirBuf, 11);
    Enqueue(&cirBuf, 33);
    Enqueue(&cirBuf, 24);
    Enqueue(&cirBuf, 44);
    Enqueue(&cirBuf, 66);
    Enqueue(&cirBuf, 55);
    Display(&cirBuf);
    Destroy(&cirBuf);
}
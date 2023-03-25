#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define HEAPSIZE 10
int minHeap[HEAPSIZE];

int activeIndex = 1;

void HeapifyBottomToTop(int index)
{
    if(index == 0)
        return;
    
    int parentIndex = index/2;

    if(minHeap[parentIndex] > minHeap[index])
    {
        int temp                = minHeap[parentIndex];
        minHeap[parentIndex]    = minHeap[index];
        minHeap[index]          = temp;
        HeapifyBottomToTop(parentIndex);
    }
}

void Push(int data)
{
    if(activeIndex == HEAPSIZE)
    {
        printf("\nHeap FULL - %d not inserted\n",data);
        return;
    }
    
    minHeap[activeIndex] = data;
    HeapifyBottomToTop(activeIndex);
    activeIndex++;
}

void HeapifyTopToBottom(int index)
{
    int lChild   = index*2;
    int rChild   = index*2 + 1;
    int smallest = index;

    if( (lChild < activeIndex) && (minHeap[lChild] < minHeap[smallest]) )
        smallest = lChild;
    if( (rChild < activeIndex) && (minHeap[rChild] < minHeap[smallest]) )
        smallest = rChild;

    if(smallest != index)
    {
        int temp            = minHeap[smallest];
        minHeap[smallest]   = minHeap[index];
        minHeap[index]      = temp;
        HeapifyTopToBottom(smallest);
    }   
}

int Pop()
{
    if(activeIndex == 1)
    {
        printf("Heap empty\n");
        return INT_MIN;
    }
    
    int data = minHeap[1];
    minHeap[1] = minHeap[activeIndex-1];
    activeIndex--;
    HeapifyTopToBottom(1);
    return data;
}

void Display()
{
    for(int i = 1 ; i < activeIndex; ++i)
        printf("%d ", minHeap[i]);
    printf("\n");
}

int main()
{
    srand(time(NULL));
    for(int i = 1 ; i <= HEAPSIZE; ++i)
    {
        int data = rand() % (HEAPSIZE*10);
        printf("%d ", data);
        Push(data);
    }
    printf("\n");

    Display();

    int activeSize = activeIndex-1;
    for(int i = 1 ; i <= activeSize; ++i)
    {
        int data = Pop();
        printf("%d ", data);
    }
    printf("\n");

    return 0;
}


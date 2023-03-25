#include "Utilities.h"
#include <iostream>

void MaxHeapify(IntVec & myVec, int i)
{
    int largestNodeIndex = i; // Initialize largest as root
    int leftChildIndex   = 2 * i + 1; // left = 2*i + 1
    int rightChildIndex  = 2 * i + 2; // right = 2*i + 2
  
    // If left child is larger than root
    if (leftChildIndex < myVec.size())
        largestNodeIndex = (myVec[leftChildIndex] > myVec[largestNodeIndex])?
                            leftChildIndex:largestNodeIndex;
  
    // If right child is larger than largest so far
    if (rightChildIndex < myVec.size())
        largestNodeIndex = (myVec[rightChildIndex] > myVec[largestNodeIndex])?
                            rightChildIndex:largestNodeIndex;
  
    // If largest is not root
    if (largestNodeIndex != i) {
        swap(myVec[i], myVec[largestNodeIndex]);
  
        // Recursively heapify the affected sub-tree
        MaxHeapify(myVec, largestNodeIndex);
    }
}

void BuildMaxHeap(IntVec & myVec)
{
    // Index of last non-leaf node
    int startIdx = (myVec.size() / 2) - 1;
  
    // Perform reverse level order traversal
    // from last non-leaf node and heapify
    // each node
    for (int i = startIdx; i >= 0 ; i--) {
        MaxHeapify(myVec, i);
    }
}


void MinHeapify(IntVec & myVec, int i)
{
    int smalestNodeIndex = i; // Initialize largest as root
    int leftChildIndex   = 2 * i + 1; // left = 2*i + 1
    int rightChildIndex  = 2 * i + 2; // right = 2*i + 2
  
    // If left child is larger than root
    if (leftChildIndex < myVec.size())
        smalestNodeIndex = (myVec[leftChildIndex] < myVec[smalestNodeIndex])?
                            leftChildIndex:smalestNodeIndex;
  
    // If right child is larger than largest so far
      if (rightChildIndex < myVec.size())
        smalestNodeIndex = (myVec[rightChildIndex] < myVec[smalestNodeIndex])?
                            rightChildIndex:smalestNodeIndex;
  
    // If largest is not root
    if (smalestNodeIndex != i) {
        swap(myVec[i], myVec[smalestNodeIndex]);
  
        // Recursively heapify the affected sub-tree
        MinHeapify(myVec, smalestNodeIndex);
    }
}

void BuildMinHeap(IntVec & myVec)
{
    // Index of last non-leaf node
    int startIdx = (myVec.size() / 2) - 1;
  
    // Perform reverse level order traversal
    // from last non-leaf node and heapify
    // each node
    for (int i = startIdx; i >= 0 ; i--) {
        MinHeapify(myVec, i);
    }
}

void HeapSortAsc(IntVec myVect)
{
    cout << "[";
    while (!myVect.empty())
    {
        cout << *(myVect.begin()) << " ";
        myVect.erase(myVect.begin());
        if(myVect.empty())
            break;
        BuildMinHeap(myVect);
    }
    cout << "]\n";
}

void HeapSortDesc(IntVec myVect)
{
    cout << "[";
    while (!myVect.empty())
    {
        cout << *(myVect.begin()) << " ";
        myVect.erase(myVect.begin());
        if(myVect.empty())
            break;
        BuildMaxHeap(myVect);
    }
    cout << "]\n";
}

int main()
{
    IntVec myVec = GenerateRandmomIntVec(1000);
    BuildMinHeap(myVec);
    cout << "After building Min Heap :\n";
    DisplayVec(myVec);
    cout << "Asc : ";
    HeapSortAsc(myVec);
    BuildMaxHeap(myVec);
    cout << "After building Max Heap :\n";
    DisplayVec(myVec);
    cout << "Desc : ";
    HeapSortDesc(myVec);
    return 0;
}
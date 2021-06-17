#ifndef _BUBBLESORT_H_
#define _BUBBLESORT_H_

using namespace std;

constexpr unsigned int inputSize = 100;

template<class T> void BubbleSortAsc(T toSort[], int noOfItems);
template<class T> void BubbleSortDesc(T toSort[], int noOfItems);

#include "BubbleSort.cpp"

#endif //_BUBBLESORT_H_
#ifndef _BUBBLESORT_H_
#define _BUBBLESORT_H_

#include <iostream>
#include "../../Utilities/Utils.h"

template<class T>
class BubbleSort
{
public:
    BubbleSort() = default;
    void SortAscending(T toSort[]);
    void SortDescending(T toSort[]);
};

#endif //_BUBBLESORT_H_
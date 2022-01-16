#ifndef _BUBBLESORT_H_
#define _BUBBLESORT_H_

#include <iostream>
#include "../../Utilities/Utils.h"

template<class T, size_t N>
class BubbleSort
{
public:
    void SortAscending(T toSort[]) 
    {
        LogEntryExit log(__func__,LogType::ExecTimeOnly);
    
        bool swapped = false;
        for (auto i = 0 ; i < (N - 1) ; ++i)
        {
            for (auto j = 0 ; j < (N - i - 1) ; ++j)
                if (toSort[j] > toSort[j+1])
                {
                    std::swap(toSort[j], toSort[j+1]);
                    swapped = true;
                }
    
            if(!swapped) //Already sorted
                break;
        }
    }
    
    void SortDescending(T toSort[]) 
    {
        LogEntryExit log(__func__,LogType::ExecTimeOnly);
    
        bool swapped = false;
        for (auto i = 0; i < N - 1; i++)
        {
            for (auto j = 0; j < N - i - 1; j++)
                if (toSort[j] < toSort[j+1])
                {
                    std::swap(toSort[j], toSort[j+1]);
                    swapped = true;
                }
    
            if(!swapped) //Already sorted
                break;
        }
    }
};

#endif //_BUBBLESORT_H_
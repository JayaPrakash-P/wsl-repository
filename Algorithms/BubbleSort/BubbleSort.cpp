#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

#include "BubbleSort.h"
#include "../../Utilities/Utils.h"

template<class T>
void BubbleSortAsc(T toSort[], int noOfItems) 
{
	LogEntryExit log(__func__,LogType::All);

    bool swapped = false;
	for (auto i = 0; i < noOfItems - 1; i++)
	{
		for (auto j = 0; j < noOfItems - i - 1; j++)
			if (toSort[j] > toSort[j+1])
			{
				swap(toSort[j], toSort[j+1]);
				swapped = true;
			}

		if(!swapped)
		{
			cout << "Already sorted!!!\n";
			break;
		}
			
	}
}

template<class T>
void BubbleSortDesc(T toSort[], int noOfItems) 
{
	LogEntryExit log(__func__,LogType::All);

    bool swapped = false;
	for (auto i = 0; i < noOfItems - 1; i++)
	{
		for (auto j = 0; j < noOfItems - i - 1; j++)
			if (toSort[j] < toSort[j+1])
			{
				swap(toSort[j], toSort[j+1]);
				swapped = true;
			}

		if(!swapped)
		{
			cout << "Already sorted!!!\n";
			break;
		}
			
	}
}


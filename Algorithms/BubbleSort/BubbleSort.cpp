#include "BubbleSort.h"

template <typename T>
void BubbleSort<T>::SortAscending(T toSort[]) 
{
	LogEntryExit log(__func__,LogType::All);

    int noOfItems = sizeof(toSort)/sizeof(toSort[0]);

    bool swapped = false;
	for (auto i = 0; i < noOfItems - 1; i++)
	{
		for (auto j = 0; j < noOfItems - i - 1; j++)
			if (toSort[j] > toSort[j+1])
			{
				std::swap(toSort[j], toSort[j+1]);
				swapped = true;
			}

		if(!swapped)
		{
			std::cout << "Already sorted!!!\n";
			break;
		}
	}
}

template<typename T>
void BubbleSort<T>::SortDescending(T toSort[]) 
{
	LogEntryExit log(__func__,LogType::All);

    int noOfItems = sizeof(toSort)/sizeof(toSort[0]);

    bool swapped = false;
	for (auto i = 0; i < noOfItems - 1; i++)
	{
		for (auto j = 0; j < noOfItems - i - 1; j++)
			if (toSort[j] < toSort[j+1])
			{
				std::swap(toSort[j], toSort[j+1]);
				swapped = true;
			}

		if(!swapped)
		{
			std::cout << "Already sorted!!!\n";
			break;
		}
	}
}

template class BubbleSort<int>;
template class BubbleSort<char>;
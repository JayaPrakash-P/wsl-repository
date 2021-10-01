#include <iostream>

#include "./BubbleSort/BubbleSort.h"

const unsigned int inputSize = 100;

int main()
{
	int toSort[inputSize] = {0};
	unsigned int noOfItems = sizeof(toSort) / sizeof(toSort[0]);

    /* initialize random seed: */
    srand (time(NULL));

    for(auto i = 0 ; i < inputSize; i++)
		toSort[i] = rand() % inputSize;

	std::cout << "Before ASC: ";
	for (int i = 0; i < noOfItems; i++)
		std::cout << toSort[i] << " ";

	BubbleSort<int> bubbleSort;
	bubbleSort.SortAscending(toSort);

	std::cout << "After : ";
	for (int i = 0; i < noOfItems; i++)
		std::cout << toSort[i] << " ";
	std::cout << std::endl;

	/* initialize random seed: */
    srand (time(NULL));

    for(auto i = 0 ; i < inputSize; i++)
		toSort[i] = rand() % inputSize;

	std::cout << "Unsorted(DESC) : ";
	for (int i = 0; i < noOfItems; i++)
		std::cout << toSort[i] << " ";
	std::cout << std::endl;

	BubbleSort<int> bubbleSort;
	bubbleSort.SortDescending(toSort);

	std::cout << "Sorted(DESC) : ";
	for (int i = 0; i < noOfItems; i++)
		std::cout << toSort[i] << " ";
	std::cout << std::endl;

	return 0;
}

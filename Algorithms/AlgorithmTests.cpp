#include <iostream>

#include "./BubbleSort/BubbleSort.h"

extern const unsigned int inputSize;

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

	BubbleSortAsc<int>(toSort, noOfItems);

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

	BubbleSortDesc<int>(toSort, noOfItems);

	std::cout << "Sorted(DESC) : ";
	for (int i = 0; i < noOfItems; i++)
		std::cout << toSort[i] << " ";
	std::cout << std::endl;

	return 0;
}

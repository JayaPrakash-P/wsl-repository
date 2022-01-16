#include <iostream>

#include "Algorithms.h"
#include "gtest/gtest.h"

const unsigned int inputSize = 10000;

TEST(Bubble, Ascending)
{
  int toSort[inputSize] = {0};
  BubbleSort<int, inputSize> bubbleSort;
  GenerateRandomDataSet<int, inputSize>(toSort);
  bubbleSort.SortAscending(toSort);
  for(auto i = 0 ; i < (inputSize - 1) ; ++i)
    ASSERT_LE(toSort[i], toSort[i+1]);
}

TEST(Bubble, Descending)
{
  int toSort[inputSize] = {0};
  BubbleSort<int, inputSize> bubbleSort;
  GenerateRandomDataSet<int, inputSize>(toSort);
  bubbleSort.SortDescending(toSort);
  for(auto i = 0 ; i < (inputSize - 1) ; ++i)
    ASSERT_GE(toSort[i], toSort[i+1]);
}

class SortingTests : public testing::Test
{
 protected:
    void SetUp() override
    {
        GenerateRandomDataSet<int, inputSize>(toSort);
    }

    BubbleSort<int, inputSize> bubbleSort;
    int toSort[inputSize] = {0};
};

TEST_F(SortingTests, BubbleAscending)
{
  bubbleSort.SortAscending(toSort);
  for(auto i = 0 ; i < (inputSize - 1) ; ++i)
    ASSERT_LE(toSort[i], toSort[i+1]);
}

TEST_F(SortingTests, BubbleDescending)
{
  bubbleSort.SortDescending(toSort);
  for(auto i = 0 ; i < (inputSize - 1) ; ++i)
    ASSERT_GE(toSort[i], toSort[i+1]);
}

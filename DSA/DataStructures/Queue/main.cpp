#include "Queue.h"
#include <iostream>

int main()
{
  Queue<int>* myQueue = new Queue<int>(100);

  std::cout << "Queue- Enqueue 100 elements from 1~100\n";
  for (int i = 1 ; i <= 100 ; ++i)
    myQueue->Enqueue(i);

  myQueue->First();
  myQueue->Last();

  std::cout << "Queue - Dequeue 50 elements from 1~50\n";
  for (int i = 0 ; i < 50 ; ++i)
  {
    int data = myQueue->Dequeue();
    std::cout << data << " ";
  }
  std::cout << std::endl;

  myQueue->First();
  myQueue->Last();

  std::cout << "Queue- Enqueue 1 element 101\n";
  for (int i = 101 ; i <= 101 ; ++i)
    myQueue->Enqueue(i);
  std::cout << std::endl;
  myQueue->First();
  myQueue->Last();

  std::cout << "Try dequeue-ing 100 elements...\n";
  for (int i = 0 ; i < 100 ; ++i)
  {
    int data = myQueue->Dequeue();
    std::cout << data << " ";
  }
  std::cout << std::endl;

  delete myQueue;
}
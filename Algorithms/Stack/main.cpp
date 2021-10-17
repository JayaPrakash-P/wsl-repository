#include "Stack.h"
#include <iostream>

int main()
{
  Stack<int>* myStack = new Stack<int>(100);

  std::cout << "Stack- PUSH Test(SUCCESS)...\n";
  for (int i = 0 ; i < 100 ; ++i)
    myStack->Push(i);

  std::cout << "Stack - POP Test(SUCCESS)...\n";
  for (int i = 0 ; i < 100 ; ++i)
  {
    int data = myStack->Pop();
    std::cout << data << ",";
  }
  std::cout << std::endl;

  std::cout << "Stack - POP Test(FAILURE)...\n";
  for (int i = 0 ; i < 5 ; ++i)
  {
    int data = myStack->Pop();
    std::cout << data << ",";
  }
  std::cout << std::endl;

  std::cout << "Stack- PUSH Test(FAILURE)...\n";
  for (int i = 0 ; i < 105 ; ++i)
    myStack->Push(i);

  delete myStack;
}
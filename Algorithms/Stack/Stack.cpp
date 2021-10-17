#include "Stack.h"
#include <iostream>
#include <string>

template<typename T>
Stack<T>::Stack(int cap):myCapacity(cap), myTop(-1)
{
  std::cout << "Stack constructed with capacity : " << myCapacity << std::endl;
  myStack = new T[myCapacity];
}

template<typename T>
Stack<T>::~Stack()
{
  std::cout << "Stack destructed\n";
  delete[] myStack;
}

template<typename T>
void Stack<T>::Push(T data)
{
  if(IsFull())
  {
      std::cout << "Stack FULL!!!\n";
      return;
  }
  myStack[++myTop] = data;
}

template<typename T>
T Stack<T>::Pop()
{
  if(IsEmpty())
  {
      std::cout << "Stack EMPTY!!!\n";
      return 0;
  }
  return myStack[myTop--];
}

template<typename T>
T Stack<T>::Top()
{
  if(IsEmpty())
  {
      std::cout << "Stack EMPTY!!!\n";
      return 0;
  }
  return myStack[myTop];
}

template<typename T>
bool Stack<T>::IsEmpty()
{
  return (myTop == -1);
}

template<typename T>
bool Stack<T>::IsFull()
{
  return (myTop == (myCapacity - 1));
}

template class Stack<int>;
template class Stack<char>;
template class Stack<std::string>;
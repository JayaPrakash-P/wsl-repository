#ifndef _STACK_H_
#define  _STACK_H_

template<typename T>
class Stack
{
public:
  Stack(int cap = 100);
  ~Stack();

  void Push(T data);
  T    Pop();
  T    Top();

  bool IsEmpty();
  bool IsFull();

private:
  T            *myStack;
  int          myTop;
  unsigned int myCapacity;
};

#endif //_STACK_H_
#ifndef _QUEUE_H_
#define  _QUEUE_H_

template<typename T>
class Queue
{
public:
  Queue(int cap = 100);
  ~Queue();

  void   Enqueue(T data);
  T      Dequeue();
  void   First();
  void   Last();

  bool IsEmpty();
  bool IsFull();

private:
  T            *myQueue;
  int          myFront;
  int          myRear;
  unsigned int myCapacity;
};

#endif //_QUEUE_H_
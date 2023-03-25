#include "Queue.h"
#include <iostream>
#include <string>

template<typename T>
Queue<T>::Queue(int cap):myCapacity(cap), myFront(-1), myRear(-1)
{
  std::cout << "Queue constructed with capacity : " << myCapacity << std::endl;
  myQueue = new T[myCapacity];
}

template<typename T>
Queue<T>::~Queue()
{
  std::cout << "Queue destructed\n";
  delete[] myQueue;
}

template<typename T>
void Queue<T>::Enqueue(T data)
{
  if(IsFull())
  {
    std::cout << "Queue FULL!!!\n";
    return;
  }

  if(myRear == -1)
  {
    myRear++;myFront++;
  }

  if(myRear < (myCapacity))
  {
    myQueue[myRear++] = data;

  }
  else if ( (myRear % myCapacity) < myFront )
  {
    std::cout << "Enqueue @ Empty slot at the beginning!!!\n";
    myRear = (myRear % myCapacity) ;
    myQueue[myRear++] = data;
  }
  else
    std::cout << "Enqueue - Shouldn't get here!!!\n";
}

template<typename T>
T Queue<T>::Dequeue()
{
  if(IsEmpty())
  {
      std::cout << "Queue EMPTY!!!\n";
      return 0;
  }
  T data = 0;

  if(myFront < (myCapacity))
  {
    data = myQueue[myFront++];
  }
  else if ( (myFront % myCapacity) < myRear )
  {
    myFront = (myFront % myCapacity);
    data = myQueue[myFront++];
   }
  else
    std::cout << "Dequeue - Shouldn't get here!!!\n";

  if(myFront == myRear)
  {
    myFront = myRear = -1;
  }

  return data;
}

template<typename T>
void Queue<T>::First()
{
   std::cout << "Queue FIRST : myFront : " << myFront << " !!!\n";

}

template<typename T>
void Queue<T>::Last()
{
  std::cout << "Queue LAST : myRear : " << myRear << " !!!\n";
}

template<typename T>
bool Queue<T>::IsEmpty()
{
  return ( (myFront == -1) && (myRear == -1) );
}

template<typename T>
bool Queue<T>::IsFull()
{
  return (
           ( (myFront == 0) && (myRear == myCapacity) ) ||
           ( (myFront > 0 ) && (myRear == myFront)    )
         );
}

template class Queue<int>;
template class Queue<char>;
template class Queue<std::string>;
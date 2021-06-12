// conditionVariables.cpp

#include <condition_variable>
#include <iostream>
#include <thread>
#include <map>
#include <algorithm>
#include <cassert>
#include <unordered_set>

using namespace std;

template<class T>
T cmerge (T a, T b) { T t(a); t.insert(b.begin(),b.end()); return t; }

std::mutex mutex_;
std::condition_variable condVar; 
bool ping, pong;

bool dataReady{false};

#include <iostream>
#include <string>
 
class Car
{
private:
    std::string m_make;
    std::string m_model;
	int x;
 
public:
    Car(const std::string& make, const std::string& model, int x)
        : m_make{ make }, m_model{ model }, x{x}
    {
    }
 
	bool operator== (const Car &c)
	{
		std::cout << "operator== (const Car &c)" << std::endl;
		std::cout << m_make << " - " << c.m_make<< std::endl;
		std::cout << m_model << " - " << c.m_model<< std::endl;
		std::cout << x << " - " << c.x<< std::endl;

		return (m_make == c.m_make &&
				m_model == c.m_model &&
				x == c.x);
	}
	
	bool operator!= (const Car &c)
	{
		return !(*this == c);
	}
	
	bool operator==(int y)
	{
		std::cout << "operator==(int y)" << std::endl;
		Car myCar("","",y);
		return (y == myCar.x);
	}

  friend bool operator==(int y, const Car &c);

};
 
bool operator==(int y, const Car &c)
{
	std::cout << "operator==(const Car &c, int y)" << std::endl;
	Car myCar(c.m_make,c.m_model,y);
	return (myCar == c);
}
 
void waitingForWork(){
    std::cout << "Waiting - Worker..." << std::endl;
    std::unique_lock<std::mutex> lck(mutex_);
    condVar.wait(lck, []{ return ping; });   // (4)
    std::cout << "Running " << std::endl;
}

void setDataReady(){
    {
        std::lock_guard<std::mutex> lck(mutex_);
        dataReady = true;
    }
    std::cout << "Data prepared" << std::endl;
    condVar.notify_one();                        // (3)
}



void fx ()
{
	cout <<"fx" << endl;
}

void fy ()
{
	cout <<"fy" << endl;
}

void fz ()
{
	cout <<"fz" << endl;
}

typedef void(*FPtr)();


int main()
{
  std::cout << "assert(1)\n";
  assert(1);
  //std::cout << "assert(0)\n";
  //assert(0);
  std::cout << "assert(-1)\n";
  assert(-1);

  
  
  std::cout << std::endl;

  Car corolla{ "Toyota", "Corolla", 5 };
  Car camry{ "Toyota", "Camry", 6 };
  
  if (corolla == camry)
      std::cout << "a Corolla and Camry are the same.\n";
  
  if (corolla != camry)
      std::cout << "a Corolla and Camry are not the same.\n";
  
  if (6 == camry)
    std::cout << "a Corolla and Camry are the same 1.\n";
    
  if (camry == 6)
    std::cout << "a Corolla and Camry are the same 2.\n";
  
  FPtr funPtrArray[] = {fx,fy,fz};
  FPtr funPtrArray2[] = {&fx,&fy,&fz};
  
  for(int i = 0 ; i < 3 ; i++)
  {
	  //cout <<"*******1******" << endl;
	  //funPtrArray[i];
	  //funPtrArray2[i];
	  //cout <<"******2*******" << endl;
	  funPtrArray[i](); //OK
	  funPtrArray2[i]();//OK
	  //cout <<"******3*******" << endl;
	  //&funPtrArray[i]	;
	  //&funPtrArray2[i];
	  //cout <<"******4*******" << endl;
	  //*funPtrArray[i];
	  //*funPtrArray2[i];
	  //cout <<"******5*******" << endl;
  }
  

  
  ping = pong = false;
  std::cout << std::endl;

  std::thread t1(waitingForWork);               // (1)
  //std::thread t2(setDataReady);                 // (2)
  {
	  std::cout << "Waiting - Main..." << std::endl;
	  std::lock_guard<std::mutex> lg(mutex_);
	  ping = true;
  }

  condVar.notify_one();
  t1.join();
  //t2.join();
  
  std::cout << std::endl;
  
}

class Test
{
	int myNum;

public:
	Test(int x = 0):myNum(x)
	{
		cout << "Test(int x = 0) CTOR" << endl;
	}
	
/* 	Test(const Test& x):myNum(x.myNum)
	{
		cout << "Test(const Test& x) CTOR" << endl;
	} */
	
    Test operator++(int)
    {
		//cout << "operator++(MEMBER)" << endl;
    	Test temp = *this;
		myNum++;
    	return temp;
    }
    
    Test& operator++()
    {
    	//cout << "operator++(MEMBER-int)" << endl;
    	myNum++;
    	return *this;
    }
	
	friend ostream& operator << (ostream& , const Test& );
};

/* Test operator++(Test& test)
{
	Test temp = test;
	cout << "operator++(NONMEMBER)" << endl;
	test++;
	return temp;
}

Test& operator++(Test& test, int)
{
	cout << "operator++(NONMEMBER-int)" << endl;
	++test;
	return test;
} */

ostream& operator << (ostream& cout, const Test& test)
{
	cout << "myNum = " << test.myNum;
	return cout;
}

template<typename T>
T add(T head)
{
	cout << "T add(T head)" << endl;
	return(head);
}

template<typename T, typename ...Ts>
T add(T head, Ts ...tail)
{
	cout << "T add(T head, Ts ...tail) - Size = " << (sizeof...(tail)) << endl;
	//cout << "T add(T head, Ts ...tail) - (tail) = " << (...tail) << endl;//ERROR
	//cout << "T add(T head, Ts ...tail) - (tail...) = " << (tail...) << endl;//ERROR
    if(sizeof...(tail))
	{
		head += add(tail...);
		return(head);
	}
}
 
/* int main()
{
    auto b = add(1.1, 2.2, 3.3);
    std::cout << "b = " << b << '\n';

} */
/* int main()
{
    Test t1(10);
	Test t2(20);
	cout << "t1(Before) : " << t1 << endl;
	cout << "t2(Before) : " << t2 << endl;
	cout << "t1++(Now) : " << t1++ << endl;
	cout << "++t2(Now) : " << ++t2 << endl;
	cout << "t1(After) : " << t1 << endl;
	cout << "t2(After) : " << t2 << endl;
	
    return 0;
}
 */
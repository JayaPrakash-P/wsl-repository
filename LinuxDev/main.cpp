#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <map>
#include <thread>
#include <mutex>
#include <unordered_set>
#include <bitset>

#include "Helper.h"

using namespace std;

template<typename T> using GenericType = T;
template<typename T> using GenericVector = std::vector<T>;

typedef int intAlias;
//typedef cannot be templatized
//typedef std::vector<T> GenericVectorTypeDef;
//GenericVectorTypeDef<int> myVector;

//##################################################################################################ConstMemberinClassTest
class MyClass
{

public:

  MyClass(MyClass&& a) : myInt(a.myInt)
  {
    cout << "MyClass : MOVE CTOR" << endl;
  }
  MyClass& operator==(MyClass&& a)
  {
    cout << "MyClass : MOVE ASSIGNMENT operator" << endl;
    myInt = std::move(a.myInt);
    return *this;
  }
  MyClass(const MyClass& a) : myInt(a.myInt)
  {
    cout << "MyClass : COPY CTOR" << endl;
  }
  MyClass& operator==(const MyClass& a)
  {
    cout << "MyClass : COPY ASSIGNMENT operator" << endl;
    myInt = a.myInt;
    return *this;
  }
  MyClass(int a) : myInt(a)
  {
    cout << "MyClass : DEFAULT CTOR(int)" << endl;
  }
  MyClass() : myInt(0)
  {
    cout << "MyClass : DEFAULT CTOR(void)" << endl;
  }
  void Display()
  {
    cout << "MyClass::Display : myInt = " << myInt << endl;
  }

  //C++ 98 : Cannot use with STL since default assignment operator is not provided
  //by the compiler if clss has a const member

  //const int myInt;
  int myInt;
};

void ConstMemberinClassTest()
{
   std::vector<MyClass> myClassVec;
   myClassVec.reserve(10);

   MyClass myClassObj1(10);
   MyClass myClassObj2(20);
   MyClass myClassObj3(30);
   MyClass myClassObj4(40);
   MyClass myClassObj5(50);

   myClassVec.push_back(myClassObj1);
   myClassVec.push_back(myClassObj2);
   myClassVec.push_back(myClassObj3);
   myClassVec.push_back(myClassObj4);
   myClassVec.push_back(myClassObj5);
   myClassVec.push_back(MyClass(60));

   //MyClass myClassObj2(std::move(myClassObj1));
   //myClassObj1.Display();
   //myClassObj2.Display();
}

//##################################################################################################ForEachTest

using EmpDetail = std::pair<string, int>;

void DisplayEmp(EmpDetail empData)
{
  if(empData.second < 5)
    cout << "\t" << empData.first << endl;
}

void ForEachTest()
{
  std::map<string, int> employeeMap;

  employeeMap.insert({"Employee4", 4});
  employeeMap.insert({"Employee6", 6});
  employeeMap.insert({"Employee2", 2});
  employeeMap.insert({"Employee7", 7});

  cout << "DisplayEmp(for loop) : " << endl;
  std::map<string, int>::iterator myMapItr;
  for(myMapItr=employeeMap.begin();myMapItr!=employeeMap.end(); ++myMapItr)
    if(myMapItr->second < 5)
      cout << "\t" << myMapItr->first << endl;

  cout << "DisplayEmp(for_each) : " << endl;
  std::for_each(employeeMap.begin(), employeeMap.end(), DisplayEmp);

}

//##################################################################################################StringTest

int StringTest ()
{
  std::string inputStr ("Please, replace the vowels in this sentence by asterisks.");

  std::string tempStr1;
  std::string tempStr2;
  std::string tempStr3;
  std::string tempStr4;
  std::string tempStr5;

  vector<string> outputVec1;
  vector<string> outputVec2;
  vector<string> outputVec3;
  vector<string> outputVec4;
  vector<string> outputVec5;

  std::size_t pos1, pos2;
  pos1 = pos2 = 0;

  pos2 = inputStr.find_first_of(" ", pos1);

  while (pos2!=std::string::npos)
  {
    tempStr1 = inputStr.c_str();//OK
    tempStr2 = inputStr.substr(pos1,pos2-pos1);//OK

    //error: cannot convert ‘std::string’ {aka ‘std::__cxx11::basic_string<char>’}
    //to ‘char*’ - tempStr3
    //inputStr.copy(tempStr3,pos1,pos2-pos1); //FAIL

    //error: ‘std::string’ {aka ‘class std::__cxx11::basic_string<char>’}
    //has no member named ‘get’
    //tempStr4 = inputStr.get(pos1,pos2-pos1);//FAIL

    tempStr5 = inputStr.data();


    outputVec1.push_back(tempStr1);
    outputVec2.push_back(tempStr2);
    //outputVec3.push_back(tempStr3);
    //outputVec4.push_back(tempStr4);
    outputVec5.push_back(tempStr5);

    pos1 = pos2+1;
    pos2 = inputStr.find_first_of(" ", pos1);
  }

  tempStr1 = inputStr.c_str();//OK
  tempStr2 = inputStr.substr(pos1,pos2-pos1);//OK
  //inputStr.copy(tempStr3,pos1,pos2-pos1); //FAIL
  //tempStr4 = inputStr.get(pos1,pos2-pos1);
  tempStr5 = inputStr.data();

  //outputVec1.push_back(tempStr1);//Prints complete string
  outputVec2.push_back(tempStr2);
  //outputVec3.push_back(tempStr3);
  //outputVec4.push_back(tempStr4);
  //outputVec5.push_back(tempStr5);//Prints complete string

  auto PrintVector = [](const std::vector<string>& myVec)->void
  {
    for(auto word : myVec)
      cout << word << endl;
  };

  //cout << "outputVec1(c_str) = " << endl;
  //PrintVector(outputVec1);
  cout << "outputVec2(inputStr.substr(pos1,pos2-pos1)) = " << endl;
  PrintVector(outputVec2);
  //PrintVector(outputVec3);
  //PrintVector(outputVec4);
  //cout << "outputVec5(inputStr.data()) = " << endl;
  //PrintVector(outputVec5);

  return 0;
}

//##################################################################################################LockTest

std::mutex myMutex1, myMutex2;

void WorkerThread1()
{
  std::cout << "WorkerThread1 - Entered...\n";
  myMutex1.lock();
  std::cout << "WorkerThread1 - myMutex1 Locked...\n";
  myMutex2.lock();
  std::cout << "WorkerThread1 - myMutex2 Locked...\n";
  myMutex1.unlock();
  std::cout << "WorkerThread1 - myMutex1 UnLocked...\n";
  myMutex2.unlock();
  std::cout << "WorkerThread1 - myMutex2 UnLocked...\n";
}

void WorkerThread2 ()
{
  std::cout << "WorkerThread2 - Entered(Sleep 5 seconds)...\n";
  std::this_thread::sleep_for (std::chrono::seconds(5));
  std::cout << "WorkerThread2 - Exited 5s sleep...try_lock...\n";
  myMutex2.lock();
  int tryLock = try_lock(myMutex1, myMutex2);
  std::cout << "WorkerThread2 - try_lock result = " << tryLock << "\n";

  if (tryLock == -1) {
    std::cout << "WorkerThread2\n";
    myMutex1.unlock();
    myMutex2.unlock();
  }
  else
  {
    std::cout << "[WorkerThread2 failed : mutex " << (tryLock?"myMutex2":"myMutex1") << " FAILED!!!]\n";
  }
}

int LockTest ()
{
  std::unique_lock<std::mutex> uniqueLock1 (myMutex1);
  std::unique_lock<std::mutex> uniqueLock2 (myMutex2);

  std::thread myThread1 (WorkerThread1);
  std::thread myThread2 (WorkerThread2);

  myThread1.join();
  myThread2.join();

  return 0;
}

//##################################################################################################LambdaTest

void LambdaTest()
{

  int myInt = 7;
  char myChar = 'a';

  //Without mutable, lambda cannot modify variables passed by value(myInt)
  //Variables passed by value are read only - Default capture is ByValue
  [=,&myChar]() mutable
  {
    myInt++;
    myChar = 'b';
    std::cout << "myInt: " << myInt << " myChar = " << myChar << '\n';
  }();

  std::cout << "myInt: " << myInt << " myChar = " << myChar << '\n';

  auto lambdaSumStrlenVector  = [](size_t sum, const std::string& str){ return sum + str.size(); };
  auto lambdaSumIntVector     = [](size_t sum, const int& num){ return sum + num; };

  std::vector<string> strVector = {"abc", "def", "ghi"};
  std::vector<int>    intVector = {100, 200, 300};

  size_t totalSize1 = std::accumulate(strVector.begin(), strVector.end(), 0, lambdaSumStrlenVector);
  size_t totalSize2 = std::accumulate(intVector.begin(), intVector.end(), 0, lambdaSumIntVector);

  cout << "TotalSize(STRLEN) = " << totalSize1 << endl;
  cout << "TotalSize(INT)    = " << totalSize2 << endl;

  auto f = []()->int
  {
    static int i = 1;
    return i++;
  };

  std::vector<int> v(5);
  std::generate(v.begin(), v.end(), f);

  std::cout << "v: ";
  for (auto iv: v) {
      std::cout << iv << " ";
  }
  std::cout << "\n";

  // Initialize with default values 0,1,2,3,4 from a lambda function
  // Equivalent to std::iota(v.begin(), v.end(), 0);
  std::generate(v.begin(), v.end(), [n = 0] () mutable { return n++; });

  std::cout << "v: ";
  for (auto iv: v) {
      std::cout << iv << " ";
  }
  std::cout << "\n";
}

//##################################################################################################FuncPointerTest

void Func1()
{
    cout <<"FuncPointerTest - Func1" << endl;
};

void Func2()
{
    cout <<"FuncPointerTest - Func2" << endl;
};

void Func3()
{
    cout <<"FuncPointerTest - Func3" << endl;
};

typedef void(*FPtr)();

void FuncPointerTest()
{

  auto FuncLambda1 = [](){
      cout <<"FuncPointerTest - FuncLambda1" << endl;
  };

  auto FuncLambda2 = [](){
      cout <<"FuncPointerTest - FuncLambda2" << endl;
  };

  auto FuncLambda3 = [](){
      cout <<"FuncPointerTest - FuncLambda3" << endl;
  };

  cout <<"Func1         = " << (void*)(Func1) << endl;
  cout <<"&Func1        = " << (void*)(&Func1) << endl;
  //cout <<"FuncLambda1   = " << static_cast<unsigned>(FuncLambda1) << endl;
  cout <<"&FuncLambda1  = " << static_cast<void*>(&FuncLambda1) << endl;

  FPtr funPtrArray1[] = {Func1,Func2,Func3};
  FPtr funPtrArray2[] = {&Func1,&Func2,&Func3};
  FPtr funPtrArrayLambda1[] = {FuncLambda1,FuncLambda2,FuncLambda3};
  //FPtr funPtrArrayLambda2[] = {&FuncLambda1,&FuncLambda2,&FuncLambda3};

  for(int i = 0 ; i < 3 ; i++)
  {
    //cout <<"******1*******" << endl;
    funPtrArray1[i](); //OK
    funPtrArray2[i]();//OK
    funPtrArrayLambda1[i]();//OK
    //funPtrArrayLambda2[i]();//NG
    //cout <<"*******2******" << endl;
    //funPtrArray[i];
    //funPtrArray2[i];
    //cout <<"******3*******" << endl;
    //&funPtrArray[i] ;
    //&funPtrArray2[i];
    //cout <<"******4*******" << endl;
    //*funPtrArray1[i]();
    //*funPtrArray2[i]();
    //cout <<"******5*******" << endl;
  }
}

//##################################################################################################UnorderedSetTest

//Step 1: Overload operator== for your type:
//Step 2: Specialize std::hash for your type:
typedef struct UnOrdTest
{
  int X;
  int Y;

/*     UnOrdTest(const UnOrdTest& other)
    {
      cout << "UnOrdTest CTOR - UnOrdTest(const UnOrdTest& other)" << endl;
        X = other.X;
        Y = other.Y;
    };
 */
    UnOrdTest& operator=(const UnOrdTest& other)
    {
        cout << "UnOrdTest::operator=" << endl;
        X = other.X;
        Y = other.Y;
        return *this;
    };

   size_t operator()(const UnOrdTest& pointToHash) const
   {
        cout << "UnOrdTest::operator()" << endl;
        size_t hash = pointToHash.X + 10 * pointToHash.Y;
        return hash;
    };

    bool operator==(const UnOrdTest& other) const
    {
        cout << "UnOrdTest::operator==" << endl;
        if ( (X == other.X) && (Y == other.Y) )
            return true;
        return false;
    };

}UnOrdTest;

struct PointClass
{
  int x;
  int y;

  PointClass()
  {
    cout << "PointClass CTOR - PointClass()" << endl;
  }//Unused

  PointClass(int x, int y)
  {
    cout << "PointClass CTOR - PointClass(int x, int y)" << endl;
    this->x = x;
    this->y = y;
  }

  bool operator==(const PointClass& otherPoint) const
  {
    cout << "PointClass::operator==" << endl;
    if (this->x == otherPoint.x && this->y == otherPoint.y) return true;
    else return false;
  }

  struct HashFunction
  {
    size_t operator()(const PointClass& point) const
    {
      cout << "PointClass::HashFunction::operator()" << endl;
      size_t xHash = std::hash<int>()(point.x);
      size_t yHash = std::hash<int>()(point.y) << 1;
      return xHash ^ yHash;
    }
  };
};

void UnorderedSetTest()
{
  cout << "UnorderedSetTest" << endl;
  std::unordered_set<PointClass, PointClass::HashFunction> points;
  std::unordered_set<UnOrdTest, UnOrdTest> unOrdTests({{1,1},{2,2},{4,4},{3,3}});

  unsigned n = points.bucket_count();
  std::cout << "points has " << n << " buckets.\n";

  cout << "UnorderedSetTest - Before (1,1)" << endl;
  points.insert(PointClass(1, 1));
  cout << "UnorderedSetTest - Before (2, 2)" << endl;
  points.insert(PointClass(2, 2));
  cout << "UnorderedSetTest - Before (1, 1)) - Duplicate!" << endl;
  points.insert(PointClass(1, 1)); // notice this is a duplicate
  cout << "UnorderedSetTest - Before (2, 2) - Duplicate!" << endl;
  points.insert(PointClass(2, 2)); // notice this is a duplicate
  cout << "UnorderedSetTest - Before (3, 3)" << endl;
  points.insert(PointClass(3, 3));

  std::cout << "Points: " << "\n";
  for (auto& point : points)
  {
    std::cout << "(" << point.x << ", " << point.y << ")" << "\n";
  }

  std::cout << "UnOrdTests: " << "\n";
  for (auto& unOrdTest : unOrdTests)
  {
    std::cout << "(" << unOrdTest.X << ", " << unOrdTest.Y << ")" << "\n";
  }
}

//##################################################################################################VariableInitTest


class X
{
  public:
  X(){cout << "X() CTOR\n";}
  static void* operator new[](std::size_t sz, bool b=false)
  {
    std::cout << "custom placement new called, b = " << b << '\n';
    return ::operator new(sz);
  }
  // custom placement delete
  static void operator delete(void* ptr, bool b)
  {
  std::cout << "custom placement delete called, b = " << b << '\n';
  ::operator delete(ptr);
  }

/*  void operator delete[](void* ptr)
  {
    cout << "operator delete[]\n";
    free(ptr);
  }
   void* operator new(size_t size)
  {
    cout << "operator new - size = " << size<< "\n";
    void* ptr = malloc(size);
    return ptr;
  }

  void* operator new[](size_t size)
  {
    cout << "operator new[] - size = " << size<< "\n";
    void* ptr = malloc(size);
    return ptr;
  }
  void operator delete(void* ptr)
  {
    cout << "operator delete\n";
    free(ptr);
  }
*/

};

void VariableInitTest()
{
    X x[10];
    X *xPtr = new X[10];
    X *xPtr1 = new(true) X[10];
    char   x1[12]{};
    int    x2();
    int    *px3{};
    double x4 = {};
    //int x5{5.0};//Error: narrowing conversion of '5.0e+0' from 'double' to 'int' inside { }

    cout << "x1 = " << x1 << endl;
    cout << "&x1 = " << &x1 << endl;
    cout << "*x1 = " << *x1 << endl;
    cout << "x2 = " << x2 << endl;
    cout << "px3 = " << px3 << endl;
    cout << "x4 = " << x4 << endl;
    //cout << "x5 = " << x5 << endl;
    delete[] xPtr;
    delete[] xPtr1;
}

//##################################################################################################SmartPtrTest
int SmartPtrTest()
{
    std::shared_ptr<int> sp0(new int(5));
    std::weak_ptr<int> wp0(sp0);
    std::weak_ptr<int>::element_type val = *wp0.lock();

    std::cout << "*wp0.lock() == " << val << std::endl;

    std::cout << "*sp0 == " << *sp0 << std::endl;

    std::weak_ptr<int> wp;

    {
        std::shared_ptr<int> sp(new int(10));
        wp = sp;
        std::cout << "wp.expired() == " << std::boolalpha
            << wp.expired() << std::endl;
        std::cout << "*wp.lock() == " << *wp.lock() << std::endl;
    }

    std::cout << "wp0.expired() (Before Reset) == " << std::boolalpha
        << wp0.expired() << std::endl;
    wp0.reset();
    std::cout << "wp0.expired() (After Reset) == " << std::boolalpha
        << wp0.expired() << std::endl;

    // check expired after sp is destroyed
    std::cout << "wp.expired() == " << std::boolalpha
        << wp.expired() << std::endl;
    std::cout << "(bool)wp.lock() == " << std::boolalpha
        << (bool)wp.lock() << std::endl;

    return (0);
}
//##################################################################################################ConversionCTORTest
class ConversionCTOR
{
private:
    double real;
    double imag;

public:
    // Default constructor
    ConversionCTOR(double r = 0.0, double i = 0.0) : real(r), imag(i)
    {
      std::cout << "ConversionCTOR(" << r << "," << i << ") called!!!" << std::endl;
    }

    // A method to compare two ConversionCTOR numbers
    bool operator == (ConversionCTOR rhs)
    {
      std::cout << "operator == called!!!" << std::endl;
      return (real == rhs.real && imag == rhs.imag)? true : false;
    }

    friend ostream& operator<< (ostream& out, const ConversionCTOR &myData)
    {
      out << "ConversionCTOR:(" << (myData.real) << "," << (myData.imag) << ")" << std::endl;
      return out;
    }
};

int ConversionCTORTest()
{
    // a ConversionCTOR object
    ConversionCTOR com1(3.0, 5.0);
    ConversionCTOR com2 = 3.0;

    if (com2 == 3.0)
       cout << "Same";
    else
       cout << "Not Same";
     return 0;
}
//##################################################################################################OverLoadTest

class Over {
public:
   Over() { cout << "Over default constructor\n"; }
   Over( Over &o ) { cout << "Over& constructor\n"; }
   Over( const Over &co ) { cout << "const Over& constructor\n"; }
   Over( volatile Over &vo ) { cout << "volatile Over& constructor\n"; }

   void Test(){cout << "Over::Test()\n";};
   void Test() const {cout << "Over::Test() const\n";};
   void Test() volatile {cout << "Over::Test() volatile\n";};
};

void OverLoadTest() {
   Over o1;            // Calls default constructor.
   Over o2( o1 );      // Calls Over( Over& ).
   o2.Test();
   const Over o3;      // Calls default constructor.
   Over o4( o3 );      // Calls Over( const Over& ).
   o3.Test();
   volatile Over o5;   // Calls default constructor.
   Over o6( o5 );      // Calls Over( volatile Over& ).
   o5.Test();
}
//##################################################################################################LinkedListTest

template<typename T>
class LinkedList
{
  public:
  LinkedList():head(nullptr)
  {
    cout << "LinkedList() CTOR\n";
  }

  void Insert(T data)
  {
    Node* tempNode = nullptr;
    cout << "LinkedList::Insert()\n";

    if(head != nullptr)
    {
      tempNode = head;
      while(tempNode->nextNode != nullptr)
        tempNode = tempNode->nextNode;

      tempNode->nextNode            = new Node();
      tempNode->nextNode->nodeData  = data;
      tempNode->nextNode->nextNode  = nullptr;
    }
    else
    {
      head            = new Node();
      head->nodeData  = data;
      head->nextNode  = nullptr;
    }
  }

  void Display()
  {
    if(head != nullptr)
    {
      Node* tempNode = head;
      cout << "LinkedList :";

      do
      {
        cout << "[" << tempNode->nodeData << "]";
        tempNode = tempNode->nextNode;
      }while(tempNode != nullptr);

      cout << endl;
    }
    else
    {
      cout << "LinkedList is EMPTY!!!\n";
    }
  }

private:
  struct Node
  {
    T nodeData;
    Node* nextNode;
   };
   Node* head;
};

void LinkedListTest()
{
    LinkedList<int>* lList = new LinkedList<int>();

    lList->Insert(10);
    lList->Insert(20);
    lList->Insert(30);
    lList->Insert(40);
    lList->Insert(50);

    lList->Display();

    delete lList;
}

//##################################################################################################ArrayAccessTest

//Indirection (*)           This operator is used to get the value from the pointed address.
//Reference operator (&)	This operator is used to get the address of the variable or pointer.
//Assignment (=)            You can assign the value to the pointer or value to the address which is pointed by the pointer.
//Addition (+)              You can add integer value to the pointer to point the different memory locations.
//Subtraction (-)           You can subtract the integer value from the pointer to point the different memory locations.
//comparison (==, !=, <, >,
//            <=, and >=)	T cuhis operation is valid only between two pointers that point to the same array.
//Incrementing (++)         You can use increment operators (pre and post) with the pointer.
//Decrementing (–)          You can use decrement operators (pre and post) with the pointer.

void ArrayAccessTest()
{
    int r1, r2, r3, r4, r5;
    r1 = r2 = r3 = r4 = r5 = 0;
    int arr[5]      = { 2,4,6 };
    int* p = arr;
    r1 = *(arr + 2);
    //r2 = *arr[2];//error: invalid type argument of unary ‘*’ (have ‘int’)
    r2 = *(&arr[2]);
    r3 = *(arr + *p);
    r4 = p[2];
    r5 = (long int)(p+2);

    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "r3 = " << r3 << endl;
    cout << "r4 = " << r4 << endl;
    cout << "r5 = " << r5 << endl;
}
//##################################################################################################For_Each_Impl_Test
template<class InputIterator, class Function>
void FOR_EACH(InputIterator first, InputIterator last, Function fn)
{
  while (first!=last) {
    fn (*first);
    ++first;
  }
  //return fn;      // or, since C++11: return move(fn);
}

class MyAdd
{
public:
  void operator() (int x)
  {
    std::cout << "x = " << x <<std::endl;
  }

};

typedef std::function<void(int)> Function;
Function dispFn = MyAdd();

void For_Each_Impl_Test()
{
  std::vector<int> myVec{1,2,3,4,9,8,7,6};
  FOR_EACH(begin(myVec), end(myVec), dispFn);
  FOR_EACH(begin(myVec), end(myVec), std::bind(MyAdd(), std::placeholders::_1));
}

//##################################################################################################IteratotTraitsTest
template<class BidirIt>
void my_reverse(BidirIt first, BidirIt last)
{
    typename std::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    --n;
    while(n > 0) {
        typename std::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
        n -= 2;
    }
}

void IteratotTraitsTest()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    my_reverse(v.begin(), v.end());
    for (int n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    std::list<int> l{1, 2, 3, 4, 5};
    my_reverse(l.begin(), l.end());
    for (auto n : l) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    int a[] = {1, 2, 3, 4, 5};
    my_reverse(a, a+5);
    for (int i=0; i<5; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';

//    std::istreambuf_iterator<char> i1(std::cin), i2;
//    my_reverse(i1, i2); // compilation error

}

//##################################################################################################STD_Accumulate_Test
int AccumulateFn (int x, int y)
{
    std::cout << "\nmyfunction : x = " << x << ", y = " << y << std::endl;
    return x+2*y;
}
struct AccumulateFunctor {
	int operator()(int x, int y) {return x+3*y;}
} myobject;

int STD_Accumulate_Test () {
  int init = 100;
  int numbers[] = {10,20,30};

  std::cout << "using default accumulate: ";
  std::cout << std::accumulate(numbers,numbers+3,init);
  std::cout << '\n';

  std::cout << "using functional's minus: ";
  std::cout << std::accumulate (numbers, numbers+3, init, std::minus<int>());
  std::cout << '\n';

  std::cout << "using AccumulateFn: ";
  std::cout << std::accumulate (numbers, numbers+3, init, AccumulateFn);
  std::cout << '\n';

  std::cout << "using AccumulateFunctor: ";
  std::cout << std::accumulate (numbers, numbers+3, init, AccumulateFunctor());
  std::cout << '\n';

  return 0;
}

void PrintBinary(int x)
{
  

}
void MacroTests(void)
{
  int a = 3, b = 8;
  std::cout << "a in Binary : " << std::bitset<8>(a) << std::endl;
  std::cout << "b in Binary : " << std::bitset<8>(b) << std::endl;
  int c = a^b;
  int d = c^a;
  int e = d^b;
  std::cout << "a^b = " << std::bitset<8>(c)  << std::endl;
  std::cout << "a^b^a = " << std::bitset<8>(d)  << std::endl;
  std::cout << "a^b^a^b = " << std::bitset<8>(e)  << std::endl;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-------------MAIN
int main()
{

  //ConstMemberinClassTest();
  //ForEachTest();
  //StringTest();
  //FuncPointerTest();
  //LambdaTest();
  //UnorderedSetTest();
  //VariableInitTest();
  //LinkedListTest();
  //LockTest();
  //OverLoadTest();
  //SmartPtrTest();
  //ConversionCTORTest();
  //For_Each_Impl_Test();
  //STD_Accumulate_Test();
  //IteratotTraitsTest();
  //ConstructorTests();
  //VariadicTemplateTests();
  //ThreadTests();
  MacroTests();
}

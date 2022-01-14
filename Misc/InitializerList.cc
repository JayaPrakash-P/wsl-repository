#include <iostream>

using namespace std;

class A
{
  public:
    A()
    {
        cout << "A - Default CTOR called...\n";
    }
    ~A()
    {
        cout << "A - DTOR called...\n";
    }
    A(const A& a)
    {
        cout << "A - Copy CTOR called...\n";
        *this = a;
    }
    A(A&& a)
    {
        cout << "A - Move CTOR called...\n";
        *this = std::move(a);
    }
    A& operator=(const A& a)
    {
        cout << "A - Copy assignment operator called...\n";
        return *this;
    }
    A& operator=(A&& a)
    {
        cout << "A - Move assignment operator called...\n";
        return *this;
    }
};

class B
{
  public:
    B()
    {
        cout << "B - Default CTOR called...\n";
    }
    ~B()
    {
        cout << "B DTOR called...\n";
    }
    B(A& a, A& b):bAFast(a) //Only Copy CTOR of A() while constructing B - No assignment operator. Imp. perf
    {
        cout << "B - CTOR called...\n";
        bASlow = a; //Default CTOR of A() while constructing B followed by assignment operator here
    }
    B(const B& b)
    {
        cout << "B - Copy CTOR called...\n";
        *this = b;
    }
    B(B&& b)
    {
        cout << "B - Move CTOR called...\n";
        *this = std::move(b);
    }
    B& operator=(const B& b)
    {
        cout << "B - Copy assignment operator called...\n";
        return *this;
    }
    B& operator=(B&& b)
    {
        cout << "B - Move assignment operator called...\n";
        return *this;
    }
private:
    A bAFast;
    A bASlow;
};

int main()
{
    A a1,a2;
    cout << "*************************\n";
    B b(a1, a2);
    cout << "*************************\n";

    return 0;
}
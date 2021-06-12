#include<iostream>

class MemberBase
{
public:

    int memBaseInt;

    MemberBase(int x = 1) : memBaseInt(x)
    {
        std::cout << "MemberBase - CTOR\n";
    }

    ~MemberBase()
    {
        std::cout << "MemberBase - DTOR\n";
    }

    friend std::ostream& operator<<(std::ostream&, const MemberBase&);
};

std::ostream& operator<<(std::ostream& outs, const MemberBase& memberBase)
{
    outs << "MemberBase - memBaseInt = " << (memberBase.memBaseInt) << "\n";
    return outs;
}

class MemberDerived
{
public:

    int memDerInt;

    MemberDerived(int x = 2) : memDerInt(x)
    {
        std::cout << "MemberDerived - CTOR\n";
    }

    ~MemberDerived()
    {
        std::cout << "MemberDerived - DTOR\n";
    }

    friend std::ostream& operator<<(std::ostream&, const MemberDerived&);
};

std::ostream& operator<<(std::ostream& outs, const MemberDerived& memberDer)
{
    outs << "MemberDerived - memDerInt = " << (memberDer.memDerInt) << "\n";
    return outs;
}

class Base
{
public:

    MemberBase memberBase;
    Base(int x) : memberBase(x)
    {
        std::cout << "Base - CTOR\n";
    }

    ~Base()
    {
        std::cout << "Base - DTOR\n";
    }

};

class Derived : public Base
{
public:
    MemberBase memberBase;
    MemberDerived memberDer;

    Derived(int x) : Base(x), memberDer(x), memberBase(5555)
    {
        std::cout << "Derived - CTOR\n";
    }

    ~Derived()
    {
        std::cout << "Derived - DTOR\n";
    }
};

void ConstructorTests()
{
    //std::cout << "\n************BASE*************\n";
    //Base *basePtr   = new Base(1000);
    //std::cout <<"\nbasePtr->memberBase = " << basePtr->memberBase << std::endl;
    std::cout << "\n***********DERIVED***********\n";
    Derived *derPtr = new Derived(2000);
    std::cout <<"\nderPtr->memberBase = " << derPtr->memberBase << std::endl;
    std::cout <<"\nderPtr->Base::memberBase = " << derPtr->Base::memberBase << std::endl;
    std::cout << "\n*****************************\n";

    //delete basePtr;
    delete derPtr;
}



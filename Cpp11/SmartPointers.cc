#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

class Test
{
    char* className = nullptr;

public:
    Test(const char* name)
    {
        if (name != nullptr)
        {
            size_t nameLen = strlen(name);
            className = new char[nameLen + 1];
            std::memset(className, 0, nameLen);
            std::memcpy(className,name,nameLen);
            className[nameLen] = '\0';
        }
        else
            className = nullptr;
        cout << "Test()" << endl; 
    }

    friend ostream& operator<<(ostream& out, const Test& test)
    {
        out << "ClassName = " << test.className << endl;
        return cout;
    }

    ~Test()
    {
        if(className != nullptr)
        {
            delete[] className;
        }
        cout << "~Test()" << endl; 
    }
};

int main()
{
    const char *src = "123456789";
    shared_ptr<Test> testPtr1, testPtr2;
    {
        testPtr1 = make_shared<Test>(src);
        testPtr1.
        cout << *testPtr1;
        testPtr2 = testPtr1;
    }
    cout << *testPtr2;

    return 0;

}
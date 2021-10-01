#include<thread>
#include<mutex>
#include<iostream>
#include<chrono>
#include<cstdlib>

#include<pthread.h>

using std::cout;
using std::endl;

std::mutex iomutex;

struct Static {
    ~Static()
    {
        std::cout << "Static DTOR\n";
    }
};

struct Local {
    ~Local()
    {
        std::cout << "Local DTOR\n";
    }
};

Static static_variable; // DTOR of this object *will* be called on exit

void ThreadFunction1(int n)
{
    cout << "ThreadFunction1!!!\n";
    cout << "ThreadFunction1 : Sleeping for 5s...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    cout << "ThreadFunction1 : Resumed...\n";

    sched_param sch;
    int policy;
    pthread_getschedparam(pthread_self(), &policy, &sch);
    std::lock_guard<std::mutex> lk(iomutex);
    std::cout << "Thread " << n << " is executing at priority "
              << sch.sched_priority << '\n';

}

void ExitHandlerFn(void)
{
    cout << "ExitHandlerFn called...\n";
}

void ThreadFunction2(int &n)
{
    cout << "ThreadFunction2!!!\n";
    n = 22;
}

class ThreadTest
{
public:
    void ThreadFunction(int n)
    {
        cout << "ThreadTest::ThreadFunction!!!\n";
    }
    void operator()()
    {
        cout << "ThreadTest::operator()!!!\n";
    }
    void operator()(int &n)
    {
        cout << "ThreadTest::operator(int&)!!!\n";
        n = 44;
    }
};

void ThreadTests()
{
    std::cout << "Thread Tests!!!\n";

    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";

    std::atexit(ExitHandlerFn);

    int n1 = 10, n2 = 20, n3 = 30, n4 = 40;
    ThreadTest t1, t2;
    Local local_variable;// DTOR of this object *will NOT* be called on exit

    std::thread threadObj; //Doesn't represent a thread
    std::thread thread1(ThreadFunction1, n1);
    std::thread thread2(ThreadFunction2, std::ref(n2));
    std::thread thread3(&ThreadTest::ThreadFunction, t1, n3);
    std::thread thread4(t2, std::ref(n4));
    std::thread thread5(t2);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();

    cout << "Main Thread : n1 = " << n1 << ", n2 = " << n2
         << ", n3 = " << n3 << ", n4 = " << n4 << endl;

    std::exit(EXIT_SUCCESS);
}

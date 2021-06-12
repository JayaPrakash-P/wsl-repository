#include "ThreadPoolImpl.h"

ThreadPool::ThreadPool(unsigned int noOfThreads)
    : noOfThreads(noOfThreads)
{
    std::cout << "Constructing ThreadPool with " << noOfThreads << " threads\n";

    threadList.reserve(noOfThreads);

    for(auto i = 1 ; i <= noOfThreads ; ++i)
    {
        threadList.emplace_back(std::make_unique<Thread>(i));
    }
   
    for(auto i = 0 ; i < noOfThreads ; i+=3)
    {
        threadList[i]->Activate();
    }
}

ThreadPool::~ThreadPool()
{
    std::cout << "ThreadPoolImpl - DTOR\n";
}

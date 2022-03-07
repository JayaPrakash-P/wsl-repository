#ifndef THREADPOOLIMPL_H
#define THREADPOOLIMPL_H

#include<iostream>
#include<memory>
#include<deque>
#include<queue>
#include<functional>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<cassert>

//#include "ThreadImpl.h"

typedef void (*Job)(void);

template <typename T>
class Singleton
{
public:
    Singleton(const Singleton&)             = delete;
    Singleton(Singleton&&)                  = delete;
    Singleton& operator= (const Singleton&) = delete;
    Singleton& operator= (Singleton&&)      = delete;
    
protected:
    Singleton();
};

class ThreadPool
{
public:

    static ThreadPool& GetInstance()
    {
        static ThreadPool myInstance;
        return myInstance;
    }
    unsigned int GetNoOfThreads() { return noOfThreads; }
    
    void SpawnThreads(unsigned int threadCount = std::thread::hardware_concurrency());
    void AssignWork(Job action);

private:
    ThreadPool();
    ThreadPool(const ThreadPool& other)             = delete;
    ThreadPool(ThreadPool&& other)                  = delete;
    ThreadPool& operator=(const ThreadPool& other)  = delete;
    ThreadPool& operator=(ThreadPool&& other)       = delete;
    ~ThreadPool();
    
    unsigned int noOfThreads;
    
    using ThreadContainer = std::deque< std::unique_ptr<std::thread> >;
    ThreadContainer threadPool;
    
    std::queue<Job> jobQueue;
    bool keepRunning = false;
    
    std::mutex mtxJobQueue;
    std::condition_variable condActivateJob;
    
    void Run(int i);
};

#endif // THREADPOOLIMPL_H

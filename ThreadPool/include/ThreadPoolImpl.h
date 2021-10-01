#ifndef THREADPOOLIMPL_H
#define THREADPOOLIMPL_H

#include<iostream>
#include<memory>
#include<vector>
#include<queue>
#include<functional>
#include<thread>
#include<mutex>
#include<condition_variable>

//#include "ThreadImpl.h"

typedef void (*Job)(void);

class ThreadPool
{
    public:
        explicit ThreadPool(unsigned int noOfThreads = 10);
        virtual ~ThreadPool();

        unsigned int GetNoOfThreads() { return noOfThreads; }
        void SetNoOfThreads(unsigned int val) { noOfThreads = val; }

        void Init();
        void AssignWork(Job action);


    private:
        unsigned int noOfThreads;

        //using ThreadPtr = std::unique_ptr<Thread>;
        using ThreadPtr = std::unique_ptr<std::thread>;
        std::vector<ThreadPtr> threadPtrList;
        std::queue<Job> jobQueue;
        bool keepRunning = false;

        std::mutex mtxJobQueue;
        std::condition_variable condActivateJob;



        void Start(int i);

        ThreadPool(const ThreadPool& other) = delete;
        ThreadPool& operator=(const ThreadPool& other) = delete;
};

#endif // THREADPOOLIMPL_H

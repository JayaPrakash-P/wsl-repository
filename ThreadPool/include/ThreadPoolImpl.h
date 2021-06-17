#ifndef THREADPOOLIMPL_H
#define THREADPOOLIMPL_H

#include<iostream>
#include<memory>
#include<vector>

#include "ThreadImpl.h"

class ThreadPool
{
    public:
        explicit ThreadPool(unsigned int noOfThreads = 10);
        virtual ~ThreadPool();

        unsigned int GetNoOfThreads() { return noOfThreads; }
        void SetNoOfThreads(unsigned int val) { noOfThreads = val; }

    private:
        unsigned int noOfThreads;

        using ThreadPtr = std::unique_ptr<Thread>;
        std::vector<ThreadPtr> threadList;

        ThreadPool(const ThreadPool& other) = delete;
        ThreadPool& operator=(const ThreadPool& other) = delete;
};

#endif // THREADPOOLIMPL_H

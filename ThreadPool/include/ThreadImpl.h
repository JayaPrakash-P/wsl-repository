#ifndef THREADIMPL_H
#define THREADIMPL_H

#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>

class Thread
{
    public:
        Thread(unsigned int threadId);
        virtual ~Thread();

        void AddJob();

    private:
        Thread(const Thread& other)             = delete;
        Thread& operator=(const Thread& other)  = delete;

         void Start();

        std::thread myThread;
        unsigned int threadID;
        bool keepRunning;

        std::mutex mtxActivate;
        std::condition_variable condActivate;
};

#endif // THREADIMPL_H

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
        ~Thread();

        void AddJob();

    private:
        Thread(const Thread& other)             = delete;
        Thread(Thread&& other)                  = delete;
        Thread& operator=(const Thread& other)  = delete;
        Thread& operator=(Thread&& other)       = delete;

        void Run();

        std::thread             myThread;
        unsigned int            threadID;
        bool                    procesJob;
        bool                    keepRunning;

        std::mutex              mtxActivate;
        std::condition_variable condActivate;
};

#endif // THREADIMPL_H

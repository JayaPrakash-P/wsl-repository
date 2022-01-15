#include "ThreadImpl.h"

Thread::Thread(unsigned int threadId)
    : threadID(threadId), procesJob(false), keepRunning(true)
{
    std::cout << "[" << threadID << "]Constructor\n";
    myThread = std::thread(&Thread::Run, this);
}

Thread::~Thread()
{
    std::cout << "[" << threadID << "]Destructor\n";
    {
        std::lock_guard<std::mutex> lck(mtxActivate);
        keepRunning = false;
        condActivate.notify_one();
    }
    myThread.join();
    std::cout << "[" << threadID << "]Joined...\n";
}

void Thread::AddJob()
{
    std::lock_guard<std::mutex> lck(mtxActivate);
    std::cout << "[" << threadID << "]AddJob\n";
    if(keepRunning)
    {
        procesJob = true;
        condActivate.notify_one();
    }
    else
    {
      std::cout << "[" << threadID << "] ERROR - keepRunning = false\n";  
    }
}

void Thread::Run()
{
    std::cout << "[" << threadID << "]Start\n";

    while(keepRunning)
    {
        std::unique_lock<std::mutex> lck(mtxActivate);
        std::cout << "[" << threadID << "]Before condActivate.wait\n";
        condActivate.wait(lck, [this]{return (procesJob||!keepRunning);});
        std::cout << "[" << threadID << "]After condActivate.wait\n";
        if(procesJob)
        {
            //TO DO : Execute action here
            std::this_thread::sleep_for(std::chrono::seconds(5));
            std::cout << "[" << threadID << "]Job Completed\n";
            procesJob = false;
        }
    }
    std::cout << "[" << threadID << "]Exiting...\n";
}


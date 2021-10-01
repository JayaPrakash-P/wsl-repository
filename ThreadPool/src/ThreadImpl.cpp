#include "ThreadImpl.h"

Thread::Thread(unsigned int threadId)
    : threadID(threadId),
      keepRunning(true)
{
    myThread = std::thread(&Thread::Start, this);
}

Thread::~Thread()
{
    std::cout << "Thread DTOR called for Thread#" << threadID << std::endl;
    {
        std::lock_guard<std::mutex> lck(mtxActivate);
        keepRunning = false;
        condActivate.notify_one();
    }
    std::cout << "Waiting to join Thread#" << threadID << std::endl;
    myThread.join();
    std::cout << "Thread#" << threadID << " joined...\n";
}

void Thread::AddJob()
{
    std::lock_guard<std::mutex> lck(mtxActivate);
    condActivate.notify_one();
}

void Thread::Start()
{
    //std::cout << "Spawned Thread#" << threadID << std::endl;

    while(keepRunning)
    {
        {
            std::unique_lock<std::mutex> lck(mtxActivate);
            std::cout << "Thread#" << threadID << " - Before condActivate.wait\n";
            condActivate.wait(lck, [this]{return keepRunning;});
            std::cout << "Thread#" << threadID << " - After condActivate.wait\n";
            if(keepRunning)
            {
                std::cout << "Thread#" << threadID << " Activated...\n";
                std::this_thread::sleep_for(std::chrono::seconds(5));
                //Execute action
                std::cout << "Thread#" << threadID << " After sleep...\n";
            }
            else
            {
                std::cout << "Thread#" << threadID << " Exiting...\n";
            }
        }
    }
    std::cout << "Thread#" << threadID << " Exited!!!\n";
}

#include "ThreadImpl.h"

Thread::Thread(unsigned int threadId)
    : threadID(threadId),
      keepGoing(true),
      activated(false)
{
    myThread = std::thread(&Thread::Spawn, this);
}

Thread::~Thread()
{
    std::cout << "Thread DTOR called for Thread#" << threadID << std::endl;
    {
        std::lock_guard<std::mutex> lck(mtxActivate);
        keepGoing = false;
        activated = true;
        condActivate.notify_one();
    }
    std::cout << "Waiting to join Thread#" << threadID << std::endl;
    myThread.join();
    std::cout << "Thread#" << threadID << " joined...\n";
}

void Thread::Activate()
{
    std::lock_guard<std::mutex> lck(mtxActivate);
    std::cout << "Activating Thread#" << threadID << std::endl;
    activated = true;
    condActivate.notify_one();
}

void Thread::Spawn()
{
    //std::cout << "Spawned Thread#" << threadID << std::endl;

    while(keepGoing)
    {
        {
            std::unique_lock<std::mutex> lck(mtxActivate);
            std::cout << "Thread#" << threadID << " - Before condActivate.wait\n";
            condActivate.wait(lck, [this]{return activated;});
            std::cout << "Thread#" << threadID << " - After condActivate.wait\n";
            if(keepGoing)
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
            activated = false;

        }
    }
    std::cout << "Thread#" << threadID << " Exited!!!\n";
}

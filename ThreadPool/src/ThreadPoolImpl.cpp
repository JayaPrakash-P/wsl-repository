#include "ThreadPoolImpl.h"

ThreadPool::ThreadPool(unsigned int noOfThreads)
    : noOfThreads(noOfThreads),
      keepRunning(true)
{
    std::cout << "Constructing ThreadPool with " << noOfThreads << " threads\n";
    threadPtrList.reserve(noOfThreads);
}

void ThreadPool::Init()
{
    for(auto i = 1 ; i <= noOfThreads ; ++i)
    {
        threadPtrList.emplace_back(std::make_unique<std::thread>(&ThreadPool::Start, this, i));
    }
}

void ThreadPool::Start(int threadID)
{
    std::cout << "Spawned Thread#" << threadID << std::endl;

    while(keepRunning)
    {
        Job myJob;
        {
            std::unique_lock<std::mutex> lck(mtxJobQueue);
            std::cout << "Thread#" << threadID << " - Before condActivate.wait\n";
            condActivateJob.wait(lck, [this]{return ( (!jobQueue.empty()) || (!keepRunning) );});
            if(!keepRunning)
            {
                std::cout << "Thread#" << threadID << " exiting...\n";
                break;
            }

            std::cout << "Thread#" << threadID << " executing the job...\n";
            std::this_thread::sleep_for(std::chrono::seconds(5));
            myJob = jobQueue.front();
            jobQueue.pop();
        }
        myJob();
    }
    std::cout << "Thread#" << threadID << " Exited!!!\n";
}

void ThreadPool::AssignWork(Job job)
{
    std::cout << "AssignWork\n";
    std::unique_lock<std::mutex> lck(mtxJobQueue);
    jobQueue.push(job);
}

ThreadPool::~ThreadPool()
{
    std::cout << "ThreadPoolImpl - DTOR\n";
    {
        keepRunning = false;
        condActivateJob.notify_all();
    }
    std::cout << "Joining Threads..." << std::endl;
    for(auto &threadPtr : threadPtrList)
        threadPtr->join();
    std::cout << "Joined Threads..." << std::endl;
}
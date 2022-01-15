#include "ThreadPoolImpl.h"

ThreadPool::ThreadPool() : noOfThreads(0), keepRunning(true)
{
    std::cout << "Constructing ThreadPool...\n";
}

void ThreadPool::SpawnThreads(unsigned int threadCount) 
{
    //for(auto i = 1 ; i <= threadCount ; ++i)
    //    threadPool.emplace_back(std::make_unique<Thread>(i));
    for(auto i = 1 ; i <= threadCount ; ++i)
        threadPool.emplace_back(std::make_unique<std::thread>(&ThreadPool::Run, this, i));
    
    noOfThreads = threadPool.size();
    
    assert(noOfThreads == threadCount);
    
    std::cout << "Spawned " << threadCount << " Threads...\n";
}

void ThreadPool::Run(int threadID)
{
    std::cout << "Spawned Thread#" << threadID << std::endl;

    while(keepRunning)
    {
        Job myJob;
        {
            std::unique_lock<std::mutex> lck(mtxJobQueue);
            std::cout << "Thread#" << threadID << " - Waiting for job...\n";
            condActivateJob.wait(lck, [this]{return ( (!jobQueue.empty()) || (!keepRunning) );});
            if(!keepRunning)
            {
                std::cout << "Thread#" << threadID << " exiting...\n";
                break;
            }
            std::cout << "Thread#" << threadID << " executing the job...\n";
            myJob = jobQueue.front();
            jobQueue.pop();
        }
        myJob();
        std::cout << "Thread#" << threadID << " sleeping for 10 seconds...\n";
        std::this_thread::sleep_for(std::chrono::seconds(10));//For testing
    }
    std::cout << "Thread#" << threadID << " Exited!!!\n";
}

void ThreadPool::AssignWork(Job job)
{
    std::cout << "AssignWork\n";
    std::unique_lock<std::mutex> lck(mtxJobQueue);
    jobQueue.push(job);
    condActivateJob.notify_one();
}

ThreadPool::~ThreadPool()
{
    std::cout << "ThreadPoolImpl - DTOR\n";
    {
        keepRunning = false;
        condActivateJob.notify_all();
    }
    std::cout << "Joining Threads..." << std::endl;
    for(auto &threadPtr : threadPool)
        threadPtr->join();
    std::cout << "Joined Threads..." << std::endl;
}
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore
{
    unsigned long int semCount;
    std::mutex semMutex;
    std::condition_variable semCondVar;

public:
    Semaphore(unsigned long int semCount=1):semCount(semCount) {}
    ~Semaphore(){}

    void Acquire()
    {
        std::unique_lock<std::mutex> semLock(semMutex);
        semCondVar.wait(semLock, [&]{return (semCount != 0);});
        semCount--;
    }

    void Release()
    {
        std::unique_lock<std::mutex> semLock(semMutex);
        semCount++;
        semLock.unlock();
        semCondVar.notify_one();
    }
};

#endif //SEMAPHORE_H
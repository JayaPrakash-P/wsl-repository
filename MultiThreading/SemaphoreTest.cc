#include <iostream>
#include <thread>
#include <chrono>
#include "../Utilities/Semaphore.h"

Semaphore mySem{4};

void workerThread(unsigned int threadID)
{
    mySem.Acquire();
    std::cout << "workerThread#" << threadID << " executing...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    mySem.Release();
    std::cout << "workerThread#" << threadID << " exiting...\n";
}

int main()
{
    std::thread threadList[10];
    
    for(auto i = 0 ; i < 10 ; ++i)
        threadList[i] = std::thread(&workerThread, (i+1));

    for(auto &thread : threadList)
        thread.join();

    return 0;
}
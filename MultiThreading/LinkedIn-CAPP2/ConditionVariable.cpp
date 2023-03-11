#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <list>
#include "../../Utilities/Utils.h"

//CV should have an associated mutex
//  - Wait
//  - Signal (notify)
//  - Broadcast (notify_all)
//Generally, used for P[Producer-Consumer] problems
/* Example demonstrating chess moves*/

int totalMovesMutex   = 500000;
int totalMovesCondVar = 500000;

std::condition_variable myCondVar;
std::mutex moveMutex;

void CondVar_Move_Thread(int playerNumber)
{
    TimeElapsed timeElapsed(__func__);
    int waitingForMove=0;
    std::cout << "Player#" << (playerNumber+1) << " activated...\n";
    while(totalMovesCondVar > 0)
    {
        std::unique_lock<std::mutex> moveLock(moveMutex);
        if ((totalMovesCondVar%2 == playerNumber))
        {
            //std::cout << "Player#" << (playerNumber+1) << "'s turn. Moving...\n";
            totalMovesCondVar--;
            myCondVar.notify_one();
        }
        else
        {
            waitingForMove++;
            myCondVar.wait(moveLock, [&]{return (totalMovesCondVar%2 == playerNumber);});
        }
    }
    std::cout << "[CV]Player#" << (playerNumber+1) << " attempted " << waitingForMove << " times...\n";
}

void Mutex_Move_Thread(int playerNumber)
{
    TimeElapsed timeElapsed(__func__);
    int waitingForMove=0;
    std::cout << "Player#" << (playerNumber+1) << " activated...\n";
    while(totalMovesMutex > 0)
    {
        std::unique_lock<std::mutex> moveLock(moveMutex);
        if((totalMovesMutex%2 == playerNumber))
        {
            //std::cout << "Player#" << (playerNumber+1) << "'s turn. Moving...\n";
            totalMovesMutex--;
        }
        else
        {
            waitingForMove++;
        }
    }
    std::cout << "[MUTEX]Player#" << (playerNumber+1) << " attempted " << waitingForMove << " times...\n";
}

int main()
{
    std::list<std::thread> threadList;
    
    for(auto i : {0,1})
        threadList.emplace_back(std::thread(&Mutex_Move_Thread,i));

    for(auto i : {0,1})
        threadList.emplace_back(std::thread(&CondVar_Move_Thread,i));

    for(auto &thread : threadList)
        thread.join();

    return 0;
}
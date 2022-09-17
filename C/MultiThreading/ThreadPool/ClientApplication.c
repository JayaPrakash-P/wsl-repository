#include "ThreadPool.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void main()
{
    ThreadPoolParams threadPoolParams = 
    {
        .policy                 = SCHED_FIFO,
        .noOfThreads            = 8,
        .noOfSchedOtherThreads  = 0
    };

    InitializeThreadPool(threadPoolParams);

    sleep(20);
}
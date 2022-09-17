#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#define _GNU_SOURCE

typedef struct ThreadPoolParams
{
    int policy;
    //Total number of threads in pool
    int noOfThreads;
    //Number of threads to be scheduled as SCHED_OTHER
    int noOfSchedOtherThreads;
} ThreadPoolParams;

void InitializeThreadPool(ThreadPoolParams params);

#endif
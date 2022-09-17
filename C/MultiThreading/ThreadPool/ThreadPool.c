#include "ThreadPool.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct ThreadAttr
{
    pthread_t threadID;
    int threadNum;
    int threadPolicy;
    struct sched_param threadSchedParam;
} ThreadAttr;

void* StartThread(void* param);

//Globals - START
ThreadAttr **threadAttrList;
pthread_mutex_t globalMutex = PTHREAD_MUTEX_INITIALIZER;
//Globals - END
int policyList[] = {SCHED_FIFO, SCHED_RR, SCHED_OTHER, SCHED_BATCH, SCHED_IDLE, SCHED_DEADLINE};

void PrintPolicy(int policy)
{
    switch(policy)
    {
        case SCHED_FIFO:
            printf("SCHED_FIFO(%d)",SCHED_FIFO);
            break;
        case SCHED_RR:
            printf("SCHED_RR(%d)",SCHED_RR);
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER(%d)",SCHED_OTHER);
            break;
        case SCHED_BATCH:
            printf("SCHED_BATCH(%d)",SCHED_BATCH);
            break;
        case SCHED_IDLE:
            printf("SCHED_IDLE(%d)",SCHED_IDLE);
            break;
        case SCHED_DEADLINE:
            printf("SCHED_DEADLINE(%d)",SCHED_DEADLINE);
            break;
        default:
            printf("-UNKNOWN-");
            
    }
}

void DisplayPriorityRange()
{
    int noOfPolicies = sizeof(policyList)/sizeof(*policyList);
    for (int i = 0 ; i < noOfPolicies ; ++i)
    {
        int prioMin = sched_get_priority_min(policyList[i]);
        int prioMax = sched_get_priority_max(policyList[i]);
        PrintPolicy(policyList[i]);
        printf("\t: [%d] to [%d]\n", prioMin, prioMax);
    }
}

void DisplayThreadData(ThreadAttr* threadAttr)
{
  pthread_getschedparam(pthread_self(), &(threadAttr->threadPolicy), &(threadAttr->threadSchedParam));
//   printf("Thread#%d : Policy = [%d] and Priority = [%d]\n", threadAttr->threadNum,
//                                                             threadAttr->threadPolicy,
//                                                             threadAttr->threadSchedParam.sched_priority);

}

void SetThreadPriorityAndPolicy(ThreadAttr* threadAttr)
{
  int oldPolicy;
  struct sched_param oldSchedParam;
  pthread_getschedparam(pthread_self(), &oldPolicy, &oldSchedParam);
  struct sched_param sParam;

  if(threadAttr->threadPolicy == SCHED_FIFO)
    sParam.sched_priority = threadAttr->threadNum * 10;
  else
    sParam.sched_priority = 0;

  pthread_setschedparam(pthread_self(), threadAttr->threadPolicy, &sParam);
  int newPolicy;
  struct sched_param newSchedParam;
  pthread_getschedparam(pthread_self(), &newPolicy, &newSchedParam);
  printf("Thread#%d : Policy : [%d -> %d] and Priority : [%d -> %d]\n",
                threadAttr->threadNum,
                oldPolicy, newPolicy,
                oldSchedParam.sched_priority, newSchedParam.sched_priority);
}

void InitializeThreadPool(ThreadPoolParams params)
{
    // DisplayPriorityRange();

    //pthread_mutexattr_t mutexAttr;
    //pthread_mutexattr_init(&mutexAttr);
    //pthread_mutexattr_setprotocol(&mutexAttr, PTHREAD_PRIO_INHERIT);
    //pthread_mutex_init(&globalMutex, &mutexAttr);
    //pthread_mutexattr_destroy(&mutexAttr);

    pthread_attr_t threadAttr;
    threadAttrList = (ThreadAttr**)malloc(sizeof(ThreadAttr*) * (params.noOfThreads));

    for(int i = 0 ; i < (params.noOfThreads) ; ++i)
    {
        //pthread_attr_init(&threadAttr);
        //pthread_attr_setinheritsched(&threadAttr, PTHREAD_EXPLICIT_SCHED);

        threadAttrList[i] = (ThreadAttr*)malloc(sizeof(ThreadAttr));
        threadAttrList[i]->threadNum = (i+1);
        threadAttrList[i]->threadPolicy = params.policy;
        if(i < (params.noOfSchedOtherThreads))
            threadAttrList[i]->threadSchedParam.sched_priority = SCHED_OTHER;
        else
            threadAttrList[i]->threadSchedParam.sched_priority = params.policy;
        
        pthread_create(&(threadAttrList[i]->threadID), /*&threadAttr*/NULL, &StartThread, (void*)(threadAttrList[i]));

        //pthread_attr_destroy(&threadAttr);

    }
}

void* StartThread(void* param)
{
    ThreadAttr* threadAttr = (ThreadAttr*)param;

    printf("Started Thread#%d\n", threadAttr->threadNum);
    SetThreadPriorityAndPolicy(threadAttr);

    DisplayThreadData(threadAttr);
    pthread_mutex_lock(&globalMutex);
    printf("Thread#%d acquired lock\n", threadAttr->threadNum);
    sleep(2);
    pthread_mutex_unlock(&globalMutex);
    DisplayThreadData(threadAttr);
    printf("Thread#%d released lock\n", threadAttr->threadNum);
    free(threadAttr);
    threadAttr = NULL;
    pthread_exit(NULL);
}
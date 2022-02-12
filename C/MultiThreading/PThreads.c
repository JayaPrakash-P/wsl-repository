#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "PThreads.h"

#define THREADSIZE 4

void main()
{
    printf("Entering main\n");
    
    ThreadInfo threadList[THREADSIZE];

    for(int i = 0 ; i < THREADSIZE ; ++i)
    {
        sprintf(threadList[i].threadName,"Thread#%d",(i+1));
        pthread_attr_init(&threadList[i].threadAttr);
        int retVal = pthread_create(&(threadList[i].threadID), &(threadList[i].threadAttr),
                                     ThreadFunction, threadList[i].threadName);
    }

    for(int i = 0 ; i < THREADSIZE ; ++i)
    {
        int retVal = pthread_join((threadList[i].threadID),NULL);
    }
    printf("Exiting main\n");
}

void* ThreadFunction(void* threadParam_)
{
    const char* threadParam = (char*)threadParam_;
    printf("ThreadFunction[%s] - Sleeping for 5s...\n", threadParam);
    sleep(5);
    printf("ThreadFunction[%s] - Exiting\n", threadParam);
    return NULL;
}



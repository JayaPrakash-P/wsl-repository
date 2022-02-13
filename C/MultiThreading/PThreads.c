#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "PThreads.h"

#include <threads.h>

static int globalSum = 0;

void main(int argc, char * argv[])
{
    if(argc > 1)
    {
        int opt;
        while( (opt = getopt(argc, argv, "t:d:")) != -1)
        {
            switch(opt)
            {
                case 't':
                    maxThreads = atoi(optarg);
                    printf("maxThreads = %d\n",maxThreads);
                    break;
                case 'd':
                    dataSize = atoi(optarg);
                    printf("dataSize = %d\n",dataSize);
                    break;
                default:
                    printf("Invalid argument : %c\n",(char)opt);
                    printf("Usage : %s -t <NO OF THREADS> -d <DATA SIZE>\n",argv[1]);
            }
        };
    }

    //SleepAndExit();

    randomData = (int*)calloc(sizeof(int),dataSize);
    GenerateRandomData(randomData);
    printf("MainRandomData : ");
    DisplayRandomData(randomData); 
    CountAndExit();
    
    SumRandomData(randomData);

    free(randomData);

    printf("Exiting main\n");
}

void SleepAndExit()
{
    ThreadInfo *threadList = (ThreadInfo*)calloc(sizeof(ThreadInfo), maxThreads);
    for(int i = 0 ; i < maxThreads ; ++i)
    {
        sprintf(threadList[i].threadName,"Thread#%d",(i+1));
        pthread_attr_init(&threadList[i].threadAttr);
        int retVal = pthread_create(&(threadList[i].threadID), &(threadList[i].threadAttr),
                                     SleepFunction, threadList[i].threadName);
    }

    for(int i = 0 ; i < maxThreads ; ++i)
    {
        int retVal = pthread_join((threadList[i].threadID),NULL);
    }
    free(threadList);
}

void CountAndExit()
{
    ThreadInfo *threadList = (ThreadInfo*)calloc(sizeof(ThreadInfo), maxThreads);
    CountParam *countParam = (CountParam*)calloc(sizeof(CountParam), maxThreads);
    int localSum = 0;

    for(int i = 0 ; i < maxThreads ; ++i)
    {
        pthread_attr_init(&threadList[i].threadAttr);
        countParam[i].threadIndex = i;
        countParam[i].countData   = randomData;
        countParam[i].countResult = 0;
        int retVal = pthread_create(&(threadList[i].threadID), &(threadList[i].threadAttr), CountFunction, &countParam[i]);
    }

    for(int i = 0 ; i < maxThreads ; ++i)
    {
        int retVal = pthread_join(threadList[i].threadID,NULL);
        localSum += countParam[i].countResult;
    }
    printf("CountAndExit - FinalLocalSum : [%d]\n", localSum);
    printf("CountAndExit - FinalGlobalSum: [%d]\n", globalSum);

    free(threadList);
    free(countParam);
}

void* SleepFunction(void* threadParam_)
{
    const char* threadParam = (char*)threadParam_;
    printf("ThreadFunction[%s] - Sleeping for 5s...\n", threadParam);
    sleep(5);
    printf("ThreadFunction[%s] - Exiting\n", threadParam);
    return NULL;
}

void* CountFunction(void* threadParam_)
{
    static thread_local int threadLocalSum = 0;
    CountParam* threadParam = (CountParam*)threadParam_;
    int startIndex = (dataSize / maxThreads) * (threadParam->threadIndex) ;
    int xFactor    = (threadParam->threadIndex) + 1;
    int endIndex   = (xFactor == maxThreads) ? dataSize:((dataSize / maxThreads) * xFactor);
    for(int i = startIndex ; i < endIndex ; ++i)
    {
        pthread_mutex_lock(&pthreadMutex);
        threadLocalSum += threadParam->countData[i];
        globalSum += threadParam->countData[i];
        pthread_mutex_unlock(&pthreadMutex);
    }
    printf("CountFunction[%d] - {%d to %d} Sum = [%d]\n", (threadParam->threadIndex + 1), startIndex, (endIndex-1), threadLocalSum);
    threadParam->countResult = threadLocalSum;
    return NULL;
}

void GenerateRandomData(int *randomData)
{
    srand(time(NULL));
    for(int i = 0 ; i < dataSize ; ++i)
        randomData[i] = rand() % dataSize;
    printf("GenerateRandomData : ");
    DisplayRandomData(randomData);
}


void DisplayRandomData(int *randomData)
{
    for(int i = 0 ; i < dataSize ; ++i)
        printf("%d ", randomData[i]);
    printf("\n");
}

void SumRandomData(int *randomData)
{
    int sum = 0;
    for(int i = 0 ; i < dataSize ; ++i)
        sum += randomData[i];
    printf("SumRandomData : [%d]\n",sum);
}

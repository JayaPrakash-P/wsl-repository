#ifndef PTHREADS_H_
#define PTHREADS_H_

static int maxThreads = 4;
static int dataSize = 100;
int *randomData = NULL;

typedef struct
{
    char threadName[100];
    pthread_t threadID;
    pthread_attr_t threadAttr;
} ThreadInfo;

typedef struct
{
    int threadIndex;
    int* countData;
    int countResult;
} CountParam;


pthread_mutex_t pthreadMutex   = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  pthreadCondVar = PTHREAD_COND_INITIALIZER;

void SleepAndExit(void);
void* SleepFunction(void*);
void CountAndExit(void);
void* CountFunction(void*);
void GenerateRandomData(int*);
void DisplayRandomData(int*);
void SumRandomData(int*);

#endif
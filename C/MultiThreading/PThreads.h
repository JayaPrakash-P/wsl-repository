void* ThreadFunction(void*);

typedef struct
{
    char threadName[100];
    pthread_t threadID;
    pthread_attr_t threadAttr;
} ThreadInfo;
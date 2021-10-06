#include <thread>
#include <iostream>

int PthreadRet[] = {0,0};

void* PThreadWorker1(void* arg)
{
  PthreadRet[0] = *( (int*) arg);
  std::cout << "PThreadWorker1 : " << PthreadRet[0]  << "\n";
  pthread_exit(&PthreadRet[0]);
}

void* PThreadWorker2(void* arg)
{
  PthreadRet[1] = *( (int*) arg);
  std::cout << "PThreadWorker2 : " << PthreadRet[1] << "\n";
  pthread_exit(&PthreadRet[1]);
}

typedef void* (*ThreadWorker) (void*);

ThreadWorker threadWorkerArray[2] = {PThreadWorker1, PThreadWorker2 };

int main(void)
{
  pthread_t t1[2];
  int threadArgs[2] = {11, 22};
  int *threadRet[2] = {0, 0};
  for(int i = 0 ; i < 2 ; ++i)
  {
    pthread_create(&t1[i], nullptr, threadWorkerArray[i], &threadArgs[i]);
  }
  
  for(int i = 0 ; i < 2 ; ++i)
  {
    pthread_join(t1[i], (void**)&threadRet[i]);
    std::cout << "PThreadWorker" << (i+) << " Returned : " << (int)*threadRet[i] << "\n";
  }
  
  return 0;
}
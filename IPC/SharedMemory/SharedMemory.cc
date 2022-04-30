#include <sys/shm.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>
#include <mutex>
#include <condition_variable>

std::mutex dataMutex;
std::condition_variable dataCV;
bool dataWritten = false;

#define SHAREDMEM_SIZE 1024
#define SHAREDMEM_PERM IPC_CREAT|0666

void SharedMemoryReader()
{
    std::cout << "Entering SharedMemoryReader()...\n";
    key_t readerKey;
    readerKey = ftok("SharedMemFile", 25);
    int readerShmID = shmget(readerKey, SHAREDMEM_SIZE, SHAREDMEM_PERM);
    if(readerShmID == -1)
    {
        std::cout << "SharedMemoryReader() - shmget() Failed : " << std::strerror(errno) << "\n";
        exit(-1);
    }
    
    std::unique_lock<std::mutex> lk(dataMutex);
    dataCV.wait(lk, []{return dataWritten;});
    char *sharedMemData = (char*)shmat(readerShmID, NULL, 0);
    std::cout << "SharedMemoryReader - Data read from shared memory : " << sharedMemData << std::endl;
    lk.unlock();
    
    shmdt(sharedMemData);
    shmctl(readerShmID,IPC_RMID,NULL);
    std::cout << "Exiting SharedMemoryReader()...\n";
}

void SharedMemoryWriter()
{
    std::cout << "Entering SharedMemoryWriter()...\n";
    key_t writerKey = ftok("SharedMemFile", 25);
    int writerShmID = shmget(writerKey, SHAREDMEM_SIZE, SHAREDMEM_PERM);
    if(writerShmID == -1)
    {
        std::cout << "SharedMemoryWriter() - shmget() Failed : " << std::strerror(errno) << "\n";
        exit(-1);
    }
    char *sharedMemData = (char*)shmat(writerShmID, NULL, 0);
    char writerData[] = "Hello from SharedMemoryWriter!!!";
    std::unique_lock<std::mutex> lk(dataMutex);
    memcpy(sharedMemData, writerData, strlen(writerData));
    std::cout << "SharedMemoryWriter - Data written into shared memory : " << sharedMemData << std::endl;
    dataWritten = true;
    lk.unlock();
    dataCV.notify_one();

    shmdt(sharedMemData);
    std::cout << "Exiting SharedMemoryWriter()...\n";
}

int main()
{
    std::cout << "Entering main()...\n";
    std::thread shmWriter(SharedMemoryWriter);
    
    std::thread shmReader(SharedMemoryReader);
    
    shmWriter.join();
    shmReader.join();
    std::cout << "Exiting main()...\n";
}
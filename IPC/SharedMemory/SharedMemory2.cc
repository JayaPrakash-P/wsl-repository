#include <iostream>
#include <thread>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

using namespace std;

const char* shmFile = "SharedMemFile";
const size_t shmSize = 4096;

void SharedMemoryClient()
{
    cout << "SharedMemoryClient : Started...\n";
    int shmFd = shm_open(shmFile, O_RDWR, 0666);
    while(shmFd < 0)
    {
        cout << "Waiting for server to come up...\n";
        sleep(1);
        shmFd = shm_open(shmFile, O_RDWR, 0666);
    }
    char* dataBuffer = (char*)mmap(0, shmSize, PROT_READ|PROT_WRITE, MAP_SHARED, shmFd, 0);

    while (true)
    {
        if (strlen(dataBuffer) > 0)
        {
            cout << "[Server->Client] : " << dataBuffer << endl;
            strcpy(dataBuffer, "");
        }
        sleep(1);
   }

   shm_unlink(shmFile);
}

void SharedMemoryServer()
{
    cout << "SharedMemoryServer : Started...\n";
    int shmFd = shm_open(shmFile, O_CREAT|O_RDWR, 0666);
    ftruncate(shmFd, shmSize);
    char* dataBuffer = (char*)mmap(0, shmSize, PROT_READ|PROT_WRITE, MAP_SHARED, shmFd, 0);
    
    for(int i = (int)'A' ; i <= (int)'Z' ; ++i)
    {
        const char data = (char)i;
        strcpy(dataBuffer, &data);
        sleep(1);
   }

   sleep(1);

   shm_unlink(shmFile);
}

int main(int argc, char **argv)
{
    bool isClient = false;
    std::thread shmThread;
    
    if(argc != 2)
    {
        cout << "Usage : " << argv[0] << " <1/2> where 1:client and 2:Server\n";
        exit(0);
    }
    else
    {
        if(atoi(argv[1]) == 1) 
            isClient = true;
    }

    if(isClient)
        shmThread = std::thread([]{SharedMemoryClient();});
    else
        shmThread = std::thread([]{SharedMemoryServer();});

    shmThread.join();
    return 0;
}

#include "ThreadPoolImpl.h"
#include <memory>
#include <unistd.h>

void Test1 ()  { std::cout << "Test JOB - 1\n";  }
void Test2 ()  { std::cout << "Test JOB - 2\n";  }
void Test3 ()  { std::cout << "Test JOB - 3\n";  }
void Test4 ()  { std::cout << "Test JOB - 4\n";  }
void Test5 ()  { std::cout << "Test JOB - 5\n";  }
void Test6 ()  { std::cout << "Test JOB - 6\n";  }
void Test7 ()  { std::cout << "Test JOB - 7\n";  }
void Test8 ()  { std::cout << "Test JOB - 8\n";  }
void Test9 ()  { std::cout << "Test JOB - 9\n";  }
void Test10()  { std::cout << "Test JOB - 10\n"; }

Job jobArray[] = {Test1,Test2,Test3,Test4,Test5,Test6,Test7,Test8,Test9,Test10};

int main()
{
    std::cout << "Entering main...\n";
    auto& threadPool = ThreadPool::GetInstance();
    threadPool.SpawnThreads();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    for(int i = 0 ; i < 10 ; ++i)
        threadPool.AssignWork(jobArray[i]);
    std::cout << "Main Exiting...\n";
    return 0;
}
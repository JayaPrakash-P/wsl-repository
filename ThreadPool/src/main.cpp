#include "ThreadPoolImpl.h"
#include <memory>

int main()
{
    std::cout << "Entering main...\n";
    std::unique_ptr<ThreadPool> threadPool = std::make_unique<ThreadPool>(10);
    threadPool->Init();
    std::cout << "Main Exiting...\n";
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}

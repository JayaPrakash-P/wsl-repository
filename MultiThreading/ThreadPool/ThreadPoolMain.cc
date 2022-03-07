#include <iostream>
#include <thread>
#include <vector>
#include <deque>
#include <chrono>
#include <future>
#include <mutex>
#include <functional>

using namespace std;
using namespace std::chrono;

using ULL = unsigned long long;
using PT_ULL  = std::packaged_task<ULL(void)>;

using TimePoint = std::chrono::time_point<high_resolution_clock>;

class LogEntryExit
{
public:
    LogEntryExit(std::string fnName_):fnName(fnName_)
    {
        entryTime = std::chrono::high_resolution_clock::now();
    }    
    ~LogEntryExit()
    {
        exitTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = duration_cast<milliseconds>(exitTime-entryTime);
        cout << "Elapsed Time[" << fnName << "] = " << elapsedTime.count() << "ms" << endl;
    }
private:
    TimePoint entryTime;
    TimePoint exitTime;
    string fnName;
};

template <typename T>
class Singleton
{
public:
    static T& GetInstance()
    {
        static T myInstance;
        return myInstance;
    }

    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

protected:
        Singleton(){};
        virtual ~Singleton(){};
};

class ThreadPool : public Singleton<ThreadPool>
{
public:
    void SetNoOfThreads(int threads)
    {
        noOfThreads = threads;
    }

    void WorkerThread(int i)
    {
        std::cout << "WorkerThread #" << i << " started...\n";
        //std::this_thread::sleep_for(std::chrono::seconds(10));
        while(!shutDown)
        {
            std::unique_lock<std::mutex> lk(taskListMut);
            taskListConVar.wait(lk, [this]{return (!taskList.empty() || shutDown);});
            if(shutDown)
                break;
            std::cout << "WorkerThread #" << i << " Executing...\n";
            auto myTask = std::move(taskList.front());
            taskList.pop_front();
            lk.unlock();
            myTask();
        }
            std::cout << "WorkerThread #" << i << " exited...\n";
    }

    void InitializeThreads()
    {
        if(noOfThreads == 0)
            noOfThreads = std::thread::hardware_concurrency();

        for(int i = 0 ; i < noOfThreads ; ++ i)
            threadList.emplace_back(&ThreadPool::WorkerThread, this, (i+1));
        std::cout << "Created " << noOfThreads << " Threads\n";
    }

    void AssignWork(PT_ULL pTask)
    {
        std::cout << "Created " << noOfThreads << " Threads\n";
        std::lock_guard<std::mutex> lk(taskListMut);
        taskList.emplace_back(std::move(pTask));
        taskListConVar.notify_one();
    }

    void ShutDown()
    {
        shutDown = true;
        taskListConVar.notify_all();
    }

private:
    ThreadPool()
    {
        std::cout << "ThreadPool - CTOR\n";
    }
    ~ThreadPool()
    {
        std::cout << "ThreadPool - DTOR\n";
        for(auto &thread : threadList)
            thread.join();
    }
    unsigned int noOfThreads = 0;
    std::vector<std::thread> threadList;
    std::deque<PT_ULL> taskList;

    //Synchronization
    std::mutex taskListMut;
    std::condition_variable taskListConVar;
    bool shutDown = false;
    friend Singleton<ThreadPool>;
};

ULL CountTask(ULL startIndex, ULL endIndex)
{
    LogEntryExit log(__func__);
    ULL lResult = 0;
    cout << "Couting from : " << startIndex << " to " << endIndex << endl;
    for(int i = startIndex ; i <= endIndex ; ++i)
        lResult += i;

    return lResult;
}
int main()
{
    LogEntryExit log(__func__);
    unsigned long long countResult = 0;
    unsigned long long sIndex = 0;
    unsigned long long maxIndex = 1000000000;
    unsigned int noOfThreads = std::thread::hardware_concurrency();
    cout << "noOfThreads = " << noOfThreads << endl;

    ULL result = 0;
    ThreadPool::GetInstance().SetNoOfThreads(noOfThreads);
    ThreadPool::GetInstance().InitializeThreads();

    std::future<ULL> resultList[noOfThreads];
    ULL indexFactor =  maxIndex/noOfThreads;
    ULL startIndex = sIndex, endIndex = indexFactor;
    for(auto i = 0 ; i < noOfThreads ; ++i)
    {
        PT_ULL countTask(std::bind(CountTask, startIndex,endIndex));
        resultList[i] = countTask.get_future();
        ThreadPool::GetInstance().AssignWork(std::move(countTask));
        startIndex = endIndex+1;
        endIndex += indexFactor;
    }
    for(auto i = 0 ; i < noOfThreads ; ++i)
        countResult += resultList[i].get();
        
    std::cout << "countResult:" << countResult << std::endl;
    ThreadPool::GetInstance().ShutDown();

}
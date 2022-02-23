#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;
using namespace chrono_literals;

using TimePoint = std::chrono::time_point<high_resolution_clock>;
//using T = unsigned long long;
using T = unsigned int;
using ULL = unsigned long long;

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

void CountThread(int startIndex, int endIndex, ULL &result)
{
    LogEntryExit log(__func__);
    ULL lResult = 0;
    cout << "Couting from : " << startIndex << " to " << endIndex << endl;
    for(int i = startIndex ; i <= endIndex ; ++i)
        lResult += i;

    result += lResult;
}

class CountFunctor
{
    public:
    void operator()(T startIndex, T endIndex, ULL &result)
    {
       CountThread (startIndex, endIndex, result);
       cout << "result = " << result << endl;
    }
    
};

void MultiThreaded(T sIndex, T maxIndex, ULL &result)
{
    LogEntryExit log(__func__);
    unsigned int noOfThreads = std::thread::hardware_concurrency();
    cout << "noOfThreads = " << noOfThreads << endl;

    std::thread threadList[noOfThreads];
    T indexFactor =  maxIndex/noOfThreads;
    T startIndex = sIndex, endIndex = indexFactor;
    for(int i = 0 ; i < noOfThreads ; ++i)
    {
        threadList[i] = std::thread(CountThread, startIndex, endIndex, std::ref(result));
        startIndex = endIndex+1;
        endIndex += indexFactor;
    }
    for(int i = 0 ; i < noOfThreads ; ++i)
        threadList[i].join();
}

void SingleThreaded(T sIndex, T maxIndex, ULL &result)
{
    LogEntryExit log(__func__);
    //FUNCTOR
    std::thread t1(CountFunctor(), sIndex, maxIndex, std::ref(result));
    t1.join();
}

int main()
{
    LogEntryExit log(__func__);
    T maxIndex = 1000000000;
    ULL result = 0;

    SingleThreaded(0,maxIndex, result);
    cout << "SingleThreaded Result = " << result << endl;
    result = 0;
    MultiThreaded(0,maxIndex, result);
    cout << "MultiThreaded Result = " << result << endl;
    return 0;
}
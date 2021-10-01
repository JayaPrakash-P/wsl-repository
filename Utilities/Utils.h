#ifndef _UTILS_H_
#define _UTILS_H_
#include <iostream>
#include <chrono>

using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;
using DurationNs = std::chrono::duration<double, std::nano>;
using DurationMs = std::chrono::duration<double, std::milli>;

enum class LogType
{
  EntryExit         = 0x01,
  EntryExitWithTime = 0x02,
  EntryExitExecTime = 0x03,
  ExecTimeOnly      = 0x04,
  All               = 0xFF
};

inline auto now()
{
    return std::chrono::high_resolution_clock::now();
}

class LogEntryExit
{
public:
    LogEntryExit(std::string p_fnName, LogType p_logType = LogType::EntryExit)
        :fnName(p_fnName), logType(p_logType)

    {
        entryTime = now();
        switch(logType)
        {
            case LogType::ExecTimeOnly:
                //Log at exit
                break;

            case LogType::EntryExit:
                std::cout << ">>>>> Entering " << fnName << std::endl;
                break;

            case LogType::EntryExitWithTime:
                 std::cout << ">>>>> Entering " << fnName << " @ " << (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) << std::endl;
                 break;

            case LogType::EntryExitExecTime:
            case LogType::All:
                std::cout << ">>>>> Entering " << fnName << " @ " << (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) << std::endl;
                break;
        }
    }
    
    ~LogEntryExit()
    {
        exitTime = now();
        switch(logType)
        {
            case LogType::EntryExit:
                std::cout << "<<<<< Exiting  " << fnName;
                break;
            case LogType::EntryExitWithTime:
                 std::cout << "<<<<< Exiting  " << fnName << " @ " << (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
                 break;
            case LogType::ExecTimeOnly:
                std::cout << fnName << " ExecTime : " << DurationNs(exitTime - entryTime).count() << " ns, "
                          << DurationMs(exitTime - entryTime).count() << " ms";
                break;
            case LogType::EntryExitExecTime:
            case LogType::All:
                std::cout << "<<<<< Exiting  " << fnName << " @ " << (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) << " - ExecTime : " 
                          << DurationNs(exitTime - entryTime).count() << " ns, " << DurationMs(exitTime - entryTime).count() << " ms";
                break;
            default:
                break;
        }
        std::cout << std::endl;
    }
private:
    std::string fnName;
    LogType logType;
    Time entryTime, exitTime;
};

#endif //_UTILS_H_
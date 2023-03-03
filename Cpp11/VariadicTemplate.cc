#include <iostream>
#include <string>

template<typename T>
T Summer(T inputData)
{
    return inputData;
}
template<typename T, typename ...Args>
T Summer(T firstData, Args ...args)
{
    return firstData + Summer(args...);
}

int main()
{
    int sumInt = Summer<>(10,20,30,40,50);
    std::string inputString[] = {"AAAA", "BBBB", "CCCC", "DDDD"};
    std::string sumString = Summer<std::string>(inputString[0],inputString[1],inputString[2],inputString[3]);
    std::cout << "sumInt = " << sumInt << std::endl;
    std::cout << "sumString = " << sumString << std::endl;
    
    return 0;
}

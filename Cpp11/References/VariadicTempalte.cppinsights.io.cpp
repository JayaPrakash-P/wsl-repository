#include <iostream>
#include <string>

template<typename T>
T Summer(T inputData)
{
  return inputData;
}


/* First instantiated from: insights.cpp:12 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int Summer<int>(int inputData)
{
  return inputData;
}
#endif


/* First instantiated from: insights.cpp:12 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::basic_string<char> Summer<std::basic_string<char> >(std::basic_string<char> inputData)
{
  return std::basic_string<char>(static_cast<std::basic_string<char> &&>(inputData));
}
#endif

template<typename T, typename ... args>
T Summer(T firstData, args... nextData)
{
  return firstData + Summer(nextData... );
}


/* First instantiated from: insights.cpp:17 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int Summer<int, int, int, int, int>(int firstData, int __nextData1, int __nextData2, int __nextData3, int __nextData4)
{
  return firstData + Summer(__nextData1, __nextData2, __nextData3, __nextData4);
}
#endif


/* First instantiated from: insights.cpp:19 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::basic_string<char> Summer<std::basic_string<char>, std::basic_string<char>, std::basic_string<char>, std::basic_string<char> >(std::basic_string<char> firstData, std::basic_string<char> __nextData1, std::basic_string<char> __nextData2, std::basic_string<char> __nextData3)
{
  return std::basic_string<char>(std::operator+(firstData, Summer(std::basic_string<char>(__nextData1), std::basic_string<char>(__nextData2), std::basic_string<char>(__nextData3))));
}
#endif


/* First instantiated from: insights.cpp:12 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int Summer<int, int, int, int>(int firstData, int __nextData1, int __nextData2, int __nextData3)
{
  return firstData + Summer(__nextData1, __nextData2, __nextData3);
}
#endif


/* First instantiated from: insights.cpp:12 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int Summer<int, int, int>(int firstData, int __nextData1, int __nextData2)
{
  return firstData + Summer(__nextData1, __nextData2);
}
#endif


/* First instantiated from: insights.cpp:12 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
int Summer<int, int>(int firstData, int __nextData1)
{
  return firstData + Summer(__nextData1);
}
#endif


/* First instantiated from: insights.cpp:12 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::basic_string<char> Summer<std::basic_string<char>, std::basic_string<char>, std::basic_string<char> >(std::basic_string<char> firstData, std::basic_string<char> __nextData1, std::basic_string<char> __nextData2)
{
  return std::basic_string<char>(std::operator+(firstData, Summer(std::basic_string<char>(__nextData1), std::basic_string<char>(__nextData2))));
}
#endif


/* First instantiated from: insights.cpp:12 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
std::basic_string<char> Summer<std::basic_string<char>, std::basic_string<char> >(std::basic_string<char> firstData, std::basic_string<char> __nextData1)
{
  return std::basic_string<char>(std::operator+(firstData, Summer(std::basic_string<char>(__nextData1))));
}
#endif


int main()
{
  int sumInt = Summer(10, 20, 30, 40, 50);
  std::basic_string<char> inputString[4] = {std::basic_string<char>(std::basic_string<char>("AAAA", std::allocator<char>())), std::basic_string<char>(std::basic_string<char>("BBBB", std::allocator<char>())), std::basic_string<char>(std::basic_string<char>("CCCC", std::allocator<char>())), std::basic_string<char>(std::basic_string<char>("DDDD", std::allocator<char>()))};
  std::basic_string<char> sumString = std::basic_string<char>(Summer<std::basic_string<char> >(std::basic_string<char>(inputString[0]), std::basic_string<char>(inputString[1]), std::basic_string<char>(inputString[2]), std::basic_string<char>(inputString[3])));
  std::operator<<(std::cout, "sumInt = ").operator<<(sumInt).operator<<(std::endl);
  std::operator<<(std::operator<<(std::cout, "sumString = "), sumString).operator<<(std::endl);
  return 0;
}


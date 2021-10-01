#include <iostream>

void log()
{
    std::cout << '\n';
}

template < typename T, typename ... Args>
void log(T first, Args ... args)
{
  std::cout << first << ' ';
  log(args...);
}

void VariadicTemplateTests()
{
    std::cout << "VariadicTemplateTests - ENTER\n";
    log(1);
    log('a', 1);
    log("ABCD", 'a',1,'b',5.5);
    std::cout << "VariadicTemplateTests - EXIT\n";
}
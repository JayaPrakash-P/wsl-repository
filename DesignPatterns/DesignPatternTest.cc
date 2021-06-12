#include <iostream>
#include "SingletonT.h"

class MySingleton : public Singleton<MySingleton>
{
public:
  void Display()
  {
    std::cout << "MySingleton::Display()\n";
  }

private:
  MySingleton(){std::cout << "MySingleton\n";};
  ~MySingleton(){std::cout << "~MySingleton\n";};

  MySingleton(const MySingleton&) = delete;
  MySingleton& operator=(const MySingleton&) = delete;

  friend class Singleton<MySingleton>;
};

int main()
{
  MySingleton::getInstance().Display();
  return 0;  
}
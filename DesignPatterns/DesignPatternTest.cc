#include <iostream>
#include "SingletonT.h"

using mySingleton = Singleton<MySingleton>;

int main()
{
  mySingleton::getInstance().Display();
  return 0;  
}
#ifndef _SINGLETON_H
#define _SINGLETON_H

#include <iostream>

template <class T>
class Singleton
{
public:
  static T& getInstance()
  {
    return T::getInstance();
  }
  
  virtual ~Singleton()
  {
    std::cout << "~Singleton()\n";
  }

protected:
  Singleton(){std::cout << "Singleton()\n";}

private:
  Singleton(const Singleton&) = delete;
  Singleton operator=(const Singleton) = delete;

};

class MySingleton : public Singleton<MySingleton>
{
public:
  void Display()
  {
    std::cout << "MySingleton::Display()\n";
  }
  static MySingleton& getInstance()
  {
     static MySingleton myInstance;
     return myInstance;
  }
private:
  MySingleton(){std::cout << "MySingleton\n";};
  ~MySingleton(){std::cout << "~MySingleton\n";};
  MySingleton(const MySingleton&) = delete;
  MySingleton& operator=(const MySingleton&) = delete;
};
#endif

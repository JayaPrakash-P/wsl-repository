#ifndef _SINGLETON_H
#define _SINGLETON_H

#include <iostream>

template <class T>
class Singleton
{
public:
  static T& getInstance()
  {
    static T instance;
    return instance;
  }
  
protected:
  Singleton()
  {
    std::cout << "Singleton()\n";
  }

  virtual ~Singleton()
  {
    std::cout << "~Singleton()\n";
  }

private:
  Singleton(const Singleton&) = delete;
  Singleton operator=(const Singleton) = delete;

};

#endif

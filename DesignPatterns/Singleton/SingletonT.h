#ifndef _SINGLETON_H
#define _SINGLETON_H

#include <iostream>

class CSingleton final
{
public:
    static CSingleton& GetInstance();
 
private:
    CSingleton() = default;
    ~CSingleton() = default;
 
    CSingleton(const CSingleton&) = delete;
    CSingleton& operator=(const CSingleton&) = delete;
    CSingleton(CSingleton&&) = delete;
    CSingleton& operator=(CSingleton&&) = delete;
};
 
CSingleton& CSingleton::GetInstance()
{
    static CSingleton instance;
    return instance;
}

template <class T>
class Singleton
{
public:
  Singleton(const Singleton&) = delete;
  Singleton operator=(const Singleton&) = delete;

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

};

#endif

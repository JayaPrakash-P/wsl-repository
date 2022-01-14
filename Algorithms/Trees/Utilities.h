#include <iostream>
#include <random>
#include <list>
#include <vector>

using namespace std;

using IntList = list<int>;
using IntVec = vector<int>;

void DisplayVec(const IntVec& myVec)
{
    cout << "Vector : [";
    for(auto data : myVec)
        cout << data << " ";
    cout << "]\n";
}

void DisplayList(const IntList& myList)
{
    cout << "List : [";
    for(auto data : myList)
        cout << data << " ";
    cout << "]\n";
}

IntList GenerateRandmomIntList(size_t listSize)
{
    IntList myList;
    random_device randomDev;
    mt19937 randomNumGen(randomDev());
    uniform_int_distribution<int> uniformDist(1,10000);

    for(int i = 0 ; i < listSize ; ++i)
    {
        int data = uniformDist(randomNumGen);
        myList.push_back(data);
    }
    DisplayList(myList);
    return myList;
}

IntVec GenerateRandmomIntVec(size_t vectSize)
{
    IntVec myVec;
    random_device randomDev;
    mt19937 randomNumGen(randomDev());
    uniform_int_distribution<int> uniformDist(1,1000);

    for(int i = 0 ; i < vectSize ; ++i)
    {
        int data = uniformDist(randomNumGen);
        myVec.push_back(data);
    }
    DisplayVec(myVec);
    return myVec;
}

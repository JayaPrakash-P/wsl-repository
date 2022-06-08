// Example program
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    std::map<char, int> indexMap;
    int start = (int)'A';
    for(int i = 1 ; i <= 26 ; ++i)
    {
        indexMap.insert({(char)start++, i});
    }

    string inputStr;
    
    while(inputStr != "QUIT")
    {
        cout << "Enter Column Name : " << endl;
        cin >> inputStr;
    
        int inputLen = inputStr.size();

        int mulFactor = 1;    
        int cellNumber = 0;
        
        while(inputLen)
        {
            cellNumber += indexMap[inputStr[inputLen-1]]*mulFactor;
            mulFactor *= 26;
            inputLen--;
        }
        
        cout << "[" << inputStr << "] ==> [" << cellNumber << "]" << endl;
    }
}

/*
A   - 1
Z   - 26
AA  - 26+1
AZ  - 26+26  26 * index[0] + index[1]
BA  - 52+1 = 26 * index[0] + index[1]
BB  - 
AAA - 703    26 * 26 * index[0] + 26*index[1] + index[2] [676 + 26 + 1]
ABA - 729    26 * 26 * index[0] + 26*index[1] + index[2] [676 + 52 + 1]
26    Z
26*26 ZZ
26

*/
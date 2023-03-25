// Example program
#include <iostream>
#include <cstring>

using namespace std;

class String
{
    char* strData;
    
public:
    explicit String(const char* inputData):strData(nullptr)
    {
        auto inputLen = strlen(inputData);
        cout << "strlen of [" << inputData << "] = " << inputLen << endl;
        strData = new char[inputLen+1];
        strcpy(strData, inputData);
        strData[inputLen+1] = 0;
    }
    
    void Reverse()
    {
        size_t inputLen = strlen(strData);
        for(auto i = 0 ; i < inputLen ; ++i)
        {
            if(i >= inputLen-i)
                break;
            else
                swap(strData[i], strData[inputLen-1-i]);
        }
    }
    
    /* operator std::string()
    {
        return std::string(strData);
    } */
    
    friend ostream& operator<< (ostream& outc, const String& inputStr)
    {
        outc << inputStr.strData;
        return outc;
    }
};

int main()
{
  char name[255];
  std::cout << "Enter String to reverse? ";
  cin.getline(name,255);
  std::cout << "IN STR  : " << name << "\n";
  String inputStr(name);
  inputStr.Reverse();
  std::cout << "OUT STR : " << inputStr << "\n";
}
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

class HRMLParser
{
public:
    HRMLParser(){}
    
    void LoadData(std::vector<string> inputData)
    {
        for(auto& line : inputData)
            ProcessLine(line);
    }
    
    void Query(const std::vector<string>& queryData)
    {
        for(auto& query : queryData)
            QueryInternal(query);  
    }

    void Display()
    {
        cout << "======================" << endl;
        for(auto& attr : attrMap)
            cout << attr.first << ":" << attr.second << endl;
        cout << "======================" << endl;
    }
private:
    std::map<string,string> attrMap;
    string currentTag;

    bool ProcessLine(const std::string& line)
    {
        int symbolIndex = 0;
        std::string tempLine = line;
        std::string::size_type linePos = tempLine.find('<');
        if(linePos == std::string::npos)
            return false;
        tempLine = tempLine.substr(linePos+1);

        linePos = tempLine.find('/');
        if(linePos != std::string::npos)
        {
            tempLine = tempLine.substr(linePos+1);
            linePos = tempLine.find('>');
            if(linePos == std::string::npos)
                return false;
            tempLine = tempLine.substr(0, linePos);
            TrimSpaces(tempLine);
            RemoveTag(tempLine);
            return true;
        }

        linePos = tempLine.find('=');
        if(linePos == std::string::npos)
        {
            linePos = tempLine.find('>');
            if(linePos == std::string::npos)
                return false;
            tempLine = tempLine.substr(0, linePos);
            TrimSpaces(tempLine);
            InsertTag(tempLine);
            return true;
        }
        else
        {
            linePos = tempLine.find(' ');
            if(linePos == std::string::npos)
            {
                linePos = tempLine.find('>');
                if(linePos == std::string::npos)
                    return false;
                else
                {
                    string tagName = tempLine.substr(0, linePos);
                    TrimSpaces(tagName);
                    InsertTag(tagName);
                    return true; 
                }
            }
            
            string tagName = tempLine.substr(0, linePos);
            TrimSpaces(tagName);
            InsertTag(tagName);
            tempLine = tempLine.substr(linePos+1);
            linePos = tempLine.find('=');
            while (linePos != std::string::npos)
            {
                string attrName = tempLine.substr(0, linePos);
                TrimSpaces(attrName);
                tempLine = tempLine.substr(linePos+1);
                linePos = tempLine.find('\"');
                if(linePos == std::string::npos)
                    return false;
                tempLine = tempLine.substr(linePos+1);
                linePos = tempLine.find('\"');
                if(linePos == std::string::npos)
                    return false;
                string attrVal = tempLine.substr(0, linePos);
                TrimSpaces(attrVal);
                InsertAttributeVal(attrName, attrVal);
                tempLine = tempLine.substr(linePos+1);
                linePos = tempLine.find('=');
            }
            symbolIndex++;
            linePos = tempLine.find('>');
            if(linePos == std::string::npos)
                return false;
            return true;
        }
    }

    void TrimSpaces(string& myStr)
    {
        while(myStr[0] == ' ')
            myStr = myStr.substr(1);
        while(myStr[myStr.length()-1] == ' ')
            myStr = myStr.substr(0, myStr.length()-1);
    }

    void InsertTag(string tagName)
    {
        if(currentTag.empty())
            currentTag = tagName;
        else
            currentTag = currentTag + "." + tagName;
    }

    void RemoveTag(string tagName)
    {
        auto tagPos = currentTag.find(tagName);
        
        if (currentTag == tagName)
            currentTag.clear();
        else if(tagPos != string::npos)
            currentTag = currentTag.substr(0, tagPos-1);
    }

    void InsertAttributeVal(string attrName, string attrValue)
    {
        attrMap.emplace(currentTag+"~"+attrName, attrValue);
    }

    void QueryInternal(const string& queryStr)
    {
        auto queryResult = attrMap.find(queryStr);
        if(queryResult != attrMap.end())
            cout << queryResult->second << endl;
        else
            cout << "Not Found!" << endl;
    }
};

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int noOfLines, noOfQueries;
    
    cin >> noOfLines >> noOfQueries;    
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    std::vector<string> inputLines, inputQueries;
    string line;
    
    for(auto i = 0 ; i < noOfLines ; ++i)
    {
        std::getline(std::cin, line);
        inputLines.emplace_back(line);
    }
    
    for(auto i = 0 ; i < noOfQueries ; ++i)
    {
        std::getline(std::cin, line);
        inputQueries.emplace_back(line);
    }
    
    HRMLParser parser;
    parser.LoadData(inputLines);
    //parser.Display();
    parser.Query(inputQueries);
    
    return 0;
}


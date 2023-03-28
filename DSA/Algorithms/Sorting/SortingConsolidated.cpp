// Example program
#include <iostream>
#include <string>
#include <string>
#include <vector>
#include <random>

using namespace std;

void Display(const vector<int> &v)
{
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void GenerateRandomData(vector<int> &v)
{
    v.clear();
    // Set up random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    // Generate a vector of 10 random integers between 1 and 100
    for (int i = 0; i < 10; ++i) {
        v.push_back(dis(gen));
    }
    
    cout << "INPUT\t\t: ";
    Display(v);
}

void BubbleSort(vector<int> &inputVec)
{
    bool sorted = true;
    for(auto i = 0 ; i < inputVec.size() - 1 ; ++i)
    {
        for(auto j = 0 ; j < (inputVec.size() - i - 1) ; ++j)
            {
                if(inputVec[j] > inputVec[j+1])
                {
                    sorted = false;
                    std::swap(inputVec[j], inputVec[j+1]);
                }
            }
        if(sorted)
            break;
    }
}

void SelectionSort(vector<int> &inputVec)
{
    int minIndex = 0;
    for(auto i = 0 ; i < inputVec.size()-1 ; ++i)
    {
        minIndex = i;
        for(auto j = i+1 ; j < inputVec.size() ; ++j)
        {
            if(inputVec[j] < inputVec[minIndex])
                minIndex = j;
        }
        
        if(minIndex != i)
            std::swap(inputVec[i], inputVec[minIndex]);
    }
}

void InsertionSort(vector<int> &inputVec)
{
    int key,j;
    for (auto i = 1; i < inputVec.size(); ++i)
    {
        key = inputVec[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are greater than key,
        to one position ahead of their current position */
        while (j >= 0 && inputVec[j] > key) {
            inputVec[j + 1] = inputVec[j];
            j = j - 1;
        }
        inputVec[j + 1] = key;
    }
}


int main()
{
    std::vector<int> inputVec;
    
    GenerateRandomData(inputVec);
    
    BubbleSort(inputVec);
    
    cout << "OUTPUT(BS)\t: ";
    Display(inputVec);
    
    GenerateRandomData(inputVec);
    
    SelectionSort(inputVec);
    
    cout << "OUTPUT(SS)\t: ";
    Display(inputVec);
    
    GenerateRandomData(inputVec);
    
    InsertionSort(inputVec);
    
    cout << "OUTPUT(IS)\t: ";
    Display(inputVec);

}
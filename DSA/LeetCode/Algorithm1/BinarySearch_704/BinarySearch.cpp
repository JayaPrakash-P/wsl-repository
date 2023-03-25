#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <climits>

using namespace std;

class BinarySearch {
public:
    int IterativeSearch1(vector<int>& nums, int target)
    {
        int low  = 0;
        int high = nums.size()-1;
        int mid  = 0;
        
        while (low <= high)
        {
            mid  = (low+high)/2; // Overflow might occur. Prefered : int mid  = (low+(high-low)/2);
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] > target)
                high = mid-1;
            else
                low = mid+1;
        }
        return -1;
    }
    
    int IterativeSearch2(vector<int>& nums, int target)
    {
        int low  = 0;
        int high = nums.size()-1;
        int mid  = 0;
        
        while (low < high)
        {
            mid = (low+high)/2;
            if(nums[mid] >= target)
                high = mid;
            else
                low = mid+1;
        }
        return ( (nums[low] == target) ? low : -1 );
    }
    
    int RecursiveSearch(vector<int>& nums, int low, int high, int target)
    {
        if(low > high)
            return -1;
        
        int mid = (low+high)/2;
        
        if(nums[mid] == target)
            return mid;
        else if(nums[mid] > target)
            return RecursiveSearch(nums, low, mid-1, target);
        else
            return RecursiveSearch(nums, mid+1, high, target);
    }
};

int main()
{
    set<int> inputSet;
    vector<int> inputArray;
    int arraySize = 10;
    
    cout << " Enter array Size : ";
    cin >> arraySize;
    
    random_device randDevice;
    mt19937 randomNumGen(randDevice());
    uniform_int_distribution<mt19937::result_type> uniformDist(-100,100);
    std::cout << "Input Random Data : ";
    char arraySeparator = '{';
    for(int i = 0 ; i < arraySize ; i++)
    {
        int randomNumber = uniformDist(randomNumGen);
        std::cout << arraySeparator << randomNumber;
        inputSet.insert(randomNumber);
        arraySeparator = ',';
    }
    std::cout << "}\nSorted Array : ";
    arraySeparator = '{';
    for(auto &setData : inputSet)
    {
        std::cout << arraySeparator << setData;
        inputArray.push_back(setData);
        arraySeparator = ',';
    }
    
    std::cout << "}\n";
    
    BinarySearch binarySearch;
    int numToSearch = 0;
    char option = '0';
    
    int expectedIndex = 0;
    
    for(auto &arrayData : inputArray)
    {
        int itr1Res = binarySearch.IterativeSearch1(inputArray, arrayData);
        int itr2Res = binarySearch.IterativeSearch2(inputArray, arrayData);
        int recuRes = binarySearch.RecursiveSearch(inputArray, 0, (inputArray.size()-1), arrayData);
        
        if ( (itr1Res ==  expectedIndex) && ( itr2Res ==  expectedIndex) && (recuRes == expectedIndex) )
            cout << "Binary Search SUCEEDED for data : " << arrayData << " @ Index# : " << expectedIndex << "\n";
        else
        {
            cout << "Binary Search FAILED for data  : " << arrayData << " @ Index# : " << expectedIndex << "\n";
            cout << "IterativeSearch1 Result        : " << itr1Res << "\n";
            cout << "IterativeSearch2 Result        : " << itr2Res << "\n";
            cout << "RecursiveSearch  Result        : " << recuRes << "\n";
        }
        expectedIndex++;
    }
}
#include <iostream>
#include <vector>
#include <random>
#include <climits>

//35. Search Insert Position

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int low  = 0;
        int high = nums.size()-1;
        int mid  = 0;
        
        while (low <= high)
        {
            mid  = (low+high)/2;
            if(nums[mid] == target)
                return mid;
            if(nums[mid] > target)
                high = mid-1;
            else
                low = mid+1;
        }
        if(target > nums[low])
            return (low+1);
        else
            return (low-1);
                
    }
};

//1,2,3(B),4(B),5(B),6(B),7(B),8(B),9(B),10(B)

int IterativeSearch1(vector<int>& nums, int target)
{
    int low  = 0;
    int high = nums.size()-1;
    int mid  = 0;
    
    while (low <= high)
    {
        mid  = (low+high)/2;
        if(nums[mid] == target)
            return mid;
        else if(nums[mid] > target)
            high = mid-1;
        else
            low = mid+1;
    }
    return -1;
}

class Solution {
public:
    int firstBadVersion(int n)
    {
        if(isBadVersion(1) == true)
            return 1;      
        else
        {
            int low  = 1;
            int high = n;
            int mid  = 0;
            
            while (low < high)
            {
                mid  = (low+high)/2;
                if(isBadVersion(mid))
                    high = mid;
                else
                    low = mid;
            }
            
            return low;
        }
    }
};

int main()
{
    vector<int> inputArray;
    
    cout << " Enter version array Size : ";
    cin >> arraySize;
    
    for(int i = 1 ; i <= arraySize ; ++i)
        inputArray.push_back(1);
    
    int verToFind = 0;
    cout << " Enter Version to be checked : ";
    cin >> verToFind;

    Solution firstBadVer;
    firstBadVer.firstBadVersion(verToFind);
    
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
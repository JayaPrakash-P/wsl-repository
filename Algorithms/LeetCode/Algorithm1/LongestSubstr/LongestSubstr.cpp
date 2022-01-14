#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int l = 1, sLen = s.length();
        
        if(!sLen)
            return 0;
        
        int next[sLen];
        fill_n(next, sLen, sLen-1);
        
        for(int i = 0 ; i < sLen ; ++i)
            for(int j = i+1 ; j < sLen ; ++j)
                if(s[i] == s[j])
                {
                    next[i] = j;
                    break;
                }
        
        for(int i = 0 ; i < sLen ; ++i)
            cout << s[i] << "-" << next[i] << endl;
        
        for(int i = 0 ; i < sLen ; ++i)
            for(int j = i+1 ; j <= next[i] ; ++j)
                if( (next[j] > next[i]) || (next[j] == (sLen-1)))
                     l = max(l, (j-i+1));
                else
                {
                    i = j;
                    break;
                }
        
        return l;
        
    }
};

int main(int argc, char** argv)
{
    string inS = argv[1];
    cout << "inS = " << inS << endl;
    Solution sol;
    int n = sol.lengthOfLongestSubstring(inS);
    cout << "n = " << n << endl;
    return 0;
}
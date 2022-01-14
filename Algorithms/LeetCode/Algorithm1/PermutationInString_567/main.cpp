#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        
        int l1 = s1.length();
        int l2 = s2.length();
        int l3 = 0;
        cout << "l1 =" << l1 << endl;
        cout << "l2 =" << l2 << endl;
        for(int i = 0; i < (l2-l1) ; ++i)
        {

            for(int j = 0; j < l1 ; ++j)
            {
                if(s2[i] == s1[j])
                   l3++;
            }
            cout << "l3 =" << l3 << endl;
            if(l3 == l1)
                return true;
            else
                l3 = 0;
        }
        return false;        
    }
};

int main(int argc, char** argv)
{
    cout << "Entering main\n";
    
    string s1{}, s2{};
    Solution s;
        
    if(argc == 3)
    {
        s1 = argv[1];
        s2 = argv[2];
    }
    else
    {
        s2 = "eidbaooo";
        s1 = "ab";
    }
    
    bool res = s.checkInclusion(s1,s2);
    cout << "Result = " << res << endl;
    return 0;
}

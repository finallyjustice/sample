/* Implement strStr() */

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n1 = haystack.size(); 
        int n2 = needle.size();
        const char *s1 = haystack.c_str();
        const char *s2 = needle.c_str();
        
        if(n2 > n1)
            return -1;
        
        int idx = -1;
        int flag;
        for(int i=0; i<=n1-n2; i++)
        {
            flag = 0;
            for(int j=0; j<n2; j++)
            {
                if(s1[i+j] != s2[j])
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
            {
                idx = i;
                break;
            }
        }
        
        return idx;
    }
};

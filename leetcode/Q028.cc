/* Implement strStr() */

class Solution {
public:
    int strStr(string haystack, string needle) {
        int l1 = haystack.size();
        int l2 = needle.size();
        
        if(l1 < l2)
            return -1;
            
        int idx = -1;
        for(int i=0; i<=l1-l2; i++) {
            int found = 1;
            for(int j=0; j<l2; j++) {
                if(haystack[i+j] != needle[j]) {
                    found = 0;
                    break;
                }
            }
            
            if(found == 1) {
                idx = i;
                break;
            }
        }
        
        return idx;
    }
};

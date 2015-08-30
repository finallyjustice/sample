/* Longest Substring Without Repeating Characters */

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        const char *str = s.c_str();
        
        if(n == 0)
            return 0;
        
        int tag[n];
        int i = 0; 
        int j = 1;
        set<char> st;
        st.insert(str[0]);
        int cur_max = 1;
        int cur_len = 1;
        
        while(j < n)
        {
            if(st.find(str[j]) != st.end())
            {
                while(i < j)
                {
                    if(str[i] != str[j])
                    {
                        st.erase(str[i]);
                        i++;
                        cur_len--;
                    }
                    else
                    {
                        i++;
                        j++;
                        break;
                    }
                }
            }
            else
            {
                st.insert(str[j]);
                j++;
                cur_len++;
            }
            
            if(cur_len > cur_max)
                cur_max = cur_len;
        }
        
        return cur_max;
    }
};

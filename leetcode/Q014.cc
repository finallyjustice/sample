/* Longest Common Prefix */

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        string sretn;
        if(n == 0)
            return sretn;
        
        const char *sc = strs[0].c_str();
        int lm = strs[0].size();
        int max = 0;
        
        for(int i=0; i<n; i++)
        {
            int len = strs[i].size();
            const char *cc = strs[i].c_str();
            
            int x = 0;
			int y = 0;
            int lcomm = 0;
            
            while(x<lm && y<len)
            {
                if(sc[x] != cc[y])
                    break;
                
                x++;
                y++;
                lcomm++;
            }
            
            lm = lcomm;
            max = lcomm;
        }
        
        vector<char> vret;
        for(int i=0; i<max; i++)
            vret.push_back(sc[i]);
        string sret(vret.begin(), vret.end());
        
        return sret;
    }
};

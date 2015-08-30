/* ZigZag Conversion */

class Solution {
public:
    string convert(string s, int numRows) {
        int n = s.size();
        if(numRows == 1 || n <= numRows)
            return s;
        
        const char *str = s.c_str();
        vector<char> vret;
        
        int idx;
        int gid = 0;
        
        for(int i=0; i<numRows; i++)
        {
            if(i==0 || i==numRows-1)
            {
                for(int j=0; ; j++)
                {
                    idx = i+j*(2*numRows-2);
                    if(idx >= n || gid >= n)
                        break;
                    
                    vret.push_back(str[idx]);
                    gid++;
                }
            }
            else
            {
                for(int j=0; ; j++)
                {
                    if(j % 2 == 0)
                    {
                        idx = i+j/2*(2*numRows-2);
                        if(idx >= n || gid >= n)
                            break;
                            
                        vret.push_back(str[idx]);
                        gid++;
                    }
                    else
                    {
                        idx = i+(j/2+1)*(2*numRows-2)-2*i;
                        if(idx >= n || gid >= n)
                            break;
                            
                        vret.push_back(str[idx]);
                        gid++;
                    }
                }
            }
        }
        
        string sret(vret.begin(),vret.end());
        return sret;
    }
};

/* String to Integer (atoi) */

class Solution {
public:
    int myAtoi(string str) {
        const char *sc = str.c_str();
        int n = str.size();
        long ret = 0;
        int flag = 0;
        int start = 0;
        
        int sign = 1;
        for(int i=0; i<n; i++)
        {
            if(sc[i] == ' ' && start == 0)
                continue;
                
            if(sc[i] == ' ' && start == 1)
                break;
                
            if(sc[i]=='+' && flag!=1)
            {
                sign = 1;
                flag = 1;
                start = 1;
                continue;
            }
            if(sc[i]=='-' && flag!=1)
            {
                sign = -1;
                flag = 1;
                start = 1;
                continue;
            }
            
            if(sc[i]<'0' || sc[i]>'9')
                break;
                
            ret = ret*10+(sc[i]-'0');
            start = 1;
            
            if(ret > 0x7fffffff && sign == 1)
                return 0x7fffffff;
            
            if(ret > 0x80000000 && sign == -1)
                return 0x80000000;
        }

        return sign*ret;
    }
};

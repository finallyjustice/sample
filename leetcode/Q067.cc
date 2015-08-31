/* Add Binary */

class Solution {
public:
    string addBinary(string a, string b) {
        int n1 = a.size();
        int n2 = b.size();
        const char *s1 = a.c_str();
        const char *s2 = b.c_str();
        
        int carry = 0;
        list<char> lret;
        
		int i = n1-1;
        int j = n2-1;
        while(i>=0 || j>=0)
        {
            int v1 = i>=0?s1[i]-'0':0;
            int v2 = j>=0?s2[j]-'0':0;
            
            int tmp = v1+v2+carry;
            carry = tmp / 2;
            tmp = tmp % 2;
            
            lret.insert(lret.begin(), tmp+'0');
            
            if(i >= 0)
                i--;
            if(j >= 0)
                j--;
        }
        
        if(carry != 0)
            lret.insert(lret.begin(), carry+'0');
            
        string sret(lret.begin(), lret.end());
        return sret;
    }
};

/* Reverse Integer */
class Solution {
public:
    int reverse(int x) {
        long n = 0;
        int r;
        int s = x>=0?1:-1;
        x = x>=0?x:-x;
        while(x != 0)
        {
            r = x % 10;
            n = n * 10 + r;
            x = x / 10;
        }
        
        if(n > INT_MAX || -n > INT_MAX)
            return 0;
            
        return s*n;
    }
};

/* Climbing Stairs */

class Solution {
public:
    int climbStairs(int n) {
        // T(n) = T(n-1)+T(n-2)
        // T(2) = 2
        // T(1) = 1
        // T(0) = 1
        
        /*if(n==0 || n==1)
            return 1;
            
        return climbStairs(n-1)+climbStairs(n-2);*/
        
        if(n==0 || n==1)
            return 1;
        
        int log[n];
        log[0] = 1;
        log[1] = 1;

        for(int i=2; i<=n; i++)
            log[i] = log[i-1]+log[i-2];
        return log[n];
    }
};

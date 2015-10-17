/* Count Primes */

class Solution {
public:
    int countPrimes(int n) {
        int *check = (int *)malloc(sizeof(int)*n);
        for(int i=0; i<n; i++)
            check[i] = 0;
            
        for(int i=2; i*i<n; i++) {
            if(check[i] == 0) {
                for(int j=i; j*i<n; j++) {
                    check[j*i] = 1;
                }
            }
        }
        
        int tot = 0;
        for(int i=2; i<n; i++)
            if(check[i] == 0)  
                tot++;
                
        free(check);
                
        return tot;
    }
};

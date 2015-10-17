/* Edit Distance */

class Solution {
public:
    int minDistance(string word1, string word2) {
        int l1 = word1.size();
        int l2 = word2.size();
        
        if(l1 == 0)
            return l2;
        if(l2 == 0)
            return l1;
            
        int **m = (int **)malloc(sizeof(int *)*(l1+1));
        for(int i=0; i<l1+1; i++) {
            m[i] = (int *)malloc(sizeof(int)*(l2+1));
            memset(m[i], 0, sizeof(int)*(l2+1));
        }
        
        // start of algorithm
        for(int i=1; i<l1+1; i++)
            m[i][0] = i;
        for(int j=1; j<l2+1; j++)
            m[0][j] = j;
            
        for(int i=1; i<l1+1; i++) {
            for(int j=1; j<l2+1; j++) {
                if(word1[i-1] == word2[j-1])
                    m[i][j] = m[i-1][j-1];
                else 
                    m[i][j] = m[i-1][j-1]+1;
                m[i][j] = min(m[i][j], min(m[i-1][j]+1, m[i][j-1]+1));
            }
        }
        
        int ret = m[l1][l2];
        
        for(int i=0; i<l1+1; i++)
            free(m[i]);
        free(m);
        
        return ret;
    }
};

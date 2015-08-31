/* Merge Sorted Array */

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1;
        int j = n-1;
        int c = m+n-1;
        
        while(i>=0 || j>=0)
        {
            int v1 = i>=0 ? nums1[i] : -INT_MAX;
            int v2 = j>=0 ? nums2[j] : -INT_MAX;
            
            if(v1 >= v2)
            {
                nums1[c] = v1;
                i--;
            }
            else
            {
                nums1[c] = v2;
                j--;
            }
            c--;
        }
    }
};

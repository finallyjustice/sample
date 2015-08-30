/* Remove Duplicates from Sorted Array */

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n==0 || n==1)
            return n;
            
        int size = 0;
        for(int i=0; i<n; i++)
        {
            if(nums[i] != nums[size])
            {
                size++;
                nums[size] = nums[i];
            }
        }
        
        return size+1;
    }
};

/* Remove Element */

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        
        if(n == 0)
            return n;
            
        int size = -1;
        for(int i=0; i<n; i++)
        {
            if(nums[i] != val)
            {
                size++;
                nums[size] = nums[i];
            }
        }
        
        return size+1;
    }
};

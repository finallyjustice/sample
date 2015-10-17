/* Kth Largest Element in an Array */

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        quick_sort(nums, 0, n-1);
        return nums[n-k];
    }
    
    void quick_sort(vector<int>& nums, int p, int q) {
        if(p >= q)
            return;
            
        int m = partition(nums, p, q);
        quick_sort(nums, p, m);
        quick_sort(nums, m+1, q);
    }
    
    int partition(vector<int>& nums, int p, int q) {
        int pivot = nums[q];
        int i = p-1;
        for(int j=p; j<q; j++) {
            if(nums[j] <= pivot) {
                i++;
                int tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
            }
        }

        int tmp = nums[q];
        nums[q] = nums[i+1];
        nums[i+1] = tmp;

        return i;
    }
};

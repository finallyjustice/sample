/* Contains Duplicate */

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int size = nums.size();
        set<int> s;
        for(int i=0; i<size; i++) {
            if(s.find(nums[i]) != s.end())
                return true;
            else
                s.insert(nums[i]);
        }
        return false;
        
        /*vector<int> tmp = nums;
        int size = tmp.size();
        quick_sort(tmp, 0, tmp.size()-1);
        for(int i=0; i<size-1; i++)
            if(tmp[i] == tmp[i+1])
                return true;
        return false;*/
    }
    
    /*void quick_sort(vector<int>& nums, int p, int q) {
        if(p >= q)
            return;
        int m = partition(nums, p, q);
        quick_sort(nums, p, m);
        quick_sort(nums, m+1, q);
    }
    
    int partition(vector<int>& nums, int p, int q) {
        int pivot = nums[q];
        int i = p-1;
        for(int j=p; j<=q; j++) {
            if(nums[j] <= pivot) {
                i++;
                int n = nums[j];
                nums[j] = nums[i];
                nums[i] = n;
            }
        }
        return i-1;
    }*/
};

/* Two Sum */

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> data;
        int n = nums.size();
        vector<int> ret;
        
        for(int i=0; i<n; i++)
            data[nums[i]] = i;
            
        map<int, int>::iterator it;
        for(int i=0; i<n; i++)
        {
            it = data.find(target-nums[i]);
            if(it != data.end())
            {
                if(i >= it->second)
                    continue;
                    
                ret.push_back(i+1);
                ret.push_back(it->second+1);
                
                return ret;
            }
        }
    }
};

/* Convert Sorted Array to Binary Search Tree */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int size = nums.size();
        return sortedArrayToBSTRecv(nums, 0, size-1);
    }
    
    TreeNode* sortedArrayToBSTRecv(vector<int>& nums, int p, int q) {
        if(p > q)
            return NULL;
        
        int size = q-p+1;
        int mid = (size-1)/2 + p;
        
        TreeNode *ln = sortedArrayToBSTRecv(nums, p, mid-1);
        TreeNode *rn = sortedArrayToBSTRecv(nums, mid+1, q);
        
        TreeNode *n = (TreeNode *)malloc(sizeof(TreeNode));
        n->left = ln;
        n->right = rn;
        n->val = nums[mid];
        
        return n;
    }
};

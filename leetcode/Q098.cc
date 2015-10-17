/* Validate Binary Search Tree */

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
    bool isValidBST(TreeNode* root) {
        if(root == NULL)
            return true;
            
        vector<int> v;
        in_order_walk(root, v);
        
        int size = v.size();
        for(int i=0; i<size; i++) {
            if(i == 0)
                continue;
            if(v[i] <= v[i-1])
                return false;
        }
        return true;
    }

    void in_order_walk(TreeNode *root, vector<int>& v) {
        if(root == NULL)
            return;
        
        in_order_walk(root->left, v);
        v.push_back(root->val);
        in_order_walk(root->right, v);
    }

    /*bool isValidBST(TreeNode* root) {
        return isValidBSTRecv(root, -INT_MAX, INT_MAX);
    }
    
    bool isValidBSTRecv(TreeNode* root, int p, int q) {
        if(root == NULL)
            return true;
        if(root->val>p && root->val<q)
            return isValidBSTRecv(root->left, p, root->val) && isValidBSTRecv(root->right, root->val, q);
        else
            return false;
    }*/
};

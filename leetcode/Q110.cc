/* Balanced Binary Tree */

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
    bool isBalanced(TreeNode* root) {
        if(root == NULL)
            return true;
        if(root->left==NULL && root->right==NULL)
            return true;
        int hl = height(root->left);
        int hr = height(root->right);
        if(abs(hl-hr) > 1)
            return false;
        else
            return isBalanced(root->left) && isBalanced(root->right);
    }
    
    int height(TreeNode* root) {
        if(root == NULL)
            return 0;
        return 1+max(height(root->left), height(root->right));
    }
};

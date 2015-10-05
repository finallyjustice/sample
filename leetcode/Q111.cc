/* Minimum Depth of Binary Tree */

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
    int minDepth(TreeNode* root) {
        if(root == NULL)
            return 0;
        if(root->left==NULL && root->right==NULL)
            return 1;
            
        int dl = minDepth(root->left);
        int dr = minDepth(root->right);
        if(dl == 0)
            dl = INT_MAX;
        if(dr == 0)
            dr = INT_MAX;
            
        return 1+min(dl, dr);
    }
};

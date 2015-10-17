/* Lowest Common Ancestor of a Binary Tree */

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!covers(root, p) || !covers(root, q))
            return NULL;
        return lowestCommonAncestorRecv(root, p, q);
    }
    
    TreeNode* lowestCommonAncestorRecv(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL)
            return NULL;
        if(root==p || root==q)
            return root;
        int is_p_on_left = covers(root->left, p);
        int is_q_on_left = covers(root->left, q);
        
        if(is_p_on_left != is_q_on_left)
            return root;
            
        if(is_p_on_left==1 && is_q_on_left==1)
            return lowestCommonAncestorRecv(root->left, p, q);
        if(is_p_on_left==0 && is_q_on_left==0)
            return lowestCommonAncestorRecv(root->right, p, q);
    }
    
    int covers(TreeNode *root, TreeNode *n) {
        if(root == NULL)
            return 0;
        if(root == n)
            return 1;
        return covers(root->left, n) || covers(root->right, n);
    }
};

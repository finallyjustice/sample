/* Invert Binary Tree */

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
    TreeNode* invertTree(TreeNode* root) {
        // iterative solution
        if(root == NULL)
            return NULL;
        
        queue<TreeNode *> q;
        q.push(root);
        
        while(!q.empty()) {
            TreeNode *pn = q.front();
            TreeNode *ln = pn->left;
            TreeNode *rn = pn->right;
            pn->left = rn;
            pn->right = ln;
            
            q.pop();
            if(ln != NULL)
                q.push(ln);
            if(rn != NULL)
                q.push(rn);
        }
        
        return root;
        
        /* recursive solution
        if(root == NULL)
            return NULL;
        
        TreeNode *ln = root->left;
        TreeNode *rn = root->right;
        
        root->left = invertTree(rn);
        root->right = invertTree(ln);
        
        return root;*/
    }
};

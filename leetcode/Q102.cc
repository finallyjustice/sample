/* Binary Tree Level Order Traversal */

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vv;
        if(root == NULL)
            return vv;
            
        queue<TreeNode *> q1;
        queue<int> q2;
        
        q1.push(root);
        q2.push(0);
        
        int cd = -1;
        while(!q1.empty())
        {
            TreeNode *tmp = q1.front();
            int deep = q2.front(); 
            
            if(deep > cd)
            {
                cd = deep;
                vector<int> v;
                vv.push_back(v);
            }
            
            vv[cd].push_back(tmp->val);
            
            if(tmp->left != NULL)
            {
                q1.push(tmp->left);
                q2.push(cd+1);
            }
            
            if(tmp->right != NULL)
            {
                q1.push(tmp->right);
                q2.push(cd+1);
            }
            
            q1.pop();
            q2.pop();
        }
        
        return vv;
    }
};

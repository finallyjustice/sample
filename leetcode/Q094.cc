/* Binary Tree Inorder Traversal */

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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> v;
        if(root == NULL)
            return v;
            
        stack<TreeNode *> s;
        TreeNode *tmp = root;
        
        while(1) {
            while(tmp != NULL) {
                s.push(tmp);
                tmp = tmp->left;
            }
            
            if(!s.empty()) {
                tmp = s.top();
                s.pop();
                v.push_back(tmp->val);
                tmp = tmp->right;
            } else {
                break;
            }
        }
        
        return v;
    }
};

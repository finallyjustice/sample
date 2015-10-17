/* Binary Tree Preorder Traversal */

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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> v;
        if(root == NULL)
            return v;
            
        TreeNode *tmp = root;
        stack<TreeNode *> s;
        do {
            while(tmp != NULL) {
                v.push_back(tmp->val);
                if(tmp->right != NULL)
                    s.push(tmp->right);
                tmp = tmp->left;
            }
            
            if(!s.empty()) {
                tmp = s.top();
                s.pop();
            }
        } while(!s.empty() || tmp!=NULL);
        
        return v;
    }
};

/* Binary Tree Postorder Traversal */

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> v;
        if(root == NULL)
            return v;
            
        stack<TreeNode *> s;
        TreeNode *tmp = root;
        do {
            while(tmp != NULL) {
                v.push_back(tmp->val);
                if(tmp->left != NULL)
                    s.push(tmp->left);
                tmp = tmp->right;
            }
            
            if(!s.empty()) {
                tmp = s.top();
                s.pop();
            }
        } while(!s.empty() || tmp!=NULL);
        
        int n = v.size();
        int m = n/2;
        for(int i=0; i<m; i++) {
            int t = v[i];
            v[i] = v[n-1-i];
            v[n-1-i] = t;
        }
        
        return v;
    }
};

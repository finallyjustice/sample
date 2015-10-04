/* Binary Tree Level Order Traversal II */

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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> vv;
        if(root == NULL)
            return vv;
            
        queue<TreeNode *> qn;
        queue<int> qd;
        int cd = -1;
        
        qn.push(root);
        qd.push(0);
        
        while(!qn.empty()) {
            TreeNode* n = qn.front();
            int d = qd.front();
            
            if(d > cd) {
                vector<int> nv;
                vv.push_back(nv);
                cd++;
            }
            vv[d].push_back(n->val);
            
            if(n->left != NULL) {
                qn.push(n->left);
                qd.push(d+1);
            }
            
            if(n->right != NULL) {
                qn.push(n->right);
                qd.push(d+1);
            }
            
            qn.pop();
            qd.pop();
        }
        
        int level = vv.size();
        vector<vector<int>> fv(level);
        for(int i=0; i<level; i++) {
            fv[i] = vv[level-1-i];
        }
        return fv;
    }
};

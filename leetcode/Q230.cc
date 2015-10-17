/* Kth Smallest Element in a BST */

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
    int kthSmallest(TreeNode* root, int k) {
        list<int> l;
        in_order_walk(root, l);
        list<int>::iterator it;
        int r = 1;
        for(it=l.begin(); it!=l.end(); it++) {
            if(r == k)
                return *it;
            r++;
        }
    }
    
    void in_order_walk(TreeNode *root, list<int>& l) {
        if(root == NULL)
            return;
        in_order_walk(root->left, l);
        l.push_back(root->val);
        in_order_walk(root->right, l);
    }
};

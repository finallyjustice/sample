/* Convert Sorted List to Binary Search Tree */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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
    TreeNode* sortedListToBST(ListNode* head) {
        if(head == NULL)
            return NULL;
        int q = -1;
        ListNode *tmp = head;
        while(tmp != NULL) {
            q++;
            tmp = tmp->next;
        }
        tmp = head;
        return sortedListToBSTRecv(tmp, 0, q);
    }
    
    TreeNode* sortedListToBSTRecv(ListNode* &head, int p, int q) {
        if(p > q)
            return NULL;
        int m = p+(q-p)/2;
        
        TreeNode *left = sortedListToBSTRecv(head, p, m-1);
        TreeNode *root = new TreeNode(head->val);
        head = head->next;
        TreeNode *right = sortedListToBSTRecv(head, m+1, q);
        
        root->left = left;
        root->right = right;
        
        return root;
    }
};

/* Delete Node in a Linked List */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        if(node == NULL)
            return;
            
        while(node->next->next != NULL) {
            node->val = node->next->val;
            node = node->next;
        }
        
        node->val = node->next->val;
        ListNode *tmp = node->next;
        node->next = NULL;
        free(tmp);
    }
};

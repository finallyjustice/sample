/* Reverse Linked List */

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
    ListNode* reverseList(ListNode* head) {
        if(head == NULL)
            return NULL;
        
        ListNode *tmp = head;
        ListNode *ret = NULL;
        while(tmp != NULL) {
            ListNode *n = tmp;
            tmp = tmp->next;
            insert_head(&ret, n);
        }
        
        return ret;
    }
    
    void insert_head(ListNode **head, ListNode *n) {
        if(*head == NULL) {
            *head = n;
            n->next = NULL;
            return;
        }
        
        n->next = *head;
        *head = n;
    }
};

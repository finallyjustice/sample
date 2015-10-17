/* Remove Linked List Elements */

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
    ListNode* removeElements(ListNode* head, int val) {
        if(head == NULL)
            return head;
        
        ListNode *tmp = head;
        ListNode *nh = NULL;
        ListNode *nt = NULL;
        
        while(tmp != NULL) {
            ListNode *n = tmp;
            tmp = tmp->next;
            if(n->val == val)
                free(n);
            else
                insert_tail(&nh, &nt, n);
        }
        
        return nh;
    }
    
    void insert_tail(ListNode **head, ListNode **tail, ListNode *n) {
        n->next = NULL;
        if(*head == NULL) {
            *head = n;
            *tail = n;
            return;
        }
        
        (*tail)->next = n;
        *tail = n;
    }
};

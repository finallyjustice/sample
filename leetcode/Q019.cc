/* Remove Nth Node From End of List */

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *hn = head;
        ListNode *tn = head;
        
        for(int i=0; i<n-1; i++)
            tn = tn->next;
            
        // if removing head
        if(tn->next == NULL)
        {
            ListNode *tmp = head;
            head = head->next;
            free(tmp);
            return head;
        }
            
        ListNode *pn;
        do {
            pn = hn;
            hn = hn->next;
            tn = tn->next;
        } while(tn->next);
        
        pn->next = hn->next;
        free(hn);
        return head;
    }
};

/* Remove Duplicates from Sorted List */

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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *n = head;
        if(n == NULL)
            return n;
            
        while(n->next != NULL)
        {
            if(n->next->val != n->val)
            {
                n = n->next;
                continue;
            }
            else
            {
                ListNode *tmp = n->next;
                n->next = n->next->next;
                free(tmp);
            }
        }
        
        return head;
    }
};

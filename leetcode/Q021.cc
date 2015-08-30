/* Merge Two Sorted Lists */

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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *ln = NULL;
        ListNode *tail = NULL;
        
        int v1, v2;
        while(l1!=NULL || l2!=NULL)
        {
            v1 = l1==NULL?INT_MAX:l1->val;
            v2 = l2==NULL?INT_MAX:l2->val;
            
            ListNode *tmp;
            if(v1 <= v2)
            {
                // insert v1 into ln
                tmp = l1;
                l1 = l1->next;
            }
            else
            {
                // insert v2 into ln
                tmp = l2;
                l2 = l2->next;
            }
            
            // implementation of insertion
            tmp->next = NULL;
            if(ln == NULL)
            {
                ln = tmp;
                tail = tmp;
            }
            else
            {
                tail->next = tmp;
                tail = tail->next;
            }
        }
        
        return ln;
    }
};

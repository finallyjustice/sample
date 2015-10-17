/* Intersection of Two Linked Lists */

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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA==NULL || headB==NULL) 
            return NULL;
            
        int l1=0, l2=0;
        ListNode *tmpA = headA;
        ListNode *tmpB = headB;
        
        while(tmpA != NULL) {
            tmpA = tmpA->next;
            l1++;
        }
        while(tmpB != NULL) {
            tmpB = tmpB->next;
            l2++;
        }
        
        int step;
        if(l1 >= l2) {
            step = l1-l2;
            tmpA = headA;
            tmpB = headB;
        } else {
            step = l2-l1;
            tmpA = headB;
            tmpB = headA;
        }
        
        for(int i=0; i<step; i++) 
            tmpA = tmpA->next;
            
        while(tmpA!=NULL && tmpB!=NULL) {
            if(tmpA == tmpB)
                return tmpA;
            tmpA = tmpA->next;
            tmpB = tmpB->next;
        }
        
        return NULL;
    }
};

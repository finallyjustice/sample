/* Add Two Numbers */

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *ret = NULL;
        int sum;
        int carry = 0;
        vector<int> tmp;
        
        int v1;
        int v2;
        while(l1!=NULL || l2!=NULL)
        {
            v1 = l1==NULL? 0 : l1->val;
            v2 = l2==NULL? 0 : l2->val;
            
            sum = v1+v2+carry;
            carry = sum / 10;
            sum = sum % 10;
            tmp.push_back(sum);
            
            if(l1 != NULL)
                l1 = l1->next;
            if(l2 != NULL)
                l2 = l2->next;
        }
        
        if(carry != 0)
            tmp.push_back(carry);
            
        int num = tmp.size();
        if(num == 0)
            return ret;
        
        ret = new ListNode(tmp[0]);
        ListNode *tail = ret;
        
        for(int i=1; i<num; i++)
        {
            ListNode *n = new ListNode(tmp[i]);
            tail->next = n;
            tail = n;
        }
        
        return ret;
    }
};

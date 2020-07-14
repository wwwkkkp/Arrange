// 6.6 36. 合并两个排序的链表 

输入两个递增排序的链表，合并这两个链表并使新链表中的结点仍然是按照递增排序的。
样例
输入：1->3->5 , 2->4->5

输出：1->2->3->4->5->5


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
    ListNode* merge(ListNode* l1, ListNode* l2) {
        if(!l1&&!l2) return NULL;
        auto a=new ListNode(-1);
        auto b=a;
        while(l1&&l2){
            if(l1->val>l2->val) {
                b->next=l2;
                b=b->next;
                l2=l2->next;
            }else{
                b->next=l1;
                b=b->next;
                l1=l1->next;
            }

        }  
        if(l1)b->next=l1;
        else b->next=l2;
        
        b=a->next;
        delete a;
        return b;
        
    } 
};
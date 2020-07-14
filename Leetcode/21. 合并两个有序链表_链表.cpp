

//21. 合并两个有序链表
将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

示例：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4


//递归
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
        if(!l1)return l2;
        if(!l2)return l1;
        ListNode* l3=NULL;
        if(l1->val>l2->val){
            l3=l2;
            l3->next=mergeTwoLists(l1,l2->next);
        }else{
            l3=l1;
            l3->next=mergeTwoLists(l1->next,l2);
        }
        return l3;
    }
};



//双指针
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
        if(!l1)return l2;
        if(!l2)return l1;
        ListNode* l3=new ListNode(0);
        ListNode* t=l3;
        ListNode* p=l1;
        ListNode* q=l2;
        
        while(p&&q){
            if(p->val>q->val){
                t->next=q;
                t=t->next;
                q=q->next;
            }else{
                t->next=p;
                t=t->next;
                p=p->next;
            }
        }
        if(!p)t->next=q;
        if(!q)t->next=p;
        return l3->next;
    }
};
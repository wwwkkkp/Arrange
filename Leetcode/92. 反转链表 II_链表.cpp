

//92. 反转链表 II
反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。

说明:
1 ≤ m ≤ n ≤ 链表长度。

示例:

输入: 1->2->3->4->5->NULL, m = 2, n = 4
输出: 1->4->3->2->5->NULL


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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(!head)return NULL;
        ListNode* t=new ListNode(0);
        t->next=head;
        ListNode* p=t;
        int m1=m;
        while(--m1&&p)p=p->next; //需要交换的结点的上一个结点
        ListNode* ne=p->next;
        ListNode* ol=ne->next;
        ne->next=NULL;

        n=n-m;

        while(ol&&n--){
            ListNode* x=ol->next;
            ol->next=ne;
            ne=ol;
            ol=x;

        }
        p->next=ne;
        while(p->next)p=p->next;
        p->next=ol;
        return t->next;
    }
};
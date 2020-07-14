
//5.6 33. 链表中倒数第k个节点 


输入一个链表，输出该链表中倒数第k个结点。
注意：
k >= 0;
如果k大于链表长度，则返回 NULL;
样例
输入：链表：1->2->3->4->5 ，k=2

输出：4

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
 //倒数第k个数就是正数第n-k个数
class Solution {
public:
    ListNode* findKthToTail(ListNode* p, int k) {
        int n=0;
        auto pend=p;
        while(pend){
            n++;
            pend=pend->next;
        }
        if(k>n) return NULL;
        int a=n-k;
        while(a--){
            p=p->next;
        }
        return p;
    }
};
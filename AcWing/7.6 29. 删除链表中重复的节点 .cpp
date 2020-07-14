//7.6 29. 删除链表中重复的节点 

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留。
样例1
输入：1->2->3->3->4->4->5

输出：1->2->5
样例2
输入：1->1->1->2->3

输出：2->3

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
    ListNode* deleteDuplication(ListNode* head) {
        ListNode* a=new ListNode(-1);  //要删除头结点的链表，都要添加一个虚拟结点 
        ListNode* b=a;
        a->next = head;
        while(b->next){
            ListNode* c=b->next; //两个指针遍历，
            while(c&&b->next->val==c->val) c=c->next;
            if(c==b->next->next)b=b->next; //如果两个指针中间隔一个，那说明中间这个结点只有一个
            else b->next=c; //否则删除这些结点
        }
        ListNode* p=a->next;
        //detele a;
        return p;
    }
};
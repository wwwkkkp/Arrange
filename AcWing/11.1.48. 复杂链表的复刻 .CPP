

//11.1.48. 复杂链表的复刻 

请实现一个函数可以复制一个复杂链表。
在复杂链表中，每个结点除了有一个指针指向下一个结点外，还有一个额外的指针指向链表中的任意结点或者null。
注意：
函数结束后原链表要与输入时保持一致。


/**
 * Definition for singly-linked list with a random pointer.
 * struct ListNode {
 *     int val;
 *     ListNode *next, *random;
 *     ListNode(int x) : val(x), next(NULL), random(NULL) {}
 * };
 */
 
class Solution {
public:
    ListNode *copyRandomList(ListNode *head) {
        unordered_map<ListNode*,ListNode*>up;//用这个表建立原链表结点和新链表结点的映射关系
        if(!head) return NULL;
        ListNode*p=head;
        up[NULL]=NULL;
        while(p){
            up[p]=new ListNode(p->val);
            p=p->next;
        }
        p=head;
        while(p){
            up[p]->random=up[p->random];
            up[p]->next=up[p->next];
            p=p->next;
        }
        return up[head];
    }
};

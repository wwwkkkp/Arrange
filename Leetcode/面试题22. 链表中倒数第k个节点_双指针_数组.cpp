/*面试题22. 链表中倒数第k个节点

输入一个链表，输出该链表中倒数第k个节点。
为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。例如，一个链表有6个节点，从头节点开始，它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点。

示例：

给定一个链表: 1->2->3->4->5, 和 k = 2.

返回链表 4->5.
*/


//双指针法，耗时8ms
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
    ListNode* getKthFromEnd(ListNode* p, int k) {
        ListNode* s;
        s=p;
        int i=0;
        while(p && i<k){
            p=p->next;
            i++;
        }        
        while(p){
            p=p->next;
            s=s->next;  
        }

        return s;
    }
};

//双指针法，耗时0ms,与上面的很相似，但是时间上差很多，不得其解
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* p, int k) {
        ListNode* s;
        s=p;
        while(p && k-->0){
            p=p->next;
        }        
        while(p){
            p=p->next;
            s=s->next;  
        }
        return s;
    }
};

//数组法
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* p, int k) {
        ListNode* s;
        s=p;
        int i=0;
        while(p!=NULL && i<k){
            p=p->next;
            i++;
        }
        if(i<k)
            return NULL;        
        while(p!=NULL){
            p=p->next;
            s=s->next;  
        }

        return s;
    }
};
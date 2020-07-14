

//82. 删除排序链表中的重复元素 II
给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字。

示例 1:

输入: 1->2->3->3->4->4->5
输出: 1->2->5
示例 2:

输入: 1->1->1->2->3
输出: 2->3


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 //链表，注意不要对空结点进行操作
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head)return NULL;
        auto p=new ListNode(0);
        p->next=head;
        auto t=p;
        while(t->next){
            auto t1=t->next;
            auto t2=t1->next;
            if(!t2)break;
            if(t1->val==t2->val){
                int k=t1->val;
                while(t->next&&t->next->val==t1->val){
                    t->next=t->next->next;
                }
            }else{
                t=t->next;
            }
        }
        return p->next;
    }
};


//23. 合并K个排序链表
合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。

示例:

输入:
[
  1->4->5,
  1->3->4,
  2->6
]
输出: 1->1->2->3->4->4->5->6



//其实就是合并两个链表，只是多合并了几次
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n=lists.size();
        if(n==1)return lists[0];
        if(!n)return NULL;
        for(int i=1;i<lists.size();i++)
            lists[0]=mergeTwoLists(lists[0],lists[i]);
        return lists[0];
    }
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
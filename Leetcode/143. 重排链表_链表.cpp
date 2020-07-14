


//143. 重排链表
给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例 1:

给定链表 1->2->3->4, 重新排列为 1->4->2->3.
示例 2:

给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.


//链表
class Solution {
public:
    void reorderList(ListNode* head) {
        if(!head) return;
        vector<ListNode*>v;
        while(head){
            v.push_back(head); //把结点都存到vector中，然后用双指针去遍历就行了
            head=head->next;
        }
        int n=v.size();
        int i=0,j=n-1;
        while(i<j){
            v[i]->next=v[j];
            i++;
            if(i==j){v[i]->next=NULL;break;}
            v[j]->next=v[i];
            j--;
            if(i==j){v[i]->next=NULL;break;}
        }
        return ;
    }
};

解法二 递归
解法三：把链表平均分成两部分，然后翻转第二个链表，然后双指针遍历

https://leetcode-cn.com/problems/reorder-list/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-34/
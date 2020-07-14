
//61. 旋转链表
给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。

示例 1:

输入: 1->2->3->4->5->NULL, k = 2
输出: 4->5->1->2->3->NULL
解释:
向右旋转 1 步: 5->1->2->3->4->NULL
向右旋转 2 步: 4->5->1->2->3->NULL
示例 2:

输入: 0->1->2->NULL, k = 4
输出: 2->0->1->NULL
解释:
向右旋转 1 步: 2->0->1->NULL
向右旋转 2 步: 1->2->0->NULL
向右旋转 3 步: 0->1->2->NULL
向右旋转 4 步: 2->0->1->NULL

//链表
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
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head)return NULL;
        int n=0;
        ListNode* p=head;
        while(p){p=p->next;n++;}
        k=k%n;
        k++;
        ListNode* t=head;
        p=head;
        for(int i=0;i<k;i++)t=t->next; //先移动k个结点
        while(t){p=p->next;t=t->next;}; //然后两个节点一起动，这样最后后面的结点就到了想要的位置
        auto rear=head;
        while(rear->next)rear=rear->next;
        rear->next=head;
        t=p->next;
        p->next=NULL;
        return t;
    }
};

//写法简洁一点
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head)return NULL;
        int n=1;
        ListNode* rear=head;
        while(rear->next){rear=rear->next;n++;}  //当需要对链表计数的时候，判断语句应该是rear->next，因为计完数以后，rear结点恰好指向尾结点
        rear->next=head;
        k=k%n;
        k=n-1-k;  
        auto p=head;
        while(k--)p=p->next;//保证p到尾结点的距离是k，这里其实可以借鉴上面的做法，用双指针去移动
        auto t=p->next;
        p->next=NULL;
        return t;
    }
};
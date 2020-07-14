
//25. K 个一组翻转链表
给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

 

示例：

给你这个链表：1->2->3->4->5

当 k = 2 时，应当返回: 2->1->4->3->5

当 k = 3 时，应当返回: 3->2->1->4->5

 

说明：

你的算法只能使用常数的额外空间。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

//先计算要翻转多少次，然后再分次翻转

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
    ListNode* reverseKGroup(ListNode* h, int k) {
        if(!h)return NULL;
        ListNode* head=new ListNode(0);
        head->next=h;
        ListNode* p=head;
        int i=0;
        while(p->next){
            p=p->next;
            i++;
        }
        int n=i/k;  //翻转多少次
        p=head;
        ListNode* ne=head;
        ListNode* ol=ne->next;
        ListNode* te=ol->next;
        while(n--){
            int k1=k-1;
            while(k1--){   
                ne=ol;
                ol=te;
                te=te->next;//三个指针，ol和ne翻转
                ol->next=ne;
            }
            p->next=ol;
            int k2=k;
            while(k2--){
                p=p->next;//移动到这一段开始的头结点，现在是尾结点了
            }
            p->next=te;
            if(te)  //如果表长刚好能被k整除，就需要添加这个判断，因为这个时候te已经是NULL了
                ne=ol,ol=te,te=te->next;
        }
        return head->next;
    }
};




//递归做法，简单很多
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head)return NULL;
        ListNode* p=head;
        int k1=k;
        while(p&&--k1)p=p->next;//找到第k个结点，
        if(k1>0)return head;//如果在找到第k个结点之前结点就结束了，那就原封不动返回
        ListNode* ne=head;
        ListNode* ol=head->next;
		
        while(ne!=p){//翻一个k个结点，
            ListNode* t=ol->next;
            ol->next=ne;
            ne=ol;
            ol=t;
        }
        head->next=reverseKGroup(ol,k); //递归下去
        return ne;
    }
};
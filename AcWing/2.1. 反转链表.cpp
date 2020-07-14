//7.35. 反转链表 

定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的头结点。
思考题：
请同时实现迭代版本和递归版本。
样例
输入:1->2->3->4->5->NULL

输出:5->4->3->2->1->NULL

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
//两种方法，第一种，迭代法  和数据结构中的那道每n个结点翻转一次的题有点像
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* old=head;
		ListNode* newL=NULL;
		while(old){
			ListNode* tmp=old->next;
			old->next=newL;
			newL=old;
			old=tmp;		
		}
		return new;
    }
};


//第二种递归法，举例[1,2,3,4,5] 应该返回[5,4,3,2,1]
class Solution {
public:
    ListNode* reverseList(ListNode* head) {  //递归法 要搞清楚函数的意思是什么，比如，这个函数的意思就是求头结点是head的链表的翻转，
		if(!head||!head->next) return head;  //如果头结点为空或者只有一个结点，返回该结点
		ListNode* s=reverseList(head->next); //返回以head->next为头结点的链表，5->4->3->2->null,1->2,然后让2->1,1->NULL,就是反转后的链表
		ListNode* k=s;
		while(k->next)
			k=k->next;
		k->next=head;
		head->next=NULL;
		return s;
    }
};

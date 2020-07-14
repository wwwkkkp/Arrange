//2.  1451.单链表快速排序 

给定一个单链表，请使用快速排序算法对其排序。
要求：期望平均时间复杂度为 O(nlogn)

，期望额外空间复杂度为 O(logn)
。
思考题： 如果只能改变链表结构，不能修改每个节点的val值该如何做呢？

数据范围
链表中的所有数大小均在 
int
int
范围内，链表长度在 [0,10000]。

输入样例：
[5, 3, 2]
输出样例：
[2, 3, 5]

//链表的快速排序：
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
    
	ListNode* get_end(ListNode* p){
		while(p->next)
			p=p->next;
		return p;
	}
    ListNode* quickSortList(ListNode* head) { //链表的快速排序
		if(!head||!head->next) return head;
        auto left=new ListNode(-1),mid=new ListNode(-1),right=new ListNode(-1);  //auto可以换成 ListNode*
		auto leftend=left,midend=mid,rightend=right;
		
		int k=head->val;
		for(auto p=head;p;p=p->next){
			if(p->val<k){
				leftend->next=p;
				leftend=leftend->next;				
			}
			else if(p->val==k){
				midend->next=p;
				midend=midend->next;
			}
			else{
				rightend->next=p;
				rightend=rightend->next;
			}
		}
		rightend->next=leftend->next=midend->next=NULL;
		left->next=quickSortList(left->next);
		right->next=quickSortList(right->next);
		
		ListNode* p=get_end(left);//可以直接写成   get_end(left->next)->next=mid->next;
		p->next=mid->next;
		
		p=get_end(left);
		p->next=right->next;

		auto p1=left->next;
		delete left;  //注意删除结点，好习惯
		delete mid;
		delete right;
		return p1;
    }
}
//
思路就是创建左中右三个链表，小于第一个值的放左边，等于放中间，大于放右边，然后分别对左中右三个链表排序，最后连起来
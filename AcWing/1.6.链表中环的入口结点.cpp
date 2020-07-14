//6.34. 链表中环的入口结点 
给定一个链表，若其中包含环，则输出环的入口节点。
若其中不包含环，则输出null。
样例
 
给定如上所示的链表：
[1, 2, 3, 4, 5, 6]
2
注意，这里的2表示编号是2的节点，节点编号从0开始。所以编号是2的节点就是val等于3的节点。

则输出环的入口节点3.



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
    ListNode *entryNodeOfLoop(ListNode *head) {
        ListNode* f,s;
		f=head;
		s=head;
		while(f&&s){
			s=s->next;
			f=f->next;
			f=f->next;
			if(s==f){
				s=head;
				while(s!=f){
					s=s->next;
					f=f->next;
				}
				return s;
			}
		}
		return NULL;
    }
};


//这道题题解见：https://www.acwing.com/solution/AcWing/content/741/
//这道题还可以通过map来解，把已经访问过的节点存入map中，然后再次访问就输出
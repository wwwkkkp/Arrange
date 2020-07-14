



面试题 02.01. 移除重复节点
编写代码，移除未排序链表中的重复节点。保留最开始出现的节点。

示例1:

 输入：[1, 2, 3, 3, 2, 1]
 输出：[1, 2, 3]
示例2:

 输入：[1, 1, 1, 1, 2]
 输出：[1, 2]
提示：

链表长度在[0, 20000]范围内。
链表元素在[0, 20000]范围内。
进阶：

如果不得使用临时缓冲区，该怎么解决？  //直接暴力搜，遍历每一个结点，找出链表中与该结点相同的结点，然后删除，时间复杂度O(N^2)



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
    ListNode* removeDuplicateNodes(ListNode* head) {
        unordered_set<int>us;
        auto t=head;
        if(!t)return NULL;
        auto t1=t->next;
        us.insert(t->val);
        while(t1){
            while(t1&&us.find(t1->val)!=us.end()){
                t->next=t1->next;
                t1=t->next;
            }
            if(t1){us.insert(t1->val);t1=t1->next;}
            t=t->next;
        }
        return head;
    }
};
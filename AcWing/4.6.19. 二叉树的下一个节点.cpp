//24.19. 二叉树的下一个节点 
给定一棵二叉树的其中一个节点，请找出中序遍历序列的下一个节点。
注意：
如果给定的节点是中序遍历序列的最后一个，则返回空节点;
二叉树一定不为空，且给定的节点一定不是空节点；
样例
假定二叉树是：[2, 1, 3, null, null, null, null]， 给出的是值等于2的节点。

则应返回值等于3的节点。

解释：该二叉树的结构如下，2的后继节点是3。
  2
 / \
1   3


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode *father;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL), father(NULL) {}
 * };
 */
 
 //其实就是寻找比该结点大的最小的那个结点
 
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* p) {
        if(p->right){  //如果有右儿子，那就是右儿子的最左边的儿子，
			p=p->right;
			while(p->left)p=p->left;
			return p;
		}
		else {
			while(p->father){  
				if(p->father->left==p) //如果该结点的父结点的左儿子是该结点，那就是这个父结点，如果不是就一路往上倒，直到根结点，
					return p->father;
				p=p->father;
			}
			return NULL;
		}	
    }
};
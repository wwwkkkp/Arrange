//23.18. 重建二叉树 

输入一棵二叉树前序遍历和中序遍历的结果，请重建该二叉树。
注意:
二叉树中每个节点的值都互不相同；
输入的前序遍历和中序遍历一定合法；
样例
给定：
前序遍历是：[3, 9, 20, 15, 7]
中序遍历是：[9, 3, 15, 20, 7]

返回：[3, 9, 20, null, null, 15, 7, null, null, null, null]
返回的二叉树如下所示：
    3
   / \
  9  20
    /  \
   15   7
   
   
   
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
 
 //前序中序还原
 
class Solution {
public:
	vector<int> pe,in;
	unordered_map<int,int>up;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        pe=preorder;
		in=inorder;
		for(int i=0;i<pe.size();i++)
			up[in[i]]=i;
		
		return dfs(0,pe.size()-1,0,in.size()-1);
    }
	
	TreeNode* dfs(int pl,int pr,int il,int ir){  //前序起点终点，中序起点终点的构成的树的头结点
		if(pl>pr) return NULL;
		TreeNode* a=new TreeNode(pe[pl]);
		int n=up[pe[pl]];
		TreeNode* left=dfs(pl+1,n-il+pl,il,n-1);  
		TreeNode* right=dfs(n-il+pl+1,pr,n+1,ir);
		a->left=left;
		a->right=right;
		return a;
	}
};
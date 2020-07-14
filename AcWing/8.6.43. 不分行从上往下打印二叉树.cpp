//8.6.43. 不分行从上往下打印二叉树 

输入如下图所示二叉树[8, 12, 2, null, null, 6, null, 4, null, null, null]
    8
   / \
  12  2
     /
    6
   /
  4

输出：[8, 12, 2, 6, 4]


//bfs

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> printFromTopToBottom(TreeNode* root) {
        queue<TreeNode*>q;
		vector<int>v;
		if(!root)return v;
		
		q.push_back(root);
		while(q.size()){
			auto p=q.front();q.pop();
			v.push_back(p->val);
			if(p->left)
				q.push_back(p->left);
			if(p->right)
				q.push_back(p->right);
		}
		return v;
    }
};



//111. 二叉树的最小深度
给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

说明: 叶子节点是指没有子节点的节点。

示例:

给定二叉树 [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回它的最小深度  2.



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
    int n=INT_MAX;
    int minDepth(TreeNode* root) {
        if(!root)return 0;
        dfs(root,1);
        return n;
    }
    void dfs(TreeNode* root,int a){
        if(!root->left&&!root->right){ //深度的结束语句是没有子树
            n=min(n,a);
            return ;
        }
        if(root->left)dfs(root->left,a+1);
        if(root->right)dfs(root->right,a+1);
    }
};
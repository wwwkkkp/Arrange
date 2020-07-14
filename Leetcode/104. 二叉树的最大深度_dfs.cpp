

//104. 二叉树的最大深度
给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

说明: 叶子节点是指没有子节点的节点。

示例：
给定二叉树 [3,9,20,null,null,15,7]，

    3
   / \
  9  20
    /  \
   15   7
返回它的最大深度 3 。



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //dfs
class Solution {
public:
    int n=0;
    int maxDepth(TreeNode* root) {
        if(!root)return 0;
        work(root,0);
        return n;
    }
    void work(TreeNode* root,int le){
        if(!root){
            n=max(n,le);
            return ;
        }
        work(root->left,le+1);
        work(root->right,le+1);
    }
};
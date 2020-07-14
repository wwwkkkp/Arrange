

//124. 二叉树中的最大路径和
给定一个非空二叉树，返回其最大路径和。

本题中，路径被定义为一条从树中任意节点出发，达到任意节点的序列。该路径至少包含一个节点，且不一定经过根节点。

示例 1:

输入: [1,2,3]

       1
      / \
     2   3

输出: 6
示例 2:

输入: [-10,9,20,null,null,15,7]

   -10
   / \
  9  20
    /  \
   15   7

输出: 42


//深搜
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
    int res=INT_MIN;    //全局变量，记录最大路径和
    int maxPathSum(TreeNode* root) {
        if(!root)return 0;
        
        dfs(root);
        return res;
        
    }
    int dfs(TreeNode* r){  //以r为起始结点的最大路径和
        if(!r)return 0;
        
        int leftmax=max(0,dfs(r->left));		//左边的最大路径和
        int rightmax=max(0,dfs(r->right));		//右边的最大路径和
        res=max(res,r->val+leftmax+rightmax);     //两边的最大路径和+当前的结点数，就是以当前节点为连接点的最大路径和
        return r->val+max(leftmax,rightmax);	//返回的是以r为起点的最大路径和
    }
};




//这个有点复杂，6.20
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
    int maxl=INT_MIN,co=0,m=INT_MIN;
    int maxPathSum(TreeNode* root) {
        if(!root)return 0;
        int ml=0,mr=0;
        if(root->left){
            dfs(root->left);			//左边最大和
            ml=maxl;maxl=INT_MIN;co=0;
        }
        if(root->right){
            dfs(root->right);			//右边最大和
            mr=maxl;maxl=INT_MIN;co=0;
        }

        int k=max(root->val+ml+mr,max(root->val,max(root->val+ml,root->val+mr)));
        m=max(m,k);

        maxPathSum(root->left);
        maxPathSum(root->right);
        return m;
        
    }
    void dfs(TreeNode *r){
        if(!r)return ;
        co+=r->val;
        maxl=max(maxl,co);
        dfs(r->left);
        if(r->left)co-=r->left->val;
        dfs(r->right);
        if(r->right)co-=r->right->val;
    }
};


//112. 路径总和
给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。

说明: 叶子节点是指没有子节点的节点。

示例: 
给定如下二叉树，以及目标和 sum = 22，

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
返回 true, 因为存在目标和为 22 的根节点到叶子节点的路径 5->4->11->2。


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

    bool hasPathSum(TreeNode* root, int sum) {
        return dfs(root,sum);
    }
    bool dfs(TreeNode* root,int a){
        if(!root)return false;			 //这个为空是父结点一边为空的情况
        if(!root->left&&!root->right){   //注意：判断树是否到叶子结点，要判断左右子树都要为空才行，
            if(a-root->val==0)return true;   
            return false;
        }
        if( dfs(root->left,a-root->val) || dfs(root->right,a-root->val)) return true;
        return false;   
    }
};


//7.7版本  //上个例子是直接减去和，这个例子要回溯，所以麻烦些，以后还是用减吧
class Solution {
public:
    int s=0;
    bool hasPathSum(TreeNode* root, int &sum) {
        if(!root)return false;
        
        s+=root->val;
        if(root->left==NULL&&root->right==NULL){
            if(sum==s){
                return true;
            }
            s-=root->val;				//子结点的回溯
            return false;
        }
		
        bool a=hasPathSum(root->left,sum);
        bool b=hasPathSum(root->right,sum);
        if(a||b)return true;
        s-=root->val;					//非子节点的回溯
        return false;
    }
};
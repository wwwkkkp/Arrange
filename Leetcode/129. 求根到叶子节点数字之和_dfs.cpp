
//129. 求根到叶子节点数字之和
给定一个二叉树，它的每个结点都存放一个 0-9 的数字，每条从根到叶子节点的路径都代表一个数字。

例如，从根到叶子节点路径 1->2->3 代表数字 123。

计算从根到叶子节点生成的所有数字之和。

说明: 叶子节点是指没有子节点的节点。

示例 1:

输入: [1,2,3]
    1
   / \
  2   3
输出: 25
解释:
从根到叶子节点路径 1->2 代表数字 12.
从根到叶子节点路径 1->3 代表数字 13.
因此，数字总和 = 12 + 13 = 25.
示例 2:

输入: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
输出: 1026
解释:
从根到叶子节点路径 4->9->5 代表数字 495.
从根到叶子节点路径 4->9->1 代表数字 491.
从根到叶子节点路径 4->0 代表数字 40.
因此，数字总和 = 495 + 491 + 40 = 1026.


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
    int sum=0;
    int sumNumbers(TreeNode* root) {
        if(!root)return sum;
        
        dfs(root,0);
        return sum;
    }
    void dfs(TreeNode* root,int s){
        if(!root->left&&!root->right){
            s=s*10+root->val;
            sum+=s;
            return ;
        }
        
        if(root->left){           
            dfs(root->left,s*10+root->val);
        }
        if(root->right){
            dfs(root->right,s*10+root->val);
        }
    }
};


 //如果结点大小任意
class Solution {
public:
    int sum=0;
    int sumNumbers(TreeNode* root) {
        if(!root)return sum;
        
        dfs(root,0);
        return sum;
    }
    void dfs(TreeNode* root,int s){
        if(!root->left&&!root->right){
            int b=root->val;
            int i=0;
            if(!b)i=1;
            else
                while(b>0){
                    b=b/10;
                    i++;
                }     
            s=s*pow(10,i)+root->val;
            sum+=s;
            return ;
        }
        
        int b=root->val;
        int i=0;
        if(!b)i=1;
        else
            while(b>0){
                b=b/10;
                i++;
            }
        
        if(root->left){           
            dfs(root->left,s*pow(10,i)+root->val);
        }
        if(root->right){
            dfs(root->right,s*pow(10,i)+root->val);
        }
    }
};
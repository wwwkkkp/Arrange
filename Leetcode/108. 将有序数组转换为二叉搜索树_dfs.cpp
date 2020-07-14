


//108. 将有序数组转换为二叉搜索树
将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。

本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

示例:

给定有序数组: [-10,-3,0,5,9],

一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：

      0
     / \
   -3   9
   /   /
 -10  5


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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return dfs(nums,0,nums.size()-1);
    }
    TreeNode* dfs(vector<int>& nums,int a,int b){
        if(a>b)return NULL;
        if(a==b){
            TreeNode* t=new TreeNode(nums[a]);
            return t;
        }
        int x=a+b+1>>1;	//当中间数是一个的时候，那父结点就是他本身，如果中间数有两个，这里选择较大的那一个
        TreeNode* t=new TreeNode(nums[x]);
        t->left=dfs(nums,a,x-1);
        t->right=dfs(nums,x+1,b);
        return t;
    }
};

//7.3版本
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int n=nums.size();
        if(n==0)return NULL;
        if(n==1)return new TreeNode(nums[0]);
        
        int n1=n/2;
        TreeNode* head=new TreeNode(nums[n1]);
        
        vector<int>v2(nums.begin(),nums.begin()+n1);
        head->left=sortedArrayToBST(v2);
        
        vector<int>v1(nums.begin()+n1+1,nums.end());
        head->right=sortedArrayToBST(v1);
        return head;
    }
};
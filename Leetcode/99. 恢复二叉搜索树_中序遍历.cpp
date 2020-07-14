
//99. 恢复二叉搜索树
二叉搜索树中的两个节点被错误地交换。

请在不改变其结构的情况下，恢复这棵树。

示例 1:

输入: [1,3,null,null,2]

   1
  /
 3
  \
   2

输出: [3,1,null,null,2]

   3
  /
 1
  \
   2
示例 2:

输入: [3,1,4,null,null,2]

  3
 / \
1   4
   /
  2

输出: [2,1,4,null,null,3]

  2
 / \
1   4
   /
  3
进阶:

使用 O(n) 空间复杂度的解法很容易实现。
你能想出一个只使用常数空间的解决方案吗？



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
 //中序遍历得到数组，正常是单调递增的，所以和单调递增的正常数组比较，找出两个结点，再遍历一遍树，交换两个值
class Solution {
public:
    vector<int>v;
    int minl=INT_MAX,maxl=INT_MIN,n;
    int k[2];
    void recoverTree(TreeNode* root) {
        work(root);
        if(!n)return;
        vector<int>v1(v.begin(),v.end());
        sort(v1.begin(),v1.end());
        
        int j=0;
        for(int i=0;i<n;i++){
            if(v1[i]!=v[i])k[j++]=v1[i];
        }
        work1(root);
        return ;
    }
    void work(TreeNode* root)
    {
        if(!root)return ;
        work(root->left);
        v.push_back(root->val);
        minl=min(minl,root->val);
        maxl=max(maxl,root->val);
        n++;
        work(root->right);
    }
    
    void work1(TreeNode* root){
        if(!root)return ;
        work1(root->left);
        if(root->val==k[1])root->val=k[0];
        else if(root->val==k[0])root->val=k[1];
        work1(root->right);
    }
};
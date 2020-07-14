
//107. 二叉树的层次遍历 II
给定一个二叉树，返回其节点值自底向上的层次遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

例如：
给定二叉树 [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回其自底向上的层次遍历为：

[
  [15,7],
  [9,20],
  [3]
]



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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if(!root)return {};
        vector<vector<int>>v;
        queue<pair<TreeNode*,int>>q;
        q.push({root,1});
        vector<int>v1;
        while(q.size()){
            auto w=q.front();
            q.pop();
            auto a=w.first;
            int b=w.second;
            if(b-v.size()==1){
                v1.push_back(a->val);
            }else{
                v.push_back(v1);
                v1.clear();
                v1.push_back(a->val);
            }
            if(a->left)q.push({a->left,b+1});
            if(a->right)q.push({a->right,b+1});
        }
        v.push_back(v1);//注意最后要把最后一行添加进去
        reverse(v.begin(),v.end());
        return v;
    }
};
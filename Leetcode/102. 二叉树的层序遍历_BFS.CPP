

//102. 二叉树的层序遍历

给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。

 

示例：
二叉树：[3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回其层次遍历结果：

[
  [3],
  [9,20],
  [15,7]
]


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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>v;
        if(!root)return v;
        
        queue<pair<TreeNode*,int>>q; //后面的int是层号
        q.push({root,0});
        vector<int>v1;
        while(q.size()){
            auto w=q.front();
            q.pop();
            int a=w.first->val;
            int b=w.second;
            if(v.size()==b){ //层号有没有变，
                v1.push_back(a);
            } else{
                v.push_back(v1);
                v1.clear();
                v1.push_back(a);
            }
            if(w.first->left)q.push({w.first->left,b+1});
            if(w.first->right)q.push({w.first->right,b+1});
        }
        v.push_back(v1);
        return v;
    }
};
/* 5296. 两棵二叉搜索树中的所有元素

给你 root1 和 root2 这两棵二叉搜索树。

请你返回一个列表，其中包含 两棵树 中的所有整数并按 升序 排序。.

示例 1：


输入：root1 = [2,1,4], root2 = [1,0,3]
输出：[0,1,1,2,3,4]
示例 2：

输入：root1 = [0,-10,10], root2 = [5,1,7,0,2]
输出：[-10,0,0,1,2,5,7,10]
示例 3：

输入：root1 = [], root2 = [5,1,7,0,2]
输出：[0,1,2,5,7]
示例 4：

输入：root1 = [0,-10,10], root2 = []
输出：[-10,0,10]
示例 5：

输入：root1 = [1,null,8], root2 = [8,1]
输出：[1,1,8,8]
 

提示：

每棵树最多有 5000 个节点。
每个节点的值在 [-10^5, 10^5] 之间。

*/


//暴力排列
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
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int>v1;
        queue<TreeNode*>q;
        if(root1!=NULL){
            q.push(root1);
            while(!q.empty()){
                TreeNode* a=q.front();
                q.pop();
                v1.push_back(a->val);
                if(a->right)
                    q.push(a->right);
                if(a->left)
                    q.push(a->left);
            }
        }
        if(root2!=NULL){
            q.push(root2);
            while(!q.empty()){
                TreeNode* a=q.front();
                q.pop();
                v1.push_back(a->val);
                if(a->right)
                    q.push(a->right);
                if(a->left)
                    q.push(a->left);
            }
        }
        sort(v1.begin(),v1.end());
        return v1;
    }
};
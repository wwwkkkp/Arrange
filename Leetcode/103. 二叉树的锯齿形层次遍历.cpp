/*  103. 二叉树的锯齿形层次遍历
给定一个二叉树，返回其节点值的锯齿形层次遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

例如：
给定二叉树 [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回锯齿形层次遍历如下：

[
  [3],
  [20,9],
  [15,7]
]

*/


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
    vector<vector<int>> Vec;
    void BFS(TreeNode* root){
        if(!root)
            return;
        int j=0;
        queue<vector<TreeNode*>>q;
        vector<TreeNode*> x;
        x.push_back(root);
        q.push(x);
        while(!q.empty()){
            vector<TreeNode*> m=q.front();
            vector<TreeNode*> n;
            vector<int> it;
            q.pop();
            int s=m.size();
            for(int i=0;i<s;i++){
                it.push_back(m[i]->val);
                if(m[i]->left)
                    n.push_back(m[i]->left);
                if(m[i]->right)
                    n.push_back(m[i]->right);
            }
            if(n.size())q.push(n);
            int k=it.size();
			/* //奇偶校验，两种方法，方法二效率更高
			
            if(j%2==1)
                for(int i=0;i<k/2;i++)
                    swap(it[i],it[k-1-i]);
            Vec.push_back(it);
			
			*/
			/*
			
			if(j%2==1){
                vector<int> reverse_t(it.rbegin(), it.rend());  //翻转it，it.rbegin(),返回的是it的最后一个值，这是逆序迭代器，it.end()是顺序迭代器
                Vec.push_back(reverse_t);
            }else
                Vec.push_back(it);
			
			*/
            j++;
        }

    }
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        BFS(root);
        return Vec;
    }
};



//114. 二叉树展开为链表
给定一个二叉树，原地将它展开为一个单链表。

 

例如，给定二叉树

    1
   / \
  2   5
 / \   \
3   4   6
将其展开为：

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6



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
class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root)return;
        stack<TreeNode*>s;

        auto k = root;
        while (s.size() || k) {
            while (k) {
                s.push(k);
                k = k->left;
            }
            k = s.top(); s.pop();
            auto p = k->left;
            auto q = k->right;
            k->left = NULL;
            k->right = p;
            while(k->right)k=k->right;//这里应该是从k往下右下遍历，因为p可能是null,而q是有值的，这样就连不上了
            k->right=q;
            k = q;
        }
        return;
    }
};
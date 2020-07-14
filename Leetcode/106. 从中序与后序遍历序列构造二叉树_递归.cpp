/*106. 从中序与后序遍历序列构造二叉树
根据一棵树的中序遍历与后序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出

中序遍历 inorder = [9,3,15,20,7]
后序遍历 postorder = [9,15,7,20,3]
返回如下的二叉树：

    3
   / \
  9  20
    /  \
   15   7

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
 
 //递归 ，105题类似
class Solution {
public:
                       //中序数组                后序数组     中序开始位置    中序长度-1      后序开始位置         后序长度-1
    TreeNode* DFS(vector<int>& inorder, vector<int>& postorder, int inst,      int inLen,    int post,            int poLen) {
        if (inLen < 0 ) 
            return NULL;
        if (inLen == 0) {
            TreeNode* s = new TreeNode(inorder[inst]);  //注意赋值形式
            return s;
        }
        TreeNode* s = new TreeNode(postorder[post + poLen]);
        int i;
        for (i = inst; i <= inst + inLen; i++) 
            if (inorder[i] == postorder[post + poLen]) break; //找到后序最后一个数在中序的位置，把中序分成前后两部分，即前后两子树
		
        s->left = DFS(inorder, postorder, inst, i - 1 - inst, post, i - 1 - inst);
		
        s->right = DFS(inorder, postorder, i + 1, inst + inLen - i - 1, post + i - inst, inst + inLen - i - 1);
		
        return s;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        TreeNode* s = DFS(inorder, postorder, 0, n - 1, 0, n - 1);
        return s;
    }
};
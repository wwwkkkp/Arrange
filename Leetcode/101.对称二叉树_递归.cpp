//101.对称二叉树
/*
给定一个二叉树，检查它是否是镜像对称的。

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

    1
   / \
  2   2
 / \ / \
3  4 4  3


但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

    1
   / \
  2   2
   \   \
   3    3

*/


//注意，这道题不能用中序遍历，，因为他不是严格的二叉树，可能存在左子树中的数全是2，右子树的数也全是2，再这样就无法分辨，反例：[1,2,2,2,null,2]
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
    bool isright(TreeNode* t,TreeNode* s){ //基本递归，左边树的左边是否等于右边树的右边，左边树的右边是否等于右边的左边
        if(t==NULL&&s==NULL)
            return true;
        if((!t&&s)||(!s&&t)||(s->val!=t->val))
            return false;
        bool a,b;
        if(t->val==s->val){
            a=isright(t->right,s->left);
            b=isright(t->left,s->right);
        }
        if(a&&b)
            return true;
        return false;  
    }
    bool isSymmetric(TreeNode* root) {
        if(!root)
            return true;
        bool ju=isright(root->left,root->right);
        return ju;
    }
};


//5.31版本
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(!root)return true;
        if(!root->left&&!root->right)return true;
        if(!root->left||!root->right)return false;
        return isd(root->left,root->right);
    }
    bool isd(TreeNode* a,TreeNode* b){
        if(!a&&!b)return true;
        if(!a||!b)return false;
        if(a->val==b->val){
            return isd(a->right,b->left)&&isd(a->left,b->right);   
        }
        return false;
    }
};
/*
方法二：迭代
除了递归的方法外，我们也可以利用队列进行迭代。队列中每两个连续的结点应该是相等的，
而且它们的子树互为镜像。最初，队列中包含的是 root 以及 root。该算法的工作原理类似于 BFS，但存在一些关键差异。每次提取两个结点并比较它们的值。
然后，将两个结点的左右子结点按相反的顺序插入队列中。当队列为空时，或者我们检测到树不对称（即从队列中取出两个不相等的连续结点）时，该算法结束。
*/
//附java解法

Javapublic boolean isSymmetric(TreeNode root) {
    Queue<TreeNode> q = new LinkedList<>();
    q.add(root);  //成套存入，成套取出
    q.add(root);
    while (!q.isEmpty()) {
        TreeNode t1 = q.poll();
        TreeNode t2 = q.poll();
        if (t1 == null && t2 == null) continue;
        if (t1 == null || t2 == null) return false;
        if (t1.val != t2.val) return false;
        q.add(t1.left);  //按照相反的顺序添加进队列
        q.add(t2.right);
        q.add(t1.right);
        q.add(t2.left);
    }
    return true;
}


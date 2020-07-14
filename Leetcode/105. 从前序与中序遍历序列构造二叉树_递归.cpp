//105. 从前序与中序遍历序列构造二叉树
/*
根据一棵树的前序遍历与中序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]

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
 
 //递归方法
class Solution {
public:
																
    TreeNode* PIbuildTree(vector<int>& preorder, vector<int>& inorder,int begin,		int begin_i,				int lenght){ 
														//begin:前序数组开始的位置，begin_i:中序数组开始的位置，lenght：要处理段的长度
        if(lenght==0){
            TreeNode* node=NULL;  
            return node;    
        }      
        if(lenght==1){
            TreeNode* node=new TreeNode(preorder[begin]);
            return node;     
        }        
        TreeNode* root=new TreeNode(preorder[begin]);  //前序第一个数就是root，根结点的位置
        int i;
        for( i=0;i<lenght;i++){
            if(inorder[begin_i+i]==preorder[begin])  //寻找前序第一个数的在中序的位置，这样就可以把树分来
            break;
        }
        root->left=PIbuildTree(preorder,inorder,begin+1,begin_i,i);
        root->right=PIbuildTree(preorder,inorder,begin+i+1,begin_i+i+1,lenght-i-1);
        return root;

    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode* root=PIbuildTree(preorder,inorder,0,0,preorder.size());
        return root;
    }
};

//非递归方法，比较巧妙，比较难理解
TreeNode* buildTree(vector<int>& pre, vector<int>& in) {
  if (pre.empty()) return NULL;
  stack<TreeNode*> S;
  TreeNode* root = new TreeNode(pre[0]);
  S.push(root);
  for (int i = 1, j = 0; i < pre.size(); i++) {  // i-前序序号，j-中序序号
    TreeNode *back = NULL, *cur = new TreeNode(pre[i]);
    while (!S.empty() && S.top()->val == in[j]) back = S.top(), S.pop(), j++;  
	//while比较妙，如果S.top()->val ！= in[j]，那该数就填在左子树上，相等就填在右子树上，因为每一个前序结点都是父结点，后面跟的是左子树和右子树
    if (back)
      back->right = cur;
    else
      S.top()->left = cur;
    S.push(cur);
  }
  return root;
}
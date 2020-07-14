//98. 验证二叉搜索树



/*
给定一个二叉树，判断其是否是一个有效的二叉搜索树。

假设一个二叉搜索树具有如下特征：


	节点的左子树只包含小于当前节点的数。
	节点的右子树只包含大于当前节点的数。
	所有左子树和右子树自身必须也是二叉搜索树。


示例 1:

输入:
    2
   / \
  1   3
输出: true


示例 2:

输入:
    5
   / \
  1   4
     / \
    3   6
输出: false
解释: 输入为: [5,1,4,null,null,3,6]。
     根节点的值为 5 ，但是其右子节点值为 4 。

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
 
 
 //利用中序遍历，二叉搜索树的顺序应该是从小到大  堆栈法
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        vector<int>Vec;
        stack<TreeNode*>s;
        TreeNode* rt= root;
        while(rt||!s.empty()){
            while(rt){
                s.push(rt);
                rt=rt->left;
            }
            rt=s.top();
            s.pop();
            
            Vec.push_back(rt->val);
            int size=Vec.size();
            if(size>=2&&Vec[size-1]<=Vec[size-2])
                return false;
            rt=rt->right; 
        }
        return true;
    }
};

//同样是中序遍历 递归法，下一个访问的结点的值要小于上一个结点的值
//递归法的中序遍历

class Solution {
 public:
	 long last = LONG_MIN; // 父节点值
	 bool flag = true; // 父亲结点是否大于子节点
	 bool isValidBST(TreeNode* root) {
		 if (!root)
			 return true;

		 // 遍历左子树
		 if (flag && root->left)
			 isValidBST(root->left);

		 // 当前结点不大于父节点，不是排序二叉树
		 if (root->val <= last)                     //下一个访问的结点的值要小于上一个结点的值，否则就不成立
			 flag = false;

		 last = root->val; // 记录父节点值   

		 // 遍历右子树
		 if (flag && root->right)
			 isValidBST(root->right);

		 // 子树都遍历完 或 不是二叉排序树，就退出
		 return flag;
	 }
 };
 
 
 //递归 查找   有点意思
class Solution {
public:
bool check(TreeNode* root, long lower, long upper) { //检查root是否满足二叉树条件，同时是否满足最小值和最大值之间
	if (!root) {
		return true;
	}
	else {
		bool left = true;
		bool right = true;
		if (root->left) {
			if (root->left->val <= lower || root->left->val >= upper || root->left->val >= root->val) {
			  return false;
			}
			else {
			  left = check(root->left, lower, root->val);  //遍历左边的时候，最大值就是根的值
			}
		}
		if (root->right) {
			if (root->right->val <= lower || root->right->val >= upper || root->right->val <= root->val) {
			  return false;
			}
			else {
			  right = check(root->right, root->val, upper);//遍历右边的时候，最小值就是原来根的值，最大值是无穷大
			}
		}
		return left && right;
		}
}

bool isValidBST(TreeNode* root) {
    if (!root) {
		return true;
    }
    else {
		return check(root,LONG_MIN,LONG_MAX); // 有 INT_MAX INT_MIN输入样例 需要更大的数据
    }
  }
};

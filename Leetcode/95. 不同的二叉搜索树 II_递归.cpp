


95. 不同的二叉搜索树 II
给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。

示例:

输入: 3
输出:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
解释:
以上的输出对应以下 5 种不同结构的二叉搜索树：

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

//递归，
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
    
    vector<TreeNode*> generateTrees(int n) {
        if(!n)return {};
        return work(1,n);
    }
    
    vector<TreeNode*>work(int a,int b){ //[a,b]区间内的搜索树集合
        if(a>b)return {NULL};
        vector<TreeNode*>v;
        for(int i=a;i<=b;i++){
            TreeNode* t=new TreeNode(i);
            vector<TreeNode*>v1=work(a,i-1);
            vector<TreeNode*>v2=work(i+1,b);

            for(TreeNode* c1:v1){
                for(TreeNode* c2:v2){
                    TreeNode* c3=new TreeNode(t->val);
					//这道题有一个陷阱，就是当返回的是vector<TreeNode*>时，放进vector中的结点要是新建的，不能在原来的t的基础上改，不然后面改的把前面放进vector中的结点都改了，其实他们是同一个结点
                    c3->right=c2;
                    c3->left=c1;
                    v.push_back(c3);
                }
            }
        }
        
        return v;
    }
};
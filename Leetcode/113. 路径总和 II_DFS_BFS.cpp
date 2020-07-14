/*  113. 路径总和 II

给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。

说明: 叶子节点是指没有子节点的节点。

示例:
给定如下二叉树，以及目标和 sum = 22，

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
		
[5,4,8,11,null,13,4,7,2,null,null,5,1]
22
返回:

[
   [5,4,11,2],
   [5,8,4,5]
]

例2：

inport:
[-2,null,-3]
-5
outport:

[[-2,-3]]


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
 
// BFS
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        queue<vector<TreeNode*>> q;
        vector<vector<int>> out1;
        if(!root)
            return  out1;
        vector<TreeNode*> t;
        t.push_back(root);
        q.push(t);
        while(!q.empty()){
            vector<TreeNode*> t1=q.front();
            q.pop();
            
            TreeNode* pro=t1[t1.size()-1];
            vector<TreeNode*> t2;
            t2=t1; //加t2防止串了，
            
            if(pro->left){
                t2.push_back(pro->left);
                q.push(t2);                    
                
            }
            t2=t1;
            if(pro->right){
                t2.push_back(pro->right);
                q.push(t2);                    
            }
            
            if(!pro->left&&!pro->right){  //如果左右子树都没有，说明到底了。就输出，如果和等于sum，就收入。
                vector<int>Vec;
                int sum1=0;
                for(int i=0;i<t1.size();i++){
                    sum1+=t1[i]->val;
                    Vec.push_back(t1[i]->val);
                }
                if(sum1==sum)
                    out1.push_back(Vec);
            }
        }
        return out1;
    }
};


//回溯

class Solution {
public:
    vector<vector<int>>out1;
			//结点          路径值记录     参考    路径和
    void DFS(TreeNode* root,vector<int>&s,int sum,int sum1){ //这个函数的意思是当在结点root的时候，走过的路径和是多少
		//注意上面第二个参数，vector<int>&s，如果写成vector<int>s，就是赋值，如果写成vector<int>&s，就是引用，引用可以使时间复杂度和空间复杂度都要减少很多
        if(root->left==NULL && root->right==NULL){
            if(sum1==sum)
                out1.push_back(s);
            return;
        }
		
        if(root->left){
            s.push_back(root->left->val);
            DFS(root->left,s,sum,sum1+root->left->val);
            s.pop_back();
        }
        if(root->right){
            s.push_back(root->right->val);
            DFS(root->right,s,sum,sum1+root->right->val);
            s.pop_back();            
        }
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if(!root)
            return out1;
        vector<int>s;
        s.push_back(root->val);
        int sum1=root->val;
        DFS(root,s,sum,sum1);
        return out1;
    }
};
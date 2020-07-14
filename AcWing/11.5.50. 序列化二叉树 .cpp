
//11.5.50. 序列化二叉树 
请实现两个函数，分别用来序列化和反序列化二叉树。
您需要确保二叉树可以序列化为字符串，并且可以将此字符串反序列化为原始树结构。
样例
你可以序列化如下的二叉树
    8
   / \
  12  2
     / \
    6   4

为："[8, 12, 2, null, null, 6, 4, null, null, null, null]"
注意:
以上的格式是AcWing序列化二叉树的方式，你不必一定按照此格式，所以可以设计出一些新的构造方式。
//简单的说就是给一个二叉树，先将其转换成string，再转换成原来的二叉树，

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

    // Encodes a tree to a single string.转化成string
    string serialize(TreeNode* root) {
        string s;
        if(!root)return s;
        dfs_s(root,s);
        return s;
    }
    void dfs_s(TreeNode* t,string &s){ //注意这里用的是 &s，意思就是在后面递归过程中，用的都是同一个s，而不是另外开辟空间存储s
        if(!t){
            s+="null ";
            return ;
        }
        s+=to_string(t->val)+" ";//前序遍历转化，
        dfs_s(t->left,s);
        dfs_s(t->right,s);
    }


    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int u=0;
        return dfs_d(data,u);
    }
    TreeNode* dfs_d(string s,int &u){ //u表示遍历s的第u个元素，也是全局变量
        int k=u;
        if(s[u]=='n'||k==s.size()){
            while(k<s.size()&&s[k]!=' ')k++;
            u=k+1;
            return NULL;
        }
        int val=0,si=1;
        if(s[k]=='-')si=-1,k++;
        for(;k<s.size()&&s[k]!=' ';k++)val=val*10+s[k]-'0';
        val*=si;
        u=k+1;
        TreeNode* t=new TreeNode(val);//用前序遍历转化成string，就要用前序遍历转化回来
        t->left=dfs_d(s,u);
        t->right=dfs_d(s,u);
        return t;
    }
};
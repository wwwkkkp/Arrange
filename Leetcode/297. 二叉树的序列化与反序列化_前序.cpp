
297. 二叉树的序列化与反序列化
序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

示例: 

你可以将以下二叉树：

    1
   / \
  2   3
     / \
    4   5

序列化为 "[1,2,3,null,null,4,5]"
提示: 这与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode 序列化二叉树的格式。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。

说明: 不要使用类的成员 / 全局 / 静态变量来存储状态，你的序列化和反序列化算法应该是无状态





/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root)return "";
        string s;
        dfs_s(root,s);
        s.erase(s.end()-1);
        return s;
    }
    void dfs_s(TreeNode* r,string &s){
        if(!r){s+="NULL,";return;}
        s+=to_string(r->val);
        s+=',';
        dfs_s(r->left,s);
        dfs_s(r->right,s);
        return ;
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string s) {			//反序列化只能用前序遍历去完成，不能用层序，所以上面的序列化需要和反序列化配套，所以才可以使用
        int u=0;
        return dfs_d(s,u);
    }
    TreeNode* dfs_d(string s,int &u){
        int k=u;
        if(s[u]=='N'||k==s.size()){
            while(k<s.size()&&s[k]!=',')k++;
            u=k+1;
            return NULL;
        }
        int val=0,s1=1;
        if(s[u]=='-')s1=-1,k++;
        while(k<s.size()&&s[k]!=','){val=val*10+s[k]-'0';k++;}
        val*=s1;
        u=k+1;
        TreeNode* t=new TreeNode(val);
        t->left=dfs_d(s,u);
        t->right=dfs_d(s,u);
        return t;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
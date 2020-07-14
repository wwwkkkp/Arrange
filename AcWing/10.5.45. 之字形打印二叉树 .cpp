
//10.5.45. 之字形打印二叉树 

请实现一个函数按照之字形顺序从上向下打印二叉树。
即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。
样例
输入如下图所示二叉树[8, 12, 2, null, null, 6, 4, null, null, null, null]
    8
   / \
  12  2
     / \
    6   4
输出：[[8], [2, 12], [6, 4]]


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
    vector<vector<int>> printFromTopToBottom(TreeNode* root) {
        vector<vector<int>>v;
        queue<pair<TreeNode*,int>>q;
        if(!root) return v;
        q.push({root,0});
        int k1=0;
        vector<int>v1;
        while(q.size()){
            auto a=q.front();
            q.pop();
            TreeNode* t=a.first;
            int k=a.second;
            if(k1==k)v1.push_back(t->val);//遇到k不一样，说明换行了
            else{
                if(k1%2==0)v.push_back(v1);//变换放向
                else{ 
                    reverse(v1.begin(),v1.end());
                    v.push_back(v1);
                }
                k1=k;
                v1.clear();
                v1.push_back(t->val);
            }
            if(t->left)q.push({t->left,k+1});
            if(t->right)q.push({t->right,k+1});
        }
        if(k1%2==0)v.push_back(v1);//变换放向
        else{ 
            reverse(v1.begin(),v1.end());
            v.push_back(v1);
        }
    }
};

//y总写法
vector<int> get_val(vector<TreeNode*> level)
{
	vector<int> res;
	for (auto &u : level)
		res.push_back(u->val);
	return res;
}

vector<vector<int>> printFromTopToBottom(TreeNode* root) {
	vector<vector<int>>res;
	if (!root) return res;
	vector<TreeNode*>level;
	level.push_back(root);
	res.push_back(get_val(level));
	bool zigzag = true;
	while (true)
	{
		vector<TreeNode*> newLevel;
		for (auto &u : level)
		{
			if (u->left) newLevel.push_back(u->left);//每一层每一层的遍历，放在vector中，访问完以后，提出数据，迭代vector
			if (u->right) newLevel.push_back(u->right);
		}
		if (newLevel.size())
		{
			vector<int>temp = get_val(newLevel);
			if (zigzag)
				reverse(temp.begin(), temp.end());
			res.push_back(temp);
			level = newLevel;
		}
		else break;
		zigzag = !zigzag;
	}
	return res;
}    


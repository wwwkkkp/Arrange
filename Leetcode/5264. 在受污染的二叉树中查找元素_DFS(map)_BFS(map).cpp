/*5264. 在受污染的二叉树中查找元素
给出一个满足下述规则的二叉树：

root.val == 0
如果 treeNode.val == x 且 treeNode.left != null，那么 treeNode.left.val == 2 * x + 1
如果 treeNode.val == x 且 treeNode.right != null，那么 treeNode.right.val == 2 * x + 2
现在这个二叉树受到「污染」，所有的 treeNode.val 都变成了 -1。

请你先还原二叉树，然后实现 FindElements 类：

FindElements(TreeNode* root) 用受污染的二叉树初始化对象，你需要先把它还原。
bool find(int target) 判断目标值 target 是否存在于还原后的二叉树中并返回结果。
 

示例 1：



输入：
["FindElements","find","find"]
[[[-1,null,-1]],[1],[2]]
输出：
[null,false,true]
解释：
FindElements findElements = new FindElements([-1,null,-1]); 
findElements.find(1); // return False 
findElements.find(2); // return True 

示例 2：

输入：
["FindElements","find","find","find"]
[[[-1,-1,-1,-1,-1]],[1],[3],[5]]
输出：
[null,true,true,false]
解释：
FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
findElements.find(1); // return True
findElements.find(3); // return True
findElements.find(5); // return False

示例 3：

输入：
["FindElements","find","find","find","find"]
[[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
输出：
[null,true,false,false,true]
解释：
FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
findElements.find(2); // return True
findElements.find(3); // return False
findElements.find(4); // return False
findElements.find(5); // return True
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
 //BFS+map  (map可以换成 unordered_map,set)
class FindElements {
public:
    map<int,int>m;  //出现过的数索引
    FindElements(TreeNode* root) {
        root->val=0;
        queue<TreeNode*>q;
        q.push(root);  
        while(!q.empty()){
            TreeNode* r=q.front();
            q.pop();
            m[r->val]=1;
            if(r->left){
                r->left->val=r->val*2+1;
                q.push(r->left);
            }
            if(r->right){
                r->right->val=r->val*2+2;
                q.push(r->right);
            }
        }
    }
    
    bool find(int target) {
        if(m[target])return true;//查找
        return false;
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
 
 //同样也可以用DFS+map
 class FindElements {
public:

    FindElements(TreeNode* root) {
		root->val=0;
		DFS(root);
    }
    
    bool find(int target) {
        if(m[target])return true;//查找
        return false;
    }
private:
	void DFS(TreeNode* root){
		if(root)
			m[root->val]=1;
		if(root->left){
			root->left->val=root->val*2+1;
			DFS(root->left);
		}
		if(root->right){
			root->right->val=root->val*2+1;
			DFS(root->right);
		}		
	}
private:
	map<int,int>m;
};
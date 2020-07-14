

1028. 从先序遍历还原二叉树
我们从二叉树的根节点 root 开始进行深度优先搜索。

在遍历中的每个节点处，我们输出 D 条短划线（其中 D 是该节点的深度），然后输出该节点的值。（如果节点的深度为 D，则其直接子节点的深度为 D + 1。根节点的深度为 0）。

如果节点只有一个子节点，那么保证该子节点为左子节点。

给出遍历输出 S，还原树并返回其根节点 root。

 

示例 1：



输入："1-2--3--4-5--6--7"
输出：[1,2,5,3,4,6,7]
示例 2：



输入："1-2--3---4-5--6---7"
输出：[1,2,5,3,null,6,null,4,null,7]
示例 3：



输入："1-401--349---90--88"
输出：[1,401,null,349,88,90]
 

提示：

原始树中的节点数介于 1 和 1000 之间。
每个节点的值介于 1 和 10 ^ 9 之间。



//这道题和11.5 序列化二叉树中的反序列类似，这种题的重点是，遍历到string的位置， 
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
    TreeNode* recoverFromPreorder(string S) {
        int u = 0;
        return dfs(S, u, 0);
    }
    TreeNode* dfs(string s, int &u, int a) {  //a:当前结点在哪一层，u:当前遍历到s的哪一个位置
        if (u == s.size())return NULL;
        int k = u;
        int val = number(s, k);
 
        TreeNode* r = new TreeNode(val);  //建立当前u所在位置的结点
        for (int i = 0; i < 2; i++) {  //检查左右子树，当遍历完左子树后，k需要更新
            int w = 0;
            while (k < s.size() && s[k] == '-') { k++; w++; }    	//检测下一个节点在哪一层

            if (w - 1 == a && i == 0) {   //如果是当前结点的左子树
                u = k;
                r->left = dfs(s, u, a + 1); 
                k = u;							//这里很重要，k应该指向当前结点u的的end()位置，方便第二次计算层数，u永远指向一个数的开头位置
                while (k < s.size() && s[k] >= '0'&&s[k] <= '9')k++;
            }
            else if (w - 1 == a && i == 1) {   //如果是当前结点的右子树
                u = k;  
                r->right = dfs(s, u, a + 1); 
                k = u;
                while (k < s.size() && s[k] >= '0'&&s[k] <= '9')k++;
            }
            else if (w == a) return r;			//如果当前结点的层数和下一个节点的层数一样，那说明在同一层，需要返回去了
            else if (k == s.size()) return r;	//结点在最后，直接返回
            else return r;
        }
        return r;
    }

    int number(string s, int &k) {
        int val = 0;
        if (k < s.size() && s[k] >= '0'&&s[k] <= '9') {
            while (k < s.size() && s[k] >= '0'&&s[k] <= '9') {
                val = val * 10 + s[k] - '0';

                k++;
            }
        }
        return val;
    }
};
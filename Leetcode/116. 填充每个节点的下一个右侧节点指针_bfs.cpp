







//116. 填充每个节点的下一个右侧节点指针
给定一个完美二叉树，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

初始状态下，所有 next 指针都被设置为 NULL。

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
//bfs
class Solution {
public:
    Node* connect(Node* root) {
        if(!root)return NULL;
        queue<pair<Node*,int>>q;
        q.push({root,1});
        while(q.size()){
            auto w=q.front();
            q.pop();
            auto t=w.first;
            int a=w.second;          
            if(!t)continue;					//注意题意，认真读题
            if(q.size()&&q.front().second==a){
                t->next=q.front().first;
            }else{ t->next=NULL;}
            q.push({t->left,a+1});
            q.push({t->right,a+1});
        }
        return root;
    }
};
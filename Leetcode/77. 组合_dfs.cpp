


//77. 组合
给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。

示例:

输入: n = 4, k = 2
输出:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

//回溯
class Solution {
public:
    int n;
    vector<int>v;
    vector<vector<int>>v1;
    vector<vector<int>> combine(int n1, int k) {
        n=n1;
        aif(!n&&!k)return {{}};
        if(k>n)return {};
        dfs(1,k);
        return v1;
    }
    void dfs(int a,int t){
        if(!t){
            v1.push_back(v);
            return;
        }
        if(a==n+1){
            return;
        }
		if(t>n-a+1)return;    //剪枝，如果要选的数多于待选的数，就返回了
        v.push_back(a);
        dfs(a+1,t-1);
        v.pop_back();
        dfs(a+1,t);
    }
};
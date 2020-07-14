
//51. N皇后
n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。



上图为 8 皇后问题的一种解法。

给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。

每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

示例:

输入: 4
输出: [
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。


//暴搜+回溯
class Solution {
public:
    bool col[20],zx[20],fx[20];  //列是否被占，正斜线是否被占，反斜线是否被占，注意：正斜线的大小和列数是不一样的
    int n;
    vector<vector<string>>v;
    vector<vector<string>> solveNQueens(int n1) {
        memset(col,0,sizeof col);
        memset(zx,0,sizeof zx);
        memset(fx,0,sizeof fx);
        n=n1;
        string s;
        for(int i=0;i<n;i++)s+='.';
        vector<string>vs;
        for(int i=0;i<n;i++)vs.push_back(s);
        dfs(0,vs);
        return v;
    }
    
    void dfs(int a,vector<string>&vs){//a是行数，vs是需要修改的棋盘
        if(a==n){
            v.push_back(vs);
            return ;
        }
        for(int i=0;i<n;i++){
            if(!col[i]&&!zx[a+i]&&!fx[a-i+n]){
                col[i]=zx[a+i]=fx[a-i+n]=1;
                vs[a][i]='Q';
                dfs(a+1,vs);
                vs[a][i]='.';
                col[i]=zx[a+i]=fx[a-i+n]=0;
            }
        }
    }
};
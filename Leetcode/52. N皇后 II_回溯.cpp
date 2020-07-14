

//52. N皇后 II
n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。



上图为 8 皇后问题的一种解法。

给定一个整数 n，返回 n 皇后不同的解决方案的数量。

示例:

输入: 4
输出: 2
解释: 4 皇后问题存在如下两个不同的解法。
[
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]

//回溯  和51一样，只是返回的是个数，而不是具体的棋盘
class Solution {
public:
    bool col[20],zx[20],fx[20];
    int n;
    int res=0;
    int totalNQueens(int n1) {
        memset(col,0,sizeof col);
        memset(zx,0,sizeof zx);
        memset(fx,0,sizeof fx);
        n=n1;
        dfs(0);
        return res;
    }
    
    void dfs(int a){
        if(a==n){
            res++;
            return ;
        }
        for(int i=0;i<n;i++){
            if(!col[i]&&!zx[a+i]&&!fx[a-i+n]){
                col[i]=zx[a+i]=fx[a-i+n]=1;
                dfs(a+1);
                col[i]=zx[a+i]=fx[a-i+n]=0;
            }
        }
    }
};
};
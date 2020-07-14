//63. 不同路径 II
/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

网格中的障碍物和空位置分别用 1 和 0 来表示。

说明：m 和 n 的值均不超过 100。

示例 1:

输入:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
输出: 2
解释:
3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：
1. 向右 -> 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右 -> 向右

*/

//基本的动态规划递推

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int sizex=obstacleGrid.size();
        int sizey=obstacleGrid[0].size();
        vector<vector<long>> SideWay(sizex,vector<long>(sizey,0));
        if(obstacleGrid[0][0]==1)
            return 0;
        else
            SideWay[0][0]=1;
        for(int i=1;i<sizex;i++)
            if(obstacleGrid[i][0]==1)
                SideWay[i][0]=0;
            else
                SideWay[i][0]=SideWay[i-1][0];
        for(int i=1;i<sizey;i++)
            if(obstacleGrid[0][i]==1)
                SideWay[0][i]=0;
            else
                SideWay[0][i]=SideWay[0][i-1];
        for(int i=1;i<sizex;i++){
            for(int j=1;j<sizey;j++){
                if(obstacleGrid[i][j]==1)
                    SideWay[i][j]=0;
                else
                    SideWay[i][j]=SideWay[i-1][j]+SideWay[i][j-1];
            }
        }
        return (int)SideWay[sizex-1][sizey-1];        
    }
};


//7.6版本
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& v) {
        int n=v.size();
        if(!n)return 0;
        int m=v[0].size();
        
        int k=max(n,m);
        vector<vector<long>> f(k+1,vector<long>(k+1,0));  //vector比数组要快一些
        for(int i=0;i<k;i++){f[0][i]=0;f[i][0]=0;}
        f[1][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(v[i-1][j-1]==1)f[i][j]=0;
                else {
                    f[i][j]=f[i-1][j]+f[i][j-1]; 
                }
            }
        }
        return f[n][m];
    }
};
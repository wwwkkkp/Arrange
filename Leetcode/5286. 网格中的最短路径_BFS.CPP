/*  5286. 网格中的最短路径

给你一个 m * n 的网格，其中每个单元格不是 0（空）就是 1（障碍物）。每一步，您都可以在空白单元格中上、下、左、右移动。

如果您 最多 可以消除 k 个障碍物，请找出从左上角 (0, 0) 到右下角 (m-1, n-1) 的最短路径，并返回通过该路径所需的步数。如果找不到这样的路径，则返回 -1。

示例 1：

输入： 
grid = 
[[0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]], 
k = 1
输出：6
解释：
不消除任何障碍的最短路径是 10。消除位置 (3,2) 处的障碍后，最短路径是 6 。该路径是 (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).

示例 2：

输入：
grid = 
[[0,1,1],
 [1,1,1],
 [1,0,0]], 
k = 1
输出：-1
解释：我们至少需要消除两个障碍才能找到这样的路径。
 
提示：

grid.length == m
grid[0].length == n
1 <= m, n <= 40
1 <= k <= m*n
grid[i][j] == 0 or 1
grid[0][0] == grid[m-1][n-1] == 0

*/

//BFS
class Solution {
public:
    int dis[4][2]={{0,1},{0,-1},{1,0},{-1,0}}; 
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m=grid.size();
        int n=grid[0].size();
        if(1==m&&1==n)return 0;
        queue<vector<int>>q;
        q.push({0,0,k,0}); //横坐标 纵坐标 还剩k次扫清障碍的机会 步数
        vector<vector<vector<int>>> visit(m,vector<vector<int>>(n,vector<int>(k+1,0)));
        
        while(!q.empty()){
            vector<int> v=q.front();
            q.pop();
            for(int i=0;i<4;i++){
                int x1=v[0]+dis[i][0];
                int y1=v[1]+dis[i][1];

                if(x1<0||x1>=m||y1<0||y1>=n)continue;

                if(grid[x1][y1]==1)
                    if(v[2]>0)
                        v[2]--;
                    else
                        continue;
                if(visit[x1][y1][v[2]]){  //还有k次扫清障碍的时候 到[x1][y1]，只能访问一次，相当于剪枝，如果是DFS要专门列一个表 装还剩k次到[x1][y1]的最小步数，大于这个步数就剪枝
                    if(grid[x1][y1]==1)
                        v[2]++; //回溯k
                    continue;
                }
                visit[x1][y1][v[2]]=1;
                if(x1==m-1&&y1==n-1)
                    return v[3]+1;

                q.push({x1,y1,v[2],v[3]+1});
                if(grid[x1][y1]==1)
                    v[2]++;
            }
        }
        return -1;
    }
};

//DFS也可以，不过要剪枝；
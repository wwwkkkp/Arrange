/*5272. 统计参与通信的服务器

这里有一幅服务器分布图，服务器的位置标识在 m * n 的整数矩阵网格 grid 中，1 表示单元格上有服务器，0 表示没有。

如果两台服务器位于同一行或者同一列，我们就认为它们之间可以进行通信。

请你统计并返回能够与至少一台其他服务器进行通信的服务器的数量。

输入：grid = [[1,0],[0,1]]
输出：0
解释：没有一台服务器能与其他服务器进行通信。

输入：grid = [[1,0],[1,1]]
输出：3
解释：所有这些服务器都至少可以与一台别的服务器进行通信。

输入：grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
输出：4
解释：第一行的两台服务器互相通信，第三列的两台服务器互相通信，但右下角的服务器无法与其他服务器通信。

*/

class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        int grid_1[m][n];
        int num=0;
        for(int i=0;i<m;i++)  //赋初始值可以简化：memset(grid_1,0,sizeof(grid_1));
            for(int j=0;j<n;j++)
                grid_1[i][j]=0;
        for(int i=0;i<m;i++){
            vector<int>a,b;
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    a.push_back(i);
                    b.push_back(j); 
                }
            }
            if(a.size()>=2){
                for(int k=0;k<a.size();k++){
                    grid_1[a[k]][b[k]]=1;
                    num++;
                }
            }                
        }
        for(int j=0;j<n;j++){
            vector<int>a,b;
            for(int i=0;i<m;i++){
                if(grid[i][j]==1){
                    a.push_back(i);
                    b.push_back(j);
                }
            }
            if(a.size()>=2){
                for(int k=0;k<a.size();k++){
                    if(grid_1[a[k]][b[k]]==1)
                        continue;
                    else
                     num++;
                }
            } 
        }
        return num;
    }
};

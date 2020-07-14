/* 542. 01 矩阵
给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。

两个相邻元素间的距离为 1 。

示例 1:
输入:

0 0 0
0 1 0
0 0 0
输出:

0 0 0
0 1 0
0 0 0
示例 2:
输入:

0 0 0
0 1 0
1 1 1
输出:

0 0 0
0 1 0
1 2 1
注意:

给定矩阵的元素个数不超过 10000。
给定矩阵中至少有一个元素是 0。
矩阵中的元素只在四个方向上相邻: 上、下、左、右。

*/


//方法1：BFS
class Solution {
public:
    int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}}; 
	vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int n=matrix.size();
        int m=matrix[0].size();

        queue<vector<int>> q;
        int p=0;
        vector<int>xy(2);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(matrix[i][j]==1){
                    xy[0]=i;
                    xy[1]=j;
                    q.push(xy);
                }
        while(!q.empty()){
            queue<vector<int>> q2;
            while(!q.empty()){
                vector<int>xy2=q.front();
                q.pop();
                int i;
                for(i=0;i<4;i++){
                    int x=xy2[0]+dir[i][0];
                    int y=xy2[1]+dir[i][1];
                    if(x<n&&x>=0 &&y<m &&y>=0&&matrix[x][y]<=p) //如果该点存在但是不符合四周都是1,或者2等，就退出
                        break;
                    else
                        continue;
                }
                if(i==4){
                    matrix[xy2[0]][xy2[1]]++;
                    q2.push(xy2);
                }
            }
            p++;
            q=q2;
        }
		return Vec;
    }
};




//方法2：动态规划

//该动态规划的思想就是：每个非0点到0的距离，跟它上下左右到0的距离有关，所以第一次遍历先将左上两个位置的非0点最小者加1更改。这样就是从左上往右下看，   非0点到0的最短距离，但是这样还不知道从右下到左上看的最短距离。        所以再从右下到左上遍历，注意这次更新除了要取右下两个点的最短距离之外，还要跟当前位置的点做一次最小值比较，因为右下可能距离更远。


class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {                
        int r = matrix.size(), c = matrix[0].size();
        vector<vector<int>> dist(r, vector<int>(c, INT_MAX - 10000));        
        //1. 从上到下，从左到右遍历矩阵
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;                    
                } else {
                    if (i > 0) dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                    if (j > 0) dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }                
            }
        }        
        //2. 从下到上，从右到左遍历
        for (int i = r - 1; i >= 0; --i) {
            for (int j = c - 1; j >= 0; --j) {
                if (i < r - 1) dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
                if (j < c - 1) dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
            }
        }
        return dist;
    }
};
/*
5255. 奇数值单元格的数目 显示英文描述 

给你一个 n 行 m 列的矩阵，最开始的时候，每个单元格中的值都是 0。

另有一个索引数组 indices，indices[i] = [ri, ci] 中的 ri 和 ci 分别表示指定的行和列（从 0 开始编号）。

你需要将每对 [ri, ci] 指定的行和列上的所有单元格的值加 1。

请你在执行完所有 indices 指定的增量操作后，返回矩阵中 「奇数值单元格」 的数目。

示例 1：

输入：n = 2, m = 3, indices = [[0,1],[1,1]]
输出：6
	解释：最开始的矩阵是 [[0,0,0],[0,0,0]]。
	第一次增量操作后得到 [[1,2,1],[0,1,0]]。
	最后的矩阵是 [[1,3,1],[1,3,1]]，里面有 6 个奇数。
	
	
示例 2：

输入：n = 2, m = 2, indices = [[1,1],[0,0]]
输出：0
解释：最后的矩阵是 [[2,2],[2,2]]，里面没有奇数。
*/


//将数字变成0-1，统计等于1的数目，

class Solution {
public:
    int oddCells(int n, int m, vector<vector<int>>& indices) {
        int ju[n][m];
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                ju[i][j]=0;
        for(int i=0;i<indices.size();i++)  //遍历所有的横坐标
            for(int j=0;j<m;j++){
                ju[indices[i][0]][j]=(ju[indices[i][0]][j]+1)%2;
            }
        for(int i=0;i<indices.size();i++) //遍历所有的纵坐标
            for(int j=0;j<n;j++){
                ju[j][indices[i][1]]=(ju[j][indices[i][1]]+1)%2;
            }
        int num=0;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                num+=ju[i][j];
        return num;
    }
};
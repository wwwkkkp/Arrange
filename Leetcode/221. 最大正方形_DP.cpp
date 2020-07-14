/*  221. 最大正方形

在一个由 0 和 1 组成的二维矩阵内，找到只包含 1 的最大正方形，并返回其面积。

示例:

输入: 

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

输出: 4



*/


//动态规划，
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(!matrix.size())
            return 0;
        int x=matrix.size();
        int y=matrix[0].size();

        int k=0;
        vector<vector<int>> Vec(x,vector<int>(y,0)); //以[i][j]为右下角的最大正方形边长
        for(int i=0;i<x;i++)
            Vec[i][0]=matrix[i][0]-'0',k=max(k,Vec[i][0]);
        for(int i=0;i<y;i++)
            Vec[0][i]=matrix[0][i]-'0',k=max(k,Vec[0][i]);
        for(int i=1;i<x;i++)
            for(int j=1;j<y;j++){
                if(matrix[i][j]=='1'){
                    Vec[i][j]=min(Vec[i-1][j],min(Vec[i][j-1],Vec[i-1][j-1]))+1; //左和上和左上的最小值+1；
                    k=max(k,Vec[i][j]);
                }
            }
        return pow(k,2);
    }
};
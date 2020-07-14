

//59. 螺旋矩阵 II
给定一个正整数 n，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。

示例:

输入: 3
输出:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]


//数组，注意边界的墙的概念，
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>>v(n, vector<int>(n));
        int x1 = 0, x2 = n-1, x3 = n-1, x4 =0; //x1,x2,x3,x4分别是上右下左的墙，
        int k = 1;
        while (k<=n*n) {
            for(int i=x4;i<=x2;i++)v[x1][i]=k++;  //从左边的墙到右边的墙，是走在上边的墙上的 ，下面的以此类推
            x1++;
            for(int i=x1;i<=x3;i++)v[i][x2]=k++;
            x2--;
            for(int i=x2;i>=x4;i--)v[x3][i]=k++;
            x3--;
            for(int i=x3;i>=x1;i--)v[i][x4]=k++;
            x4++;
        }
        return v;
    }
};
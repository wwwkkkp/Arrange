/*  5285. 元素和小于等于阈值的正方形的最大边长

给你一个大小为 m x n 的矩阵 mat 和一个整数阈值 threshold。

请你返回元素总和小于或等于阈值的正方形区域的最大边长；如果没有这样的正方形区域，则返回 0 。
 

示例 1：

输入：mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
输出：2
解释：总和小于 4 的正方形的最大边长为 2，如图所示。
示例 2：

输入：mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
输出：0
示例 3：

输入：mat = [[1,1,1,1],[1,0,0,0],[1,0,0,0],[1,0,0,0]], threshold = 6
输出：3
示例 4：

输入：mat = [[18,70],[61,1],[25,85],[14,40],[11,96],[97,96],[63,45]], threshold = 40184
输出：2
 

提示：

1 <= m, n <= 300
m == mat.length
n == mat[i].length
0 <= mat[i][j] <= 10000
0 <= threshold <= 10^5

*/

//递归
class Solution {
public:
    int maxs = 0;
    void DP(vector<vector<int>>& mat, int t, int left, int right, int m, int n, vector<vector<int>>&it) {  //it[i][j]:[0,0]和[i,j]围成的矩形的元素总和
        if (left > right) return;
        int side = (left + right) / 2;  //二分法
        int flag = 0;
        int sum = 0;
        for (int i1 = 0; i1 <= m - side; i1++) {
            if (!side) {
			    flag = 1; break;
		    }
            for (int j1 = 0; j1 <= n - side; j1++) {  
			
                if (i1 == 0 && j1 == 0)  //求边长是side的正方形的元素总和 
                    sum = it[i1 + side-1][j1 + side - 1];
                else if(i1==0)
                    sum = it[i1 + side - 1][j1 + side - 1]-it[i1+side - 1][j1-1];
                else if(j1==0)
                    sum = it[i1 + side - 1][j1 + side - 1] - it[i1 -1][j1+side - 1];
                else
                    sum = it[i1 + side - 1][j1 + side - 1] - it[i1 - 1][j1 + side - 1] - it[i1 + side - 1][j1 - 1] + it[i1-1][j1-1];
				
                if (sum <= t) {  //如果sum小于阈值
                    maxs = side; //刷新最长边界退出
                    flag = 1;
                    break;
                }
                sum = 0;
            }
            if (flag)
                break;
        }
        if (flag) {
            DP(mat, t, side + 1, right, m, n,it); //二分
        }
        else
            DP(mat, t, left, side - 1, m, n,it);
    }
	
    int maxSideLength(vector<vector<int>>& mat, int t) {
        int m = mat.size();
        int n = mat[0].size();
        int mins = min(m, n);
        vector<vector<int>> it(m,vector<int>(n,0));
        it[0][0] = mat[0][0];
        for (int i = 1; i < m; i++)
            it[i][0] = mat[i][0]+it[i-1][0];
        for (int i = 1; i < n; i++)
            it[0][i] = mat[0][i]+it[0][i-1];
        for (int i = 1; i <m;i++)
            for (int j = 1; j <n; j++) {
                it[i][j] = it[i - 1][j] + it[i][j - 1] - it[i - 1][j - 1]+mat[i][j];
            }
        DP(mat, t, 0, mins, m, n,it);
        return maxs;

    }

};
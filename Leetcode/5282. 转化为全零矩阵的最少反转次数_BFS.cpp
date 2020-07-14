/*5282. 转化为全零矩阵的最少反转次数
给你一个 m x n 的二进制矩阵 mat。

每一步，你可以选择一个单元格并将它反转（反转表示 0 变 1 ，1 变 0 ）。如果存在和它相邻的单元格，那么这些相邻的单元格也会被反转。（注：相邻的两个单元格共享同一条边。）

请你返回将矩阵 mat 转化为全零矩阵的最少反转次数，如果无法转化为全零矩阵，请返回 -1 。

二进制矩阵的每一个格子要么是 0 要么是 1 。

全零矩阵是所有格子都为 0 的矩阵。

示例 1：

输入：mat = [[0,0],[0,1]]
输出：3
解释：一个可能的解是反转 (1, 0)，然后 (0, 1) ，最后是 (1, 1) 。
示例 2：

输入：mat = [[0]]
输出：0
解释：给出的矩阵是全零矩阵，所以你不需要改变它。
示例 3：

输入：mat = [[1,1,1],[1,0,1],[0,0,0]]
输出：6
示例 4：

输入：mat = [[1,0,0],[1,0,0]]
输出：-1
解释：该矩阵无法转变成全零矩阵
 

提示：

m == mat.length
n == mat[0].length
1 <= m <= 3
1 <= n <= 3
mat[i][j] 是 0 或 1 。

*/

//BFS+暴力穷举，一个矩阵x行 y列，一次变换有x*y这种情况，把这些数都压进队列，然后第二轮每个又是x*y种情况，以此类推

class Solution {
public:
    int dis[4][2] = { {0,-1},{1,0},{0,1},{-1,0} };  
    int getkey(vector<vector<int>>& mat) { //压缩矩阵，使矩阵变成一个数，方便压入队列
        int k = 0;
        int x = mat.size();
        int y = mat[0].size();
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                k = k << 1;
                k += mat[i][j];
            }
        }
        return k;
    }
    vector<vector<int>> getmat(int key, int x, int y) {  //解压数 把树变成矩阵
        vector<vector<int>> mat(x, vector<int>(y, 0));
        for (int i = x - 1; i >= 0; i--) {
            for (int j = y - 1; j >= 0; j--) {
                mat[i][j] = key & 1;
                key >>= 1;
            }
        }
        return mat;
    }
    int minFlips(vector<vector<int>>& mat) {
        int x = mat.size();
        int y = mat[0].size();
        int sum = 0;
        for (int i = x - 1; i >= 0; i--)
            for (int j = y - 1; j >= 0; j--)
                sum += mat[i][j];
        if (sum == 0) return 0;
        queue<int> q;
        int a = getkey(mat);
        
        vector<int> d(pow(2, x*y), 0); //步数统计，
        vector<int> visit(pow(2, x*y), 0); //是否已经访问过
		
        visit[a] = 1;
        q.push(a);
		
        while (!q.empty()) {
            int m = q.front();
            q.pop();
            vector<vector<int>> mat_1 = getmat(m, x, y);  //解压数
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {

                    mat_1[i][j] = 1 - mat_1[i][j];//相邻的数翻转
                    for (int k = 0; k < 4; k++) {
                        int x1 = i + dis[k][0];
                        int y1 = j + dis[k][1];
                        if (x1 >= 0 && x1 < x && y1 >= 0 && y1 < y)
                            mat_1[x1][y1] = 1 - mat_1[x1][y1];
                    }
					
                    int b = getkey(mat_1);
                    if (!visit[b]) { //该矩阵没有出现过
                        visit[b] = 1;
                        q.push(b);//压入队列
                        d[b] = d[m] + 1;  //在原来步数的基础上+1，
                        if (b == 0)
                            return d[b];
                    }
                    mat_1[i][j] = 1 - mat_1[i][j];  //因为一个矩阵有x*y和数可以翻转，所以这里需要还原矩阵
                    for (int k = 0; k < 4; k++) {
                        int x1 = i + dis[k][0];
                        int y1 = j + dis[k][1];
                        if (x1 >= 0 && x1 < x && y1 >= 0 && y1 < y)
                            mat_1[x1][y1] = 1 - mat_1[x1][y1];
                    }

                }
            }
        }
        return -1;
    }
};
/*5277. 统计全为 1 的正方形子矩阵
给你一个 m * n 的矩阵，矩阵中的元素不是 0 就是 1，请你统计并返回其中完全由 1 组成的 正方形 子矩阵的个数。

示例 1：

输入：matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
输出：15
解释： 
边长为 1 的正方形有 10 个。
边长为 2 的正方形有 4 个。
边长为 3 的正方形有 1 个。
正方形的总数 = 10 + 4 + 1 = 15.
示例 2：

输入：matrix = 
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
输出：7
解释：
边长为 1 的正方形有 6 个。 
边长为 2 的正方形有 1 个。
正方形的总数 = 6 + 1 = 7.
 

提示：

1 <= arr.length <= 300
1 <= arr[0].length <= 300
0 <= arr[i][j] <= 1

*/



class Solution {
public:
    int countSquares(vector<vector<int>>& m) {
        int xsize = m.size();
        int ysize = m[0].size();
        vector<vector<int>> out(xsize, vector<int>(ysize, 0)); //以out[i][j]为右下角的正方形总数
        out[0][0] = m[0][0];
        for (int i = 1; i < ysize; i++) {
            out[0][i] = out[0][i - 1] + m[0][i];
        }
        for (int i = 1; i < xsize; i++) {
            out[i][0] = out[i - 1][0] + m[i][0];
        }
        for (int i = 1; i < xsize; i++) {
            for (int j = 1; j < ysize; j++) {
                out[i][j] = out[i - 1][j] + out[i][j - 1] - out[i - 1][j - 1];//递推公式
				
                int sum = m[i][j];
                int x = 0, y = 0;
                while (i - x >= 0 && j - y >= 0) {  //以i,j为右下角忘左上角找边长大于1的正方形
                    sum = 0;	
                    for (int i1 = i - x; i1 <= i; i1++) {
                        for (int j1 = j - y; j1 <= j; j1++) {
                            sum += m[i1][j1];
                        }
                    }
                    if (sum == pow(x + 1, 2)) {
                        out[i][j]++; 
                    }
                    else
                        break;
                    x++;
                    y++;

                }
            }
        }
        return out[xsize - 1][ysize - 1];
    }
};


//方法二：纯动态规划

/*
那么怎么利用之前判断过的结果呢？举个例子，比如我要判断以(2, 3)为右下角边长为3的正方形区域（红色边框区域）是否是全为1：

先判断(i, j)位置是否为1，如果否，则显然不满足；如果是，进行下一步判断
判断分别以(i - 1, j), (i - 1, j - 1), (i, j - 1)为右下角的区域是否能构成边长为2的正方形，如果能，那就满足条件。

基于上述，我们可以看出思路大致跟最大正方形那题差不多，设dp[i][j][k]表示以(i, j)为右下角，边长为k的正方形区域是否全为1，那么易得出如下状态转移方程：

dp[i][j][k] = (matrix[i][j] == 1 && dp[i - 1][j][k - 1] && dp[i][j - 1][k - 1] && dp[i - 1][j - 1] [k - 1]);

详见图 5277
*/

class Solution {
public :
	int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int len = min(m, n);
		vector<vector<vector<int>>> dp(xsize, vector<int>(ysize, vector<int>(len))); 

        int count = 0; //总数
		
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j][0] = (matrix[i][j] == 1); //边长为0，就是单数的个数
                count += dp[i][j][0] ? 1 : 0;
            }
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                for (int k = 1; k < len; k++) {
                    dp[i][j][k] = (matrix[i][j] == 1 && dp[i - 1][j][k - 1] && dp[i][j - 1][k - 1] && dp[i - 1][j - 1] [k - 1]);
					
                    if (dp[i][j][k]) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

}


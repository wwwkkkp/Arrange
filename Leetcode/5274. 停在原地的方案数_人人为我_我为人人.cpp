/*5274. 停在原地的方案数

有一个长度为 arrLen 的数组，开始有一个指针在索引 0 处。

每一步操作中，你可以将指针向左或向右移动 1 步，或者停在原地（指针不能被移动到数组范围外）。

给你两个整数 steps 和 arrLen ，请你计算并返回：在恰好执行 steps 次操作以后，指针仍然指向索引 0 处的方案数。

由于答案可能会很大，请返回方案数 模 10^9 + 7 后的结果。

 

示例 1：

输入：steps = 3, arrLen = 2
输出：4
解释：3 步后，总共有 4 种不同的方法可以停在索引 0 处。
向右，向左，不动
不动，向右，向左
向右，不动，向左
不动，不动，不动
示例  2：

输入：steps = 2, arrLen = 4
输出：2
解释：2 步后，总共有 2 种不同的方法可以停在索引 0 处。
向右，向左
不动，不动
示例 3：

输入：steps = 4, arrLen = 2
输出：8
 

提示：

1 <= steps <= 500
1 <= arrLen <= 10^6

*/

//递推关系 不妨设dp[i][j]表示步数为 i,下标在 j 的位置，显然有dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1]
//注意这里，要清楚的明白迭代中的每每一个坐标的意思
 
// 递推， 我为人人

class Solution {
public:
    int numWays(int steps, int arrLen) {
        const int M=1000000007;
        vector<vector<long long>>DP(steps+1,vector<long long>(steps+1));
        DP[0][0] = 1;
        for (int i = 1; i <= steps; ++ i)
        {
            for (int j = 0; j < i && j < arrLen; ++ j)  //位置的限制条件，不能大过步数
				
                for (int d = -1; d <= 1; ++ d)
                    if (0 <= j+d && j+d < arrLen) //注意j+d的范围，下面的也要注意
                    {
                        (DP[i][j+d] += DP[i-1][j]) %= M; // DP[i-1][j]推出他下一步可能的位置,我为人人
                    }
        }
        return DP[steps][0];
    }
};

//递推 人人为我

class Solution {
public:
    long long dp[510][510];
    int numWays(int steps, int arrLen) {
        const int mod = 1e9 + 7;
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 1; i <= steps; ++i) {
            for (int j = 0; j < std::min(505, arrLen); ++j) {
                dp[i][j] = j > 0 ? ((dp[i - 1][j - 1] + dp[i - 1][j + 1]) % mod) : (dp[i - 1][j + 1]); //人人为我
                (dp[i][j] += dp[i - 1][j]) % mod;
            }
        }
        return dp[steps][0];
    }
};

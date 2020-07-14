/*343. 整数拆分
给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。

示例 1:

输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。

示例 2:

输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。

说明: 你可以假设 n 不小于 2 且不大于 58。

*/

//递推
class Solution {
public:
    int integerBreak(int n) {
        vector<int>dp(n+1,1);
        for(int i=0;i<=n;i++)
            dp[i]=i; //2和3最开始要是2和3，1和2是错的
        for(int i=3;i<=n;i++){
            int L,R;
            if(i%2){
                L=i/2;
                R=L+1;           
            }
            else{
                L=i/2;
                R=L;
            }
            for(int j=0;j<2;j++){
                dp[i]=max(dp[L]*dp[R],dp[i]);  //一般的最大值就是中间两组，
                L--;
                R++;
            }
        }
        dp[2]=1;
        dp[3]=2;
        return dp[n];
    }
};


//递推公式
F(n) = max {i * F(n - i)}，i = 1，2，...，n - 1

class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                dp[i] = max(dp[i], max(j, dp[j]) * max(i - j, dp[i - j]));  //注意这里 max(j, dp[j]) 和 max(i - j, dp[i - j]) 有的时候dp[i]比i小，但是当分到i的时候，最小就是值就是i，比如 dp[2]=1，当4分到2+2的时候，dp[4]=4,因为2就不需要再分了，再分只能更小
            }
        }
        return dp[n];
    }
};




//516. 最长回文子序列
给定一个字符串s，找到其中最长的回文子序列，并返回该序列的长度。可以假设s的最大长度为1000。

示例 1:
输入:

"bbbab"
输出:

4
一个可能的最长回文子序列为 "bbbb"。

示例 2:
输入:

"cbbd"
输出:

2
一个可能的最长回文子序列为 "bb"。




//这道题的遍历方式有些特别，是斜向遍历
状态
f[i][j] 表示 s 的第 i 个字符到第 j 个字符组成的子串中，最长的回文序列长度是多少。

转移方程
如果 s 的第 i 个字符和第 j 个字符相同的话

f[i][j] = f[i + 1][j - 1] + 2

如果 s 的第 i 个字符和第 j 个字符不同的话

f[i][j] = max(f[i + 1][j], f[i][j - 1])

然后注意遍历顺序，i 从最后一个字符开始往前遍历，j 从 i + 1 开始往后遍历，这样可以保证每个子问题都已经算好了。

//求f[i][j]，先要知道f[i + 1][j - 1],f[i + 1][j], f[i][j - 1],画图可知，分别是左边，下边，左下面，所以是从j-i=0这条线开始向j-i=n-1遍历，
class Solution {
public:
    int dp[1100][1100];
    int longestPalindromeSubseq(string s) {
        int n=s.size();
        if(!n)return 0;
        memset(dp,0,sizeof dp);
        for(int k=0;k<n;k++){  //j-i=k，k的范围是[0,n-1]
            for(int j=0,i=j-k;j<n;j++,i=j-k){		//j的取值范围是[0,n-1],i是通过j-i=k这个公式求出
                if(i<0)continue;		//i可能小于0
                if(i==j){dp[i][j]=1;} //指向一个数，就是1
                else if(s[i]==s[j]){
                    dp[i][j]=dp[i+1][j-1]+2;
                }
                else dp[i][j]=max(dp[i+1][j],dp[i][j-1]);

            }
        }
        return dp[0][n-1];
    }
};
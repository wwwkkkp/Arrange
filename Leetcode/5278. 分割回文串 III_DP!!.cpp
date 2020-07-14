/*  5278. 分割回文串 III

给你一个由小写字母组成的字符串 s，和一个整数 k。

请你按下面的要求分割字符串：

首先，你可以将 s 中的部分字符修改为其他的小写英文字母。
接着，你需要把 s 分割成 k 个非空且不相交的子串，并且每个子串都是回文串。
请返回以这种方式分割字符串所需修改的最少字符数。

 

示例 1：

输入：s = "abc", k = 2
输出：1
解释：你可以把字符串分割成 "ab" 和 "c"，并修改 "ab" 中的 1 个字符，将它变成回文串。
示例 2：

输入：s = "aabbc", k = 3
输出：0
解释：你可以把字符串分割成 "aa"、"bb" 和 "c"，它们都是回文串。
示例 3：

输入：s = "leetcode", k = 8
输出：0
 

提示：

1 <= k <= s.length <= 100
s 中只含有小写英文字母。


*/


/*
dp(i, j, k) 表示将子串[i, j]分割成 k 个的最优结果
转移方程：dp(i, j, k) = min{dp(i, m, 1) + dp(m + 1, j, k - 1)}
*/
class Solution {
public:
    int palindromePartition(string s, int k) {
        vector<vector<vector<long>>> dp(s.size(), vector<vector<long>>(s.size(), vector<long>(k + 1, INT_MAX)));
		
        for (int i = 0; i < s.size(); i++) {
            dp[i][i][1] = 0;
            for (int j = 1; j + i < s.size() && i - j >= 0; j++) {
                if (s[i - j] == s[i + j])
                    dp[i - j][i + j][1] = 0; //这里计算的是奇数个分成一个的最优结果
                else 
                    break;
            }
        }
		
        for (int i = s.size() - 2; i >= 0; i--) {
            dp[i][i + 1][1] = s[i] == s[i + 1] ? 0 : 1;
            for (int j = i + 1; j < s.size(); j++) {
                dp[i][j][1] = (j == i + 1 ? 0 : dp[i + 1][j - 1][1]) + (s[i] == s[j] ? 0 : 1); // [i,j] 分成一块的最优结果
				
                for (int l = 2; l <= k; l++) {  //[i,j]分成两块，就是两个一块比最小 
                    for (int m = i; m < j; m++) {
                        dp[i][j][l] = std::min(dp[i][j][l], dp[i][m][1] + dp[m + 1][j][l - 1]); 
                    }
                }
            }
        }
        return dp[0][s.size() - 1][k];
    }
};

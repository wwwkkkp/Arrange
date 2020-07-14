
32. 最长有效括号
给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。

示例 1:

输入: "(()"
输出: 2
解释: 最长有效括号子串为 "()"
示例 2:

输入: ")()())"
输出: 4
解释: 最长有效括号子串为 "()()"


//注意，求得是子串，不是一共有多少个()，子序列要加f[N][N]，只要不漏掉任何一种情况就行
const int N=20000;
class Solution {
public:
    int longestValidParentheses(string s) {
        int n=s.size();
        if(!n)return 0;

        int a[N];				//以a为起点，子串能到达的最远的位置
        memset(a,-1,sizeof a);
        for(int len=2;len<=n;len+=2){  //区间DP
            for(int i=0;i+len<=n;i++){
                int j=i+len-1;
                if(len==2&&s[i]=='('&&s[j]==')'){
                    a[i]=j;
                    continue;
                }
                if(a[i+1]==j-1&&s[i]=='('&&s[j]==')'){//(())这种情况
                    a[i]=j;
                    continue;
                }
                if(a[i]>0){   //()()这种情况
                    if(a[a[i]+1]==j){
                        a[i]=j;
                    }
                    continue;
                }

            }
        }
        int res=0;
        for(int i=0;i<n;i++){
            res=max(res,a[i]-i+1);
        }
        return res;
    }
};




//leetcode解法，https://leetcode-cn.com/problems/longest-valid-parentheses/solution/zui-chang-you-xiao-gua-hao-by-leetcode-solution/
class Solution {
public:
    int longestValidParentheses(string s) {
        int maxans = 0, n = s.length();
        vector<int> dp(n, 0);
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {  //看这个')'在前面有没有对应的'('
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;  //如果有，加上这个'('前面的长度
                }
                maxans = max(maxans, dp[i]);
            }
        }
        return maxans;
    }
};
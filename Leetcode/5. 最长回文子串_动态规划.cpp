

//5. 最长回文子串

给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。
示例 2：

输入: "cbbd"
输出: "bb"





//中心扩展法

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() < 2) return s;
        int n = s.size(), maxLen = 0, start = 0;
        for (int i = 0; i < n - 1; ++i) {
            searchPalindrome(s, i, i, start, maxLen);//如果是bab的单数形式，是从中间数a开始搜索，如果是noon等双数形式，是从中间数oo开始搜索
            searchPalindrome(s, i, i + 1, start, maxLen);
        }
        return s.substr(start, maxLen);//截取字符串，start是开始截取的地方，maxlen是截取长度
    }
    void searchPalindrome(string s, int left, int right, int& start, int& maxLen) {//用&的原因是不用返回值，是那个地址的数改变，后面要用直接用就行了
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left; ++right;
        }
        if (maxLen < right - left - 1) {
            start = left + 1;           //开始截取的地方
            maxLen = right - left - 1;  //截取长度
        }
    }
};



//动态规划法
class Solution
{
public:
    string longestPalindrome(string s)
    {
        //判断空字符串的情况
        if (s == "")
        {
            return "";
        }
        string result("");
        int sSize = int(s.size());
        vector<bool> tmpVec(sSize, false);
        vector<vector<bool>> store(sSize, tmpVec);
        int start = 0, end = 0, maxLen = 0;
        //动态规划 store[i][j]
        for (int len = 1; len <= sSize; len++)
        {
            for (int i = 0; i < sSize; i++)
            {
                int j = i + len - 1;
                if (j >= sSize)
                {
                    break;
                }
                //长度为1，2的情况单独考虑
                store[i][j] = (len == 1 || len == 2 || store[i + 1][j - 1]) && s[i] == s[j];
                if (store[i][j] && (j - i + 1) > maxLen)
                {
                    maxLen = j - i + 1;
                    start = i;
                    end = j;
                }
            }
        }

        result = s.substr(start, end - start + 1);
        return result;
    }
};


拓展思路：f[i][j]：第i个字符到第j个字符是否是回文数，如果要f[i][j]为真，那 f[i+1][j-1]&&s[i]==s[j] 都为真，所以要先求得f[i+1][j-1]，所以是反过来递推

//动态规划
class Solution {
public:
    bool dp[1000][1000];
    string longestPalindrome(string s) {
        int n=s.size();
        if(!n)return "";
        int p=0,q=0;
        for(int i=0;i<n;i++){
            for(int j=i;j>=0;j--){
                if(i==j){
                    dp[j][i]=true;
                    continue;
                }
                dp[j][i]=(s[i]==s[j]);
                if(i-1>=j+1)dp[j][i]=(dp[j][i]&&dp[j+1][i-1]);
                if(dp[j][i]&&i-j>q-p){
                    p=j;q=i;
                }
            }
        }
        return s.substr(p,q-p+1);
    }
};
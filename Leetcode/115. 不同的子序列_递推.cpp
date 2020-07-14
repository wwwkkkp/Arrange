

//115. 不同的子序列
给定一个字符串 S 和一个字符串 T，计算在 S 的子序列中 T 出现的个数。

一个字符串的一个子序列是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）

题目数据保证答案符合 32 位带符号整数范围。

 

示例 1：

输入：S = "rabbbit", T = "rabbit"
输出：3
解释：

如下图所示, 有 3 种可以从 S 中得到 "rabbit" 的方案。
(上箭头符号 ^ 表示选取的字母)

rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^
示例 2：

输入：S = "babgbag", T = "bag"
输出：5
解释：

如下图所示, 有 5 种可以从 S 中得到 "bag" 的方案。 
(上箭头符号 ^ 表示选取的字母)

babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^






//递推，这种递推一般都是和他的左上斜三个方向的数发生关系，自己推，找找规律
class Solution {
public:
    long long f[100][20000];//t匹配s的数
    int numDistinct(string s, string t) {
        int n=s.size();
        int m=t.size();
        memset(f,0,sizeof f);
        for(int i=0;i<=n;i++)f[0][i]=1;//当t为空集的时候，t是每一个s的子集
        for(int i=1;i<=m;i++){   
            for(int j=1;j<=n;j++){
                if(s[j-1]==t[i-1]){
                    f[i][j]=f[i-1][j-1]+f[i][j-1];
                }
                else f[i][j]=f[i][j-1];
            }
        }
        return f[m][n];
    }
};
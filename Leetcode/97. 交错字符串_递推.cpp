

//97. 交错字符串
给定三个字符串 s1, s2, s3, 验证 s3 是否是由 s1 和 s2 交错组成的。

示例 1:

输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
输出: true
示例 2:

输入: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
输出: false


class Solution {
public:
    
    bool isInterleave(string s1, string s2, string s3) {
        int n=s1.size();
        int m=s2.size();
        int k=s3.size();
        if(n+m!=k)return false;
        bool f[1000][1000];			//s1中前i个字符和s2中前j个字符能不能形成s3中前i+j个字符
        f[0][0]=1;
        for(int i=1;i<=n&&i<=k;i++)f[i][0]=s3[i-1]==s1[i-1]&&f[i-1][0];
        for(int i=1;i<=m&&i<=k;i++)f[0][i]=s3[i-1]==s2[i-1]&&f[0][i-1];
        if(!n)return f[0][k];
        if(!m)return f[k][0];

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                f[i][j]=(f[i][j-1]&&s2[j-1]==s3[i+j-1])||(f[i-1][j]&&s1[i-1]==s3[i+j-1]);//如s1="ab",s2="d",s3="adb"或者"abd"，最后一个相等的字符可能来自s1,也可能是s2，但是只要有一个满足，那就为真
                if(i+j==k&&f[i][j])return 1; //只要结尾有一个是真，那就是真
            }
        }
        return 0;
    }
};
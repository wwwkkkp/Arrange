

//132. 分割回文串 II
给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。

返回符合要求的最少分割次数。

示例:

输入: "aab"
输出: 1
解释: 进行一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。


//这道题o(N2)也能过
const int N=2000;
class Solution {
public:
    int minCut(string s) {
        int n=s.size();
        if(n<=1)return 0;
        
        int dp[N];						//dp是[0-i]这个区间最少分割次数
        bool f[N][N];
        for(int i=0;i<n;i++){
            for(int j=i;j>=0;j--){
                if(j==i){f[j][i]=true;}
                else if(i-j==1){f[j][i]=s[i]==s[j];}
                else f[j][i]=(s[j]==s[i])&&f[j+1][i-1]; //计算出j-i是不是回文子序列
            }
        }
        
        memset(dp,0x3f3f3f,sizeof dp);
        for(int i=0;i<n;i++){
            if(f[0][i])dp[i]=0; 				//如果0-i就是回文序列，就不用分割，就是0
            else{
                for(int j=0;j<i;j++){				//枚举分割位置
                    if(f[j+1][i]){					
                        dp[i]=min(dp[i],dp[j]+1);  
                    }
                }
            }
        }
        return dp[n-1];
    }
};
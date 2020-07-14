


//17.7.80. 骰子的点数  

将一个骰子投掷n次，获得的总点数为s，s的可能范围为n~6n。
掷出某一点数，可能有多种掷法，例如投掷2次，掷出3点，共有[1,2],[2,1]两种掷法。
请求出投掷n次，掷出n~6n点分别有多少种掷法。
样例1
输入：n=1

输出：[1, 1, 1, 1, 1, 1]

解释：投掷1次，可能出现的点数为1-6，共计6种。每种点数都只有1种掷法。所以输出[1, 1, 1, 1, 1, 1]。
样例2
输入：n=2

输出：[1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1]

解释：投掷2次，可能出现的点数为2-12，共计11种。每种点数可能掷法数目分别为1,2,3,4,5,6,5,4,3,2,1。

      所以输出[1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1]。
	  

class Solution {
public:
    vector<int> numberOfDice(int n) {
        int f[n+1][6*n+2];
        memset(f,0,sizeof f);
        for (int i = 1; i <= 6; i++)f[1][i] = 1;
        for(int i=2;i<=n;i++){
            for(int j=i;j<=6*i;j++){
                for(int k=1;k<=6&&j>k;k++){
                    f[i][j]+=f[i-1][j-k];//第i次扔出的数字总和是j的情况数，
                }
            }
        }
        vector<int>v(f[n]+n,f[n]+6*n+1);
        return v;
    }
};   



//y总写法
class Solution {
public:
    vector<int> numberOfDice(int n) {
        vector<vector<int>> f(n + 1, vector<int>(n * 6 + 1));
        f[0][0] = 1;
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= i * 6; j ++ )
                for (int k = 1; k <= min(j, 6); k ++ )
                    f[i][j] += f[i - 1][j - k];

        vector<int> res;
        for (int i = n; i <= n * 6; i ++ ) res.push_back(f[n][i]);
        return res;
    }
};




//837. 新21点
爱丽丝参与一个大致基于纸牌游戏 “21点” 规则的游戏，描述如下：

爱丽丝以 0 分开始，并在她的得分少于 K 分时抽取数字。 抽取时，她从 [1, W] 的范围中随机获得一个整数作为分数进行累计，其中 W 是整数。 每次抽取都是独立的，其结果具有相同的概率。

当爱丽丝获得不少于 K 分时，她就停止抽取数字。 爱丽丝的分数不超过 N 的概率是多少？

示例 1：

输入：N = 10, K = 1, W = 10
输出：1.00000
说明：爱丽丝得到一张卡，然后停止。
示例 2：

输入：N = 6, K = 1, W = 10
输出：0.60000
说明：爱丽丝得到一张卡，然后停止。
在 W = 10 的 6 种可能下，她的得分不超过 N = 6 分。
示例 3：

输入：N = 21, K = 17, W = 10
输出：0.73278
提示：

0 <= K <= N <= 10000
1 <= W <= 10000
如果答案与正确答案的误差不超过 10^-5，则该答案将被视为正确答案通过。
此问题的判断限制时间已经减少。


class Solution {
public:
    double f[10010];
    double new21Game(int N, int K, int W) {
        f[K]=1;
        double res=0;
        int j=1;
        for(int i=K-1;i>=0;i--){
		
            double a; //以N=21,K = 17, W = 10为例，a是一步大于K的概率，
            if(i+W>=N)a=(double)(N-K+1)/W;
            else if(i+W<K)a=0;
            else a=(double)(i+W-K+1)/W;
			
            f[i]=((double)1/W)*res+a; //((double)1/W)*res是一步小于K的概率

            res+=f[i];
            if(i+W<=K-j){res-=f[K-j];j++;} //因为最多走W，所以超出的部分要减去
        }
        return f[0];
    }
};


//其实说简单点就是：令 dp[x]dp[x] 表示从得分为 x 的情况开始游戏并且获胜的概率，目标是求 dp[0] 的值。
dp[x]= (dp[x+1]+dp[x+2]+...+dp[x+W])/W;

class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (K == 0) {
            return 1.0;
        }
        vector<double> dp(K + W);
        for (int i = K; i <= N && i < K + W; i++) {
            dp[i] = 1.0;//
        }
        for (int i = K - 1; i >= 0; i--) {
            for (int j = 1; j <= W; j++) {
                dp[i] += dp[i + j] / W;
            }
        }
        return dp[0];
    }
};
​	
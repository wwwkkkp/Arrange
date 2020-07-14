/*309. 最佳买卖股票时机含冷冻期
给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。​

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
示例:

输入: [1,2,3,0,2]
输出: 3 
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]

输入：[4,2,7,1,11]
输出：10

股票类解法
https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/solution/yi-ge-fang-fa-tuan-mie-6-dao-gu-piao-wen-ti-by-lab/

*/

//动态规划 自己写的
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        if(!n||n==1) return 0;
        vector<vector<int>>ve(n,vector<int>(4,INT_MIN));  
		//ve[i][0]:当第i次是买入的时候 累计最多能挣的钱 
		//ve[i][1]:当第i次是持有股票的时候 累计最多挣的钱
		//ve[i][2]:当第i次是冷冻期的时候 累计最多挣的钱  ..这个在递推中没有用到，可以删去
		//ve[i][3]:当第i次是卖出的时候 累计最多挣的钱
        ve[0][0]=-prices[0];
        for(int i=1;i<n;i++){
            if(i<=2) ve[i][0]=-prices[i];
            else ve[i][0] =max(-prices[i], -prices[i] + ve[i - 2][3]);  //ve[i - 2][3]是目前累计挣的钱，然后和这次买入的钱相减，和 单纯买入的钱的最大值
            ve[i][1]=max(ve[i-1][1],ve[i-1][0]);   //这里考虑的是 第i-1次买 还是 第i-2次买 哪个更挣钱
            ve[i][2]=max(ve[i-1][2],ve[i-1][3]);  //这里考虑的是 第i-1次卖 还是 第i-2次卖 哪个更挣钱
            ve[i][3]=max(prices[i]+ve[i][1],ve[i-1][3]); //当前卖出是i-1次是持有或者买入的最大值加上价格 和上次卖出的最大值
        }
        return max(0,max(ve[n-1][1],ve[n-1][3]));
    }
};
 
//DP简化版 自己写的
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        if(!n||n==1) return 0;
        int v1=-prices[0];
        int v2=INT_MIN,v3=INT_MIN,v4=INT_MIN,v5=INT_MIN;
        for(int i=1;i<n;i++){
            int a=v1,d=v4;
            if(i<=2) v1=-prices[i];
            else v1 =max(-prices[i], -prices[i] + v5);
            v2=max(v2,a);
            v3=max(v3,v4);  //该句可删去
            v4=max(prices[i]+v2,v4);
            v5=d;
        }
        return max(0,max(v2,v4));
    }
};

//7.10版本1
const int N=6000;
class Solution {
public:
    int maxProfit(vector<int>& p) {
        int n=p.size();
        if(!n)return 0;
        p.insert(p.begin(),0);

        int f[N][4];
        f[0][1]=-0x3f3f3f;
        f[0][2]=0;
        f[0][3]=0;
        
		/*
		三种状态：当天操作是买入:f[i][1],          当天操作是卖出f[i][2],       当天操作是冷却f[i][3]
		买入只有两种情况转化而来，已经买了一只股票，当天不操作   和    从冷却过来，买当天的股票
		卖出只有两种情况转化而来，当天已经卖出股票，前一天已经卖出，今天不操作
		冷却两种情况转化而来，当天不操作，前一天已经卖了股票
		*/
        for(int i=1;i<=n;i++){
            f[i][1]=max(f[i-1][1],f[i-1][3]-p[i]);   //
            f[i][2]=max(f[i-1][2],f[i-1][1]+p[i]);
            f[i][3]=max(f[i-1][3],f[i-1][2]);
        }
        return max(f[n][2],f[n][3]);
    }
};

//7.10版本2 简化版本
class Solution {
public:
    int maxProfit(vector<int>& p) {
        int n=p.size();
        if(!n)return 0;
        p.insert(p.begin(),0);

        int a=-0x3f3f3f;
        int b=0;
        int c=0;
        
        for(int i=1;i<=n;i++){
            int a1=a,b1=b;
            a=a<c-p[i]?c-p[i]:a;
            b=b<a1+p[i]?a1+p[i]:b;
            c=c<b1?b1:c;
        }
        return b<c?c:b;
    }
};



//状态简化版
思路
每天可能存在三种状态：

hold：继续持有股票
sold：卖出股票
rest：什么都不做
转换关系如下：


hold： 可由两个情况转换来

前一天hold，当日rest
前一天rest，当日买入股票变为hold
sold：

前一天hold，当日卖出股票
rest：

前一天sold，当日必须rest
前一天rest，当日继续rest
所以

sold[i] = hold[i-1] + price[i];
hold[i] = max(hold[i-1], rest[i-1] - price[i])
rest[i] = max(rest[i-1], sold[i-1])
最后一天最大值情况为要么什么都不做，要么卖出股票，即 max(sold，rest)。

int maxProfit(vector<int>& prices) {
	int sold = 0, rest = 0, hold = INT_MIN;
	for (int p : prices) {
		int pre_sold = sold;
		sold = hold + p;
		hold = max(hold, rest - p);
		rest = max(rest, pre_sold);
	}
	return max(sold, rest);
}
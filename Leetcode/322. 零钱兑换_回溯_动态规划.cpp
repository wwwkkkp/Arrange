/*322. 零钱兑换
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

示例 1:

输入: coins = [1, 2, 5], amount = 11
输出: 3 
解释: 11 = 5 + 5 + 1

示例 2:

输入: coins = [2], amount = 3
输出: -1

说明:
你可以认为每种硬币的数量是无限的。

*/


//回溯
class Solution {
public:
    int DFS(vector<int>& coins,  int amount,vector<int>& vec) {  //这个函数代表的意思是当钱数是 amount 的时候的最小硬币个数
        if (amount < 0) return -1; //钱数小于零，返回-1
        if (vec[amount] != -1)
            return vec[amount]; //如果已经算过了，就不用算了  //最先到达这个数的，一定是最小硬币数，因为是从最大到最小计算的
        if (amount == 0 ) {
            return 1; //等于零返回1
        }
        int tmp= INT_MAX;
        for (int i = coins.size() - 1; i >= 0; i--) {
            if (coins[i] > amount)
                continue;
            else if (coins[i] <= amount) {
                int count=DFS(coins,  amount - coins[i],vec);  //当钱数是 amount 的时候的最小硬币个数
                if (count == -1||count== INT_MAX) continue;
                tmp = min(count + 1,tmp);
                vec[amount] = tmp;  //钱数对应的硬币数的备忘录，等于最小值  
            }
        }
        if (tmp == INT_MAX) {
            vec[amount] = INT_MAX;
            return -1;
        }
        return tmp;
    }
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());
        vector<int>vec(amount + 1, -1);
        vec[0] = 0;
        for (auto c : coins)
            if(c<amount)
                vec[c] = 1;
        int count=DFS(coins,  amount,  vec);
        return count;
    }
};





//动规

int coinChange(vector<int>& coins, int amount) {
	vector<int> dp(amount + 1, amount + 1);   
	dp[0] = 0;  //没有钱的时候就不需要硬币
	for (int i = 1; i <= amount; i++) {
		for (int coin : coins)
			if (coin <= i)
				dp[i] = min(dp[i], dp[i - coin] + 1);  //递推公式
	}
	return dp[amount] > amount ? -1 : dp[amount];
}

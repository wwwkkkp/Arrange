


1049. 最后一块石头的重量 II

有一堆石头，每块石头的重量都是正整数。

每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：

如果 x == y，那么两块石头都会被完全粉碎；
如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
最后，最多只会剩下一块石头。返回此石头最小的可能重量。如果没有石头剩下，就返回 0。

 

示例：

输入：[2,7,4,1,8,1]
输出：1
解释：
组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]，
组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]，
组合 2 和 1，得到 1，所以数组转化为 [1,1,1]，
组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。
 

提示：

1 <= stones.length <= 30
1 <= stones[i] <= 1000



//0-1背包问题
class Solution {
public:
    int lastStoneWeightII(vector<int>& v) {
        int n=v.size();
        if(!n)return 0;
        
        int s=0;
        for(auto c:v)s+=c;
        sort(v.begin(),v.end());
        
        int dp[40][10000];   //前i个数中，当背包容量是j的时候，最多能装多少个
        memset(dp,0,sizeof dp);
        
        for(int i=0;i<n;i++){
            for(int j=0;j<=s/2;j++){
                if(j-v[i]>=0){
                    if(i==0)dp[i][j]=v[i];
                    else dp[i][j]=max(dp[i-1][j-v[i]]+v[i],dp[i-1][j]);    //当前石头装或者不装
                }else{
                    if(i==0)dp[i][j]=0;
                    else dp[i][j]=dp[i-1][j];  //当前石头重量比背包容量大
                }
            }
        }
        return s-2*dp[n-1][s/2];
    }
};
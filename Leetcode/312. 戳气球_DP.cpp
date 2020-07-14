
//312. 戳气球_DP


有 n 个气球，编号为0 到 n-1，每个气球上都标有一个数字，这些数字存在数组 nums 中。

现在要求你戳破所有的气球。每当你戳破一个气球 i 时，你可以获得 nums[left] * nums[i] * nums[right] 个硬币。 这里的 left 和 right 代表和 i 相邻的两个气球的序号。注意当你戳破了气球 i 后，气球 left 和气球 right 就变成了相邻的气球。

求所能获得硬币的最大数量。

说明:

你可以假设 nums[-1] = nums[n] = 1，但注意它们不是真实存在的所以并不能被戳破。
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
示例:

输入: [3,1,5,8]
输出: 167 
解释: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
     coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167



//这道题的思路是逆向的，每次删除一个数可以看成每次增加一个数，每次操作的最大值不一定是最终的最大值，当遇到删除问题的时候，可以逆向考虑成增加问题
class Solution {
public:
    int f[510][510];
    int maxCoins(vector<int>& nums) {
        int n=nums.size();
        vector<int> num(n+2);
        for(int i=1;i<=n;i++)
            num[i]=nums[i-1];
        num[0]=num[n+1]=1;
        memset(f,-1,sizeof f);
        return m(num,0,n+1);
        
    }
    int m(vector<int>&num,int le,int ri){//在 le 和 ri 之间添加一个数所获得的最大收益，注意le 和ri 是开区间，
        if(ri==le+1) return f[le][ri]=0;
        if(f[le][ri]>0) return f[le][ri];
        int res=0;
        for(int i=le+1;i<ri;i++){  //分开之后这个问题就变成了le到i，i到ri
            res=max(res,num[i]*num[le]*num[ri]+m(num,le,i)+m(num,i,ri));
        }
        f[le][ri]=res;
        return res;
    }
};

//上述题目也可以解释为：f[le][ri]为在(le,ri)区间中戳破所有气球所获得的最大值，假设i为最后戳破的气球，f[le][ri]=max(f[le][ri],num[i]*num[le]*num[ri]+f[le][i]+f[i][ri]);



int maxCoins(int[] nums) {
    int n = nums.length;
    // 添加两侧的虚拟气球
    int[] points = new int[n + 2];
    points[0] = points[n + 1] = 1;
    for (int i = 1; i <= n; i++) {
        points[i] = nums[i - 1];
    }
    // base case 已经都被初始化为 0
    int[][] dp = new int[n + 2][n + 2];
    // 开始状态转移
    // i 应该从下往上
    for (int i = n; i >= 0; i--) {
        // j 应该从左往右
        for (int j = i + 1; j < n + 2; j++) {
            // 最后戳破的气球是哪个？
            for (int k = i + 1; k < j; k++) {
                // 择优做选择
                dp[i][j] = Math.max(
                    dp[i][j], 
                    dp[i][k] + dp[k][j] + points[i]*points[j]*points[k]
                );
            }
        }
    }
    return dp[0][n + 1];
}


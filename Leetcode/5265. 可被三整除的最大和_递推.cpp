//5265. 可被三整除的最大和
/*
给你一个整数数组 nums，请你找出并返回能被三整除的元素最大和。

 

示例 1：

输入：nums = [3,6,5,1,8]
输出：18
解释：选出数字 3, 6, 1 和 8，它们的和是 18（可被 3 整除的最大和）。
示例 2：

输入：nums = [4]
输出：0
解释：4 不能被 3 整除，所以无法选出数字，返回 0。
示例 3：

输入：nums = [1,2,3,4,4]
输出：12
解释：选出数字 1, 3, 4 以及 4，它们的和是 12（可被 3 整除的最大和）。

提示：
	1 <= nums.length <= 4 * 10^4
	1 <= nums[i] <= 10^4
*/

//方法一 递归 该方法处理数据长度较短的nums尚可，处理这道题的大数组就不行了
class Solution {
public:
    int maxsum[40001];
	void dfs(vector<int>& nums,int begin,int tem){
        int size=nums.size();
        if(begin>=size)
            return;
        if(tem%3==0 && begin>=0){
            if(maxsum[begin]>=tem)
                return;
            else
                maxsum[begin]=tem;
        }
        for(int i=begin+1;i<nums.size();i++){
            tem+=nums[i];
            dfs(nums,i,tem);
            tem-=nums[i];
        }
    }
    int maxSumDivThree(vector<int>& nums) {
        int tem=0;
        int size=nums.size();
        for(int i=0;i<40001;i++)
            maxsum[i]=0;
        dfs(nums,-1,tem);
        return *max_element(maxsum,maxsum+size);
    }
};


//方法二 递推
/*
不妨设dp[i] 代表 选取的数字累加和 模3 = i 的数字和
假定nums[i] % 3 = 1 ，那么，和 前面选取的数字和模 3 = 2 的数相加，就可以模3为 0 ，表达起来就是 dp[0] = max(dp[0], nums[i] + dp[2])
依次类推，只要不断更新 dp 数组即可，注意一点，更新的时候要保存上一个状态的值，避免后续更新的时候重复影响。
*/
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int dp[3] = { 0,0,0 };  //这里储存的是余数分别是0,1,2的最大和
        for (int i = 0; i < nums.size(); i++) {
            int mod = nums[i] % 3;
            int a = dp[0], b = dp[1], c = dp[2];//先让其等于一个中间值，因为这里的数都是要和上一状态的dp计算，如果直接算的话导致重复计算
            if (mod == 0) {
                a = dp[0] + nums[i];
                if (dp[1]) b = dp[1] + nums[i]; //因为初始值是0,0是不能被1整除的，所以dp[1]=0的时候是不能代入计算的，要等后面有余数是1数给dp[1]赋值以后，才能带入计算
                if (dp[2]) c = dp[2] + nums[i];//dp[2]同理
            }
            if (mod == 1) {
                if (dp[2]) a = max(dp[0], dp[2] + nums[i]);
                b = max(dp[1], dp[0] + nums[i]);
                if (dp[1]) c = max(dp[2], dp[1] + nums[i]);
            }
            if (mod == 2) {
                if (dp[1]) a = max(dp[0], dp[1] + nums[i]);
                if (dp[2]) b = max(dp[1], dp[2] + nums[i]);
                c = max(dp[2], dp[0] + nums[i]);
            }
            dp[0]=a,  dp[1]=b,  dp[2]=c;
        }
        return dp[0];
    }
};

//递推精简版
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int dp[3] = {0, 0, 0};
        
        for (int i = 0; i < nums.size(); ++i) {
            int mod = nums[i] % 3;

            int a = dp[(3 + 0 - mod) % 3];
            int b = dp[(3 + 1 - mod) % 3];
            int c = dp[(3 + 2 - mod) % 3];
            
            if (a || mod == 0) dp[0] = std::max(dp[0], a + nums[i]);
            if (b || mod == 1) dp[1] = std::max(dp[1], b + nums[i]);
            if (c || mod == 2) dp[2] = std::max(dp[2], c + nums[i]);
        }
        return dp[0];
    }
};

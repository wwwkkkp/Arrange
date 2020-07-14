//7.4 55. 连续子数组的最大和 



输入一个 非空 整型数组，数组里的数可能为正，也可能为负。
数组中一个或连续的多个整数组成一个子数组。
求所有子数组的和的最大值。
要求时间复杂度为O(n)。
样例
输入：[1, -2, 3, 10, -4, 7, 2, -5]

输出：18





class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(!nums.size()) return 0;
        int n=nums.size();

        int res=INT_MIN;
        int s=0;  //以第n-1个数结尾的子串最大和
        for(int i=0;i<n;i++){
            if(s<=0) s=nums[i];
            else s+=nums[i];
            res=max(res,s);
        }
        return res;
    }
};
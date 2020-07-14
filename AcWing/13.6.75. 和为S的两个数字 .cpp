//13.6.75. 和为S的两个数字 
输入一个数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。
如果有多对数字的和等于s，输出任意一对即可。
你可以认为每组输入中都至少含有一组满足条件的输出。
样例
输入：[1,2,3,4] , sum=7

输出：[3,4]

class Solution {
public:
    vector<int> findNumbersWithSum(vector<int>& nums, int t) {
        unordered_map<int ,int >um;
        int n=nums.size();
        for(int i=0;i<n;i++){
            um[nums[i]]=1;
        }
        for(int i=0;i<n;i++){
            if(um.count(t-nums[i])) //如果目标减去当前数后在um中能找到，那说明找到了一对
                return {nums[i],t-nums[i]};
        }
    }
};
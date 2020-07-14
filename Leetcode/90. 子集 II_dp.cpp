

//90. 子集 II
给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。

示例:

输入: [1,2,2]
输出:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]


//DP，用set去掉同样的项
class Solution {
public:
    set<vector<int>>us;
    vector<vector<int>>v;
    vector<int>v1;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n=nums.size();
        if(!n)return {{}};
        sort(nums.begin(),nums.end());
        work(nums,0,n);
        
        for(auto c:us)v.push_back(c);
        return v;
        
    }
    void work(vector<int>&nums,int a,int n){
        if(a==n){
            us.insert(v1);
            return;
        }
        v1.push_back(nums[a]);
        work(nums,a+1,n);
        v1.pop_back();
        work(nums,a+1,n);
        return ;
    }
};


//78. 子集
给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。

示例:

输入: nums = [1,2,3]
输出:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

//回溯
class Solution {
public:
    int n1;
    bool f[1000];
    vector<vector<int>>v;
    vector<vector<int>> subsets(vector<int>& nums) {
        int n=nums.size();
        if(!n)return {};
        n1=n;
        memset(f,0,sizeof f);
        dfs(0,nums);
        return v;
    }
    void dfs(int a,vector<int>& nums){
        if(a==n1){
            vector<int>v1;
            for(int i=0;i<n1;i++){
                if(f[i])v1.push_back(nums[i]);
            }
            v.push_back(v1);
            return;
        }       
        f[a]=true;
        dfs(a+1,nums);
        f[a]=false;
        dfs(a+1,nums);
    }
};


//第二种方法好一些
class Solution {
public:
    int n1;
    vector<int>v1;
    vector<vector<int>>v;
    vector<vector<int>> subsets(vector<int>& nums) {
        int n=nums.size();
        if(!n)return {{}};
        n1=n;
        dfs(0,nums);
        return v;
    }
    void dfs(int a,vector<int>& nums){
        if(a==n1){
            v.push_back(v1);
            return;
        }       
        v1.push_back(nums[a]);
        dfs(a+1,nums);
        v1.pop_back();
        dfs(a+1,nums);
    }
};
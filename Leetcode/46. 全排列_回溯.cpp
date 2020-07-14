
//46. 全排列
给定一个 没有重复 数字的序列，返回其所有可能的全排列。

示例:

输入: [1,2,3]
输出:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]


//全排列函数
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>v;
        sort(nums.begin(),nums.end());  //注意，全排列函数要先排序，才能执行
        v.push_back(nums);
        while(next_permutation(nums.begin(),nums.end()))v.push_back(nums);
        return v;
        
    }
};


//回溯算法
class Solution {
public:
    bool b[1000];
    vector<int>v1;
    vector<int>v2;
    vector<vector<int>>v;
    vector<vector<int>> permute(vector<int>& nums) {
        v1=nums;
        memset(b,0,sizeof(b));
        dfs(0);
        return v;
    }
    void dfs(int a){
        if(a==v1.size()){
            v.push_back(v2);
        }
        for(int i=0;i<v1.size();i++){
            if(!b[i]){
                b[i]=1;
                v2.push_back(v1[i]);
                dfs(a+1);
                v2.pop_back();
                b[i]=0;
            }
        }
    }
};
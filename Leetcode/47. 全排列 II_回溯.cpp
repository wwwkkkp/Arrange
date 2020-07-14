
//47. 全排列 II
给定一个可包含重复数字的序列，返回所有不重复的全排列。

示例:

输入: [1,1,2]
输出:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]


//全排列函数
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        set<vector<int>>us;
        vector<vector<int>>v;
        sort(nums.begin(),nums.end());
        us.insert(nums);
        while(next_permutation(nums.begin(),nums.end()))us.insert(nums);
        for(auto c:us)v.push_back(c);
        return v;
    }
};


//回溯
class Solution {
public:
    bool b[1000];
    vector<int>v1,v2;
    vector<vector<int>>v3;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        v1=nums;
        memset(b,0,sizeof b);
        dfs(0);
        return v3;
    }
    void dfs(int a){
        if(a==v1.size()){
            v3.push_back(v2);
            return;
        }
        for(int i=0;i<v1.size();){
            if(!b[i]){
                b[i]=1;
                v2.push_back(v1[i]);
                dfs(a+1);
                b[i]=0;
                v2.pop_back();
				
				int j=i;
				while(j<v1.size()&&v1[i]==v1[j])j++; //这里意味着，在第a个位置上，不能选和当前数一样的数了，6.3一样的题，写法更好
                i=j;
            }else i++;
        }
    }
};
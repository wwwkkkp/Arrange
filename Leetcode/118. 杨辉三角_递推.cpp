//118. 杨辉三角
给定一个非负整数 numRows，生成杨辉三角的前 numRows 行。



在杨辉三角中，每个数是它左上方和右上方的数的和。

示例:

输入: 5
输出:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]



//递推
class Solution {
public:
    vector<vector<int>> generate(int n) {
        if(!n)return {};
        vector<vector<int>>v;
        v.push_back({1});
        if(n==1)return v;
        for(int i=2;i<=n;i++){
            vector<int>v1(i);
            for(int j=0;j<i;j++){
                if(j==0)v1[0]=1;
                else if(j==i-1)v1[j]=1;
                else v1[j]=v.back()[j-1]+v.back()[j];
            }
            v.push_back(v1);
        }
        return v;
    }
};
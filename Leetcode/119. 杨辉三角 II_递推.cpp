

//119. 杨辉三角 II
给定一个非负索引 k，其中 k ≤ 33，返回杨辉三角的第 k 行。



在杨辉三角中，每个数是它左上方和右上方的数的和。

示例:

输入: 3
输出: [1,3,3,1]
进阶：

你可以优化你的算法到 O(k) 空间复杂度吗？



//和118一样，要注意说输出第x行，是从0开始的数的
class Solution {
public:
    vector<int> getRow(int n) {
        if(n<0)return {1};
        n++;
        if(!n)return {};
        vector<vector<int>>v;
        v.push_back({1});
        if(n==1)return v.back();
        for(int i=2;i<=n;i++){
            vector<int>v1(i);
            for(int j=0;j<i;j++){
                if(j==0)v1[0]=1;
                else if(j==i-1)v1[j]=1;
                else v1[j]=v.back()[j-1]+v.back()[j];
            }
            v.push_back(v1);a
        }
        return v.back();
    }
};
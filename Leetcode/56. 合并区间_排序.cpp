


//56. 合并区间
给出一个区间的集合，请合并所有重叠的区间。

示例 1:

输入: [[1,3],[2,6],[8,10],[15,18]]
输出: [[1,6],[8,10],[15,18]]
解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2:

输入: [[1,4],[4,5]]
输出: [[1,5]]
解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& in) {
        int n=in.size();
        if(!n)return {};
        sort(in.begin(),in.end()); //先排序
        vector<vector<int>>v;
        v.push_back(in[0]);
        for(int i=1;i<n;i++){
            if(in[i][0]<=v.back()[1])v.back()[1]=max(v.back()[1],in[i][1]);//如果in中的数和v.back()有重叠，就合并，注意，只可能和 v.back()有冲突，
            else v.push_back(in[i]);
        }
        return v;
    }
};
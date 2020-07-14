

//57. 插入区间
给出一个无重叠的 ，按照区间起始端点排序的区间列表。

在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。

示例 1:

输入: intervals = [[1,3],[6,9]], newInterval = [2,5]
输出: [[1,5],[6,9]]
示例 2:

输入: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
输出: [[1,2],[3,10],[12,16]]
解释: 这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。

//贪心，就是找出重合区间
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& in, vector<int>& ne) {
        int n= in.size();
        vector<vector<int>>v;
        if(!n) {
            v.push_back(ne);
            return v;
        }
        sort(in.begin(),in.end());
        int i=0;
        while(i<n&&in[i][1]<ne[0])v.push_back(in[i]),i++;  //找出左相交区间
        vector<int>v1(2);
        if(i<n){
            v1[0]=min(in[i][0],ne[0]);
        }else v1[0]=ne[0];
        while(i<n&&in[i][0]<=ne[1])i++; //找出右相交区间
		
        if(!i)v1[1]=ne[1];
        else v1[1]=max(in[i-1][1],ne[1]);
		
        v.push_back(v1);
        while(i<n){v.push_back(in[i]);i++;}
        return v;
    }
};

//这样写好一些
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;
        bool flag = false;        //新区间是否放置进答案
        for(int i = 0; i < intervals.size(); i++){
            if(newInterval[0] > intervals[i][1]){
                ans.push_back(intervals[i]);//比newInterval小的区间
                continue;
            }
            if(newInterval[1] < intervals[i][0]){//比newInterval大的区间
                ans.push_back(newInterval);
                flag = !flag;
                for(; i < intervals.size(); i++) //新区间放进答案后，后面的就直接添加了，
                    ans.push_back(intervals[i]);
                break;
            }
            newInterval[0] = min(newInterval[0], intervals[i][0]);  //区间合并
            newInterval[1] = max(newInterval[1], intervals[i][1]);
        }
        if(!flag)
            ans.push_back(newInterval);
        
        return ans;
    }
};

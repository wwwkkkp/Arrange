
//84. 柱状图中最大的矩形
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

示例:

输入: [2,1,5,6,2,3]
输出: 10

//单调栈
class Solution {
public:
    int largestRectangleArea(vector<int>& h) {
        int left[100000],right[100000];
        int n=h.size();
        if(!n)return 0;
        
        h.insert(h.begin(),0);
        h.push_back(0);
        
        int q[100000];
        int tt=0;
        q[0]=0;
        for(int i=1;i<=n;i++){

            while(tt>=1&&h[q[tt]]>=h[i])tt--;
            left[i]=i-q[tt];  //这里可以是q[tt]，表示的就是左边能到达的位置，现在是能向左边延伸几格
            q[++tt]=i;
        }
        tt=0;
        q[tt]=n+1;
        for(int i=n;i>0;i--){
            while(tt>=1&&h[q[tt]]>=h[i])tt--;
            right[i]=q[tt]-i;
            q[++tt]=i;
        }
        
        int res=0;
        for(int i=1;i<=n;i++){
            res=max(res,(right[i]+left[i]-1)*h[i]);

        }
        return res;
    }
};
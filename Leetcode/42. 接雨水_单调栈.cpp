


//42. 接雨水
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。



上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 感谢 Marcos 贡献此图。

示例:

输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6

//单调栈 单调递减
class Solution {
public:
    int trap(vector<int>& ht) {
        int n=ht.size();

        int q[100];
        int tt=0;
        q[0]=0;
        int res=0;
        for(int i=0;i<n;i++){
            int v=0;
            while(tt>=1&&ht[q[tt]]<=ht[i]){
                res+=(ht[q[tt]]-v)*(i-q[tt]-1); 
                v=ht[q[tt]];
                tt--;
            }
            if(tt>=1&&ht[q[tt]]>ht[i]){
                res+=(ht[i]-v)*(i-q[tt]-1);   
            }
            q[++tt]=i;
        }
        return res;
    }
};


class Solution {
public:
    int trap(vector<int>& ht) {
        int n=ht.size();
        
        ht.insert(ht.begin(),0);//可以添加这一项，作为单调栈统一模板
        int q[100];
        int tt=0;
        q[0]=0;
        int res=0;
        for(int i=1;i<=n;i++){
            int v=0;
            while(tt>=1&&ht[q[tt]]<=ht[i]){
                res+=(ht[q[tt]]-v)*(i-q[tt]-1); 
                v=ht[q[tt]];
                tt--;
            }
            if(tt>=1&&ht[q[tt]]>ht[i]){
                res+=(ht[i]-v)*(i-q[tt]-1);   
            }
            q[++tt]=i;
        }
        return res;
    }
};
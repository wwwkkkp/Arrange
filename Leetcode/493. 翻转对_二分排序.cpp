

//493. 翻转对
给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。

你需要返回给定数组中的重要翻转对的数量。

示例 1:

输入: [1,3,2,3,1]
输出: 2
示例 2:

输入: [2,4,3,5,1]
输出: 3
注意:

给定数组的长度不会超过50000。
输入数组中的所有数字都在32位整数的表示范围内。


//二分排序，分治
class Solution {
public:
    int res=0;
    void merge(vector<long long >&v1,vector<long long >&v2,int a,int b){
        if(b==a)return;
        int c=a+b>>1;
        merge(v1,v2,a,c);
        merge(v1,v2,c+1,b);
        int i=c,j=b;
		
        for(;i>=a&&j>=c+1;){ //统计前后两块满足条件的个数，这个时候两边都分别排好序了，只需要从最大值往前遍历就行
            if(v1[i]-v1[j]>v1[j]){
                res+=j-c;
                i--;
                continue;
            }
            j--;
        }
		
        i=a;j=c+1; //双指针排序
        int k=a;
        while(i<=c&&j<=b){
            if(v1[i]>v1[j]){v2[k++]=v1[j];j++;}
            else{v2[k++]=v1[i];i++;}
        }
        if(i<=c){
            for(int p=i;p<=c;p++){
                v2[k++]=v1[p];
            }
        }
        if(j<=b){
            for(int p=j;p<=b;p++){
                v2[k++]=v1[p];
            }
        }
        for(int q=a;q<=b;q++)
            v1[q]=v2[q];
        
    }
    
    int reversePairs(vector<int>& nums) {
        int n=nums.size();
        if(!n)return n;
        vector<long long>v1(nums.begin(),nums.end());  //数据运算容易超过int范围，用long long 替代
        vector<long long>v2(n);
        merge(v1,v2,0,n-1);
        return res;
    }
};


//560. 和为K的子数组
给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。

示例 1 :

输入:nums = [1,1,1], k = 2
输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
说明 :

数组的长度为 [1, 20,000]。
数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。


//令f为前i项的和，这道题就是寻找f[i]-f[j]+nums[j]=k,满足这个式子的数，转换一下：f[i]=k+f[j]-nums[j] （i>=j）,对所有的j进行遍历，找是否有满足这个式子的i,(i>=j)
class Solution {
public:
    const int N=20010;
    int subarraySum(vector<int>& nums, int k) {
        int n=nums.size();
        if(!n)return 0;
        if(n==1) return nums[0]==k?1:0;
        int f[N];
        unordered_map<int,vector<int>>up;
        f[0]=nums[0];
        up[f[0]].push_back(0);
        for(int i=1;i<n;i++){
            f[i]=f[i-1]+nums[i];
            up[f[i]].push_back(i);
        }
        int res=0;
        for(int j=0;j<n;j++){
            auto w=up.find(f[j]-nums[j]+k);
            if(w!=up.end()){
                vector<int>v=w->second;
                for(auto e:v){
                    if(e>=j)
                        res++;
                }
            }
        }
        return res;
    }
};
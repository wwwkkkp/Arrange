

1300. 转变数组后最接近目标值的数组和
给你一个整数数组 arr 和一个目标值 target ，请你返回一个整数 value ，使得将数组中所有大于 value 的值变成 value 后，数组的和最接近  target （最接近表示两者之差的绝对值最小）。

如果有多种使得和最接近 target 的方案，请你返回这些整数中的最小值。

请注意，答案不一定是 arr 中的数字。

 

示例 1：

输入：arr = [4,9,3], target = 10
输出：3
解释：当选择 value 为 3 时，数组会变成 [3, 3, 3]，和为 9 ，这是最接近 target 的方案。
示例 2：

输入：arr = [2,3,5], target = 10
输出：5
示例 3：

输入：arr = [60864,25176,27249,21296,20204], target = 56803
输出：11361
 

提示：

1 <= arr.length <= 10^4
1 <= arr[i], target <= 10^5






class Solution {
public:
    int findBestValue(vector<int>& v, int t) {
        int n=v.size();
        if(!n)return 0;
        
        sort(v.begin(),v.end());
        v.insert(v.begin(),0);
        v.push_back(0);
        
        long long f[10010];
        
        for(int i=1;i<=n;i++)f[i]=f[i-1]+v[i];
        int res=0,k=100000;
        
        for(int i=0;i<=v[n];i++){
            int l=0,r=n;
            while(l<r){             //寻找当阈值时i的时候，刚好比i大的那个数在哪个位置
                int mid=r+l+1>>1;
                if(v[mid]>i)r=mid-1;
                else l=mid;
            }
            int sum=f[r]+(n-r)*i;
            if(abs(sum-t)<k){
                res=i;
                k=abs(sum-t);
            }
        }
        return res;
    }
};
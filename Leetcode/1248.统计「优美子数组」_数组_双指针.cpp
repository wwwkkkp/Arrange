/*
5248. 统计「优美子数组」

给你一个整数数组 nums 和一个整数 k。

如果某个子数组中恰好有 k 个奇数数字，我们就认为这个子数组是「优美子数组」。

请返回这个数组中「优美子数组」的数目。

 子数组是连续的

示例 1：

输入：nums = [1,1,2,1,1], k = 3
输出：2
解释：包含 3 个奇数的子数组是 [1,1,2,1] 和 [1,2,1,1] 。
示例 2：

输入：nums = [2,4,6], k = 1
输出：0
解释：数列中不包含任何奇数，所以不存在优美子数组。
示例 3：

输入：nums = [2,2,2,1,2,2,1,2,2,2], k = 2
输出：16
*/

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int L = 0, R = 0;
        int n = 0;
        int ssize = nums.size();
        int flag[ssize+1], j = 0;  //flag保存的是两个奇数之间偶数的数量  
        for (int i = 0; i < ssize; i++) {
            if (nums[i] % 2 == 0) {
                n++;
            }
            else {
                flag[j++] = n;
                n = 0;
            }
        }
        flag[j] = n;  //flag中数的数量-1就是奇数的个数
        int sum = 0;
        for (int i = 0; i <= j - k; i++) {  
            sum += (flag[i] + 1)*(flag[i+k]+1);//举例第三个例子：flag=[3,2,3],sum=(3+1)*(2+1)+(2+1)*(3+1),
        }

        return sum;
    }
};


//这个也是双指针，好懂一点
class Solution {
public:
    const int N=50010;
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n=nums.size();
        int le[N],ri[N];
        le[0]=1;
        for(int i=1;i<n;i++){
            if(nums[i-1]%2) le[i]=1;
            else le[i]=le[i-1]+1; //第i个数左边有多少个偶数
        }
        ri[n-1]=1;
        for(int i=n-2;i>=0;i--){
            if(nums[i+1]%2) ri[i]=1;
            else ri[i]=ri[i+1]+1; //第i个数右边有多少个偶数
        }
        int i=0;
        while(i<n&&!(nums[i]%2))i++;
        if(i==n)return 0;
        int j=i;
        while(j<n&&k){
            if(nums[j]%2)//保证i j之间有k个奇数
                k--;
            if(k)j++;
        }
        if(j==n) return 0;
        int res=0;
        while(j<n){
            while(j<n&&!(nums[j]%2))j++;//循环执行
            while(i<n&&!(nums[i]%2))i++;
            res+=le[i]*ri[j];
            i++,j++;
        }
        return res;

    }
};
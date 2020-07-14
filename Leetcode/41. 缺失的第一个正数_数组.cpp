



//41. 缺失的第一个正数
给你一个未排序的整数数组，请你找出其中没有出现的最小的正整数。

 

示例 1:

输入: [1,2,0]
输出: 3
示例 2:

输入: [3,4,-1,1]
输出: 2
示例 3:

输入: [7,8,9,11,12]
输出: 1
 

提示：

你的算法的时间复杂度应为O(n)，并且只能使用常数级别的额外空间。



//这个方法虽然可行，但是空间复杂度不符合要求
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        set<int>us;
        for(auto c:nums)us.insert(c);
        int i=1;
        for(auto c:us){
            if(c>0){
                if(c==i){
                    i++;
                    continue;
                }
                break;
            }
        }
        return i;
    }
};

//正确解法
自己做一个哈希映射，即让第i个位置放的数是i+1，通过交换实现
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n=nums.size();
        for(int i=0;i<n;i++){
            while(nums[i]!=i+1){  //要保证nums[i]=i+1
                if(nums[i]<=0||nums[i]>=n||nums[i]==nums[nums[i]-1]){ //当nums[i]是负数，大于n，或者和目标位置上的数相等了，就跳出while
                    break;
                }
                int k=nums[nums[i]-1];//把数交换到对应位置上，以[3,4,-1,1]为例，i=0时，把3交换到i=2的位置上去
                nums[nums[i]-1]=nums[i];
                nums[i]=k;
            }
        }
        for(int i=0;i<n;i++)	//第一个不符合nums[i]=i+1条件的就是答案，
            if(nums[i]!=i+1)
                return i+1;
        return n+1;
    }
};
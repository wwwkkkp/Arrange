
//136. 只出现一次的数字

给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

说明：

你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？

示例 1:

输入: [2,2,1]
输出: 1
示例 2:

输入: [4,1,2,1,2]
输出: 4


//位运算
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        if(!nums.size())return 0;
        if(nums.size()==1)return nums[0];
        int a=0,b=1;
        for(;b<nums.size();a+=2,b+=2){
            if(nums[a]==nums[b])continue;
            else break;
        }
        return nums[a];
    }
};



//哈希表
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        if(!nums.size())return 0;
        unordered_map<int,int>up;
        for(int i=0;i<nums.size();i++){
            up[nums[i]]++;
        }
        auto it=up.begin();
        for(;it!=up.end();it++)
            if(it->second==1)
                break;
        return it->first;
    }
};


//异或运算 相同为0，不同为1
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res=0;
        for(int e:nums)res^=e;
        return res;
    }
};



//80. 删除排序数组中的重复项 II
给定一个排序数组，你需要在原地删除重复出现的元素,/使得每个元素最多出现两次，返回移除后数组的新长度。

不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。

示例 1:

给定 nums = [1,1,1,2,2,3],

函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3 。

你不需要考虑数组中超出新长度后面的元素。
示例 2:

给定 nums = [0,0,1,1,1,1,2,3,3],

函数应返回新长度 length = 7, 并且原数组的前五个元素被修改为 0, 0, 1, 1, 2, 3, 3 。

你不需要考虑数组中超出新长度后面的元素。


//数组
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n=nums.size();
        if(!n)return 0;
        sort(nums.begin(),nums.end());
        int i=0,j=0;  //标识位，j==1表示已经留了两个数，开始删除多余的数，
        while(i<nums.size()){
            if(j==0&&i+1<nums.size()&&nums[i]==nums[i+1]){i++;j=1;continue;}
            while(j==1&&i+1<nums.size()&&nums[i]==nums[i+1]){
                nums.erase(nums.begin()+i+1);
            }
            i++;j=0;
        }
        return nums.size();
    }
};



//如果最多出现一次
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        nums.erase(unique(nums.begin(),nums.end()),nums.end());
        return nums.size();
    }
};
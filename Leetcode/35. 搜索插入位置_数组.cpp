
//35. 搜索插入位置
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

你可以假设数组中无重复元素。

示例 1:

输入: [1,3,5,6], 5
输出: 2
示例 2:

输入: [1,3,5,6], 2
输出: 1
示例 3:

输入: [1,3,5,6], 7
输出: 4
示例 4:

输入: [1,3,5,6], 0
输出: 0


class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        for(int i=0;i<nums.size();i++)
            if(nums[i]==target)
                return i;
        for(int i=0;i<nums.size();i++)
            if(nums[i]>target)
                return i;
        return nums.size();
    }
};



//二分
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left=0,right=nums.size();
        while(left<right){
            int mid=left+right>>1;
            if(nums[mid]==target)return mid;
            if(nums[mid]>target)right=mid;
            else left=mid+1;
        }
        return right;
    }
};

//注意区分这个二分和上个二分的区别，

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left=0,right=nums.size();
        while(left<right){
            int mid=left+right+1>>1;   //这里用的是而二分的模板，如果下面是right=mid-1;那这里就是left+right+1
            if(nums[mid]==target)return mid;
            if(nums[mid]>target)right=mid-1;
            else left=mid;
        }
        return right;
    }
};

/** 区别：如果目标数在left和right之间，而right-left=1，这种情况下，	如果取的是较小值，也就是left，那就用第二种二分，下取整
																	如果取的是较大值，也就是right，用第一种二分，上取整 
																	举例：x,y,z这三个数，	下取整的判断是 f(mid)>t;范围是[y,z);结果是y
																							上取整的判断是 f(mid)>=t;范围是(x,y];结果是y
																	*/
参考 H指数II 这道题，取得就是较小的那个数，和其他情况不一样




vector<int>v = { 1,2,3,4,5,6,7,8,9 };
int work(int a) {
	return v[a];
}
double w = 4.5;
int main() {
	int l = 0, r = 8;
	while (l < r) {			//向下取整
		int m = r + l+1 >> 1; 
		if (work(m) > w)r = m-1;
		else l = m ;
	}
	int l1 = 0, r1 = 8;
	while (l1 < r1) {		//向上取整   这个一般比较常用，如果是vector中取最小值，用上面的那个
		int m = r1 + l1  >> 1;
		if (work(m) >= w)r1 = m ;
		else l1 = m+1;
	}

	return 0;
}
r=4
r1=5;
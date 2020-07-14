


//215. 数组中的第K个最大元素
在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

示例 1:

输入: [3,2,1,5,6,4] 和 k = 2
输出: 5
示例 2:

输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4
说明:

你可以假设 k 总是有效的，且 1 ≤ k ≤ 数组的长度。


//快捷方法 nth_element
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n=nums.size();
        nth_element(nums.begin(),nums.begin()+n-k,nums.end());//找出第k大的数字
		//sort(nums.begin(),nums.end());    //直接排序也可以
        return nums[n-k];
    }
};
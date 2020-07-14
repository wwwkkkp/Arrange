


//75. 颜色分类
给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

注意:
不能使用代码库中的排序函数来解决这道题。

示例:

输入: [2,0,2,1,1,0]
输出: [0,0,1,1,2,2]
进阶：

一个直观的解决方案是使用计数排序的两趟扫描算法。
首先，迭代计算出0、1 和 2 元素的个数，然后按照0、1、2的排序，重写当前数组。
你能想出一个仅使用常数空间的一趟扫描算法吗？


//数组，本题也可以用双指针法
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n=nums.size();
        int x=0,y=0,z=0;
        for(int i=0;i<n;i++){
            if(nums[i]==0)x++;
            else if(nums[i]==1)y++;
            else z++;
        }
        int i=0;
        while(x--)nums[i++]=0;
        while(y--)nums[i++]=1;
        while(z--)nums[i++]=2;
        return;
    }
};


//双指针法
若 nums[curr] = 0 ：交换第 curr个 和 第p0个 元素，并将指针都向右移。

若 nums[curr] = 2 ：交换第 curr个和第 p2个元素，并将 p2指针左移 。

若 nums[curr] = 1 ：将指针curr右移。

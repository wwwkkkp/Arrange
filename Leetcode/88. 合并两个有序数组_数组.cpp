
//88. 合并两个有序数组
给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。

 

说明:

初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
 

示例:

输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

输出: [1,2,2,3,5,6]

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int>v(nums1.begin(),nums1.begin()+m);
        int i=0,j=0,k=0;
        while(i<m&&j<n){
            if(v[i]>nums2[j])nums1[k++]=nums2[j++];
            else nums1[k++]=v[i++];
        }
        while(i<m)nums1[k++]=v[i++];
        while(j<n)nums1[k++]=nums2[j++];
        return ;
    }
};
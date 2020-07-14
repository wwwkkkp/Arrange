/*面试题51. 数组中的逆序对

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

示例 1:

输入: [7,5,6,4]
输出: 5
 

限制：

0 <= 数组长度 <= 50000
*/

//归并排序 ，注意：这个程序在LeetCode上可以通过，但是在牛客上不行，在牛客上把 int count 改成 long count 就可以了

class Solution {
public:
    int count=0;//牛客 long count=0;  //原因：可能是判定程序编译器不一样，一般来说 长度方面 long>=int，但是一般都是4byte,32位	
    void Merge(vector<int>& nums,vector<int>& nums1,int L,int C,int R){
        int i=L,j=C,k=L;
        while(i<C && j<=R){
            if(nums[i]<=nums[j]){
               nums1[k++]=nums[i++];
            }
            else {
                nums1[k++]=nums[j++];
                count+=C-i;   
            }
        }
        while(i<C){
            nums1[k++]=nums[i++];
        }
        while(j<=R){
            nums1[k++]=nums[j++];
        }  
        for(int p=R;p>=L;p--) //注意，这里只需要复制对应片段就行了
            nums[p]=nums1[p];
    }
    
    void Msort(vector<int>& nums,vector<int>& nums1,int L,int R){
        int center;
        if(L<R){
            center=L+(R-L)/2;
            Msort(nums,nums1,L,center);//左边排序
            Msort(nums,nums1,center+1,R);//右边排序
            Merge(nums,nums1,L,center+1,R);//左右排序
        }
    }
	
    int reversePairs(vector<int>& nums) {
        int n=nums.size();
        vector<int> nums1=nums;
        Msort(nums,nums1,0,n-1);
        return count;
    }
};
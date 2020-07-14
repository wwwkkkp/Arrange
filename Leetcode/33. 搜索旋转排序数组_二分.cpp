



//33. 搜索旋转排序数组
假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

你可以假设数组中不存在重复的元素。

你的算法时间复杂度必须是 O(log n) 级别。

示例 1:

输入: nums = [4,5,6,7,0,1,2], target = 0
输出: 4
示例 2:

输入: nums = [4,5,6,7,0,1,2], target = 3
输出: -1

//二分，当求某个数存不存在的时候，上取整和下取整是一样的，但是当求在哪个区间中的时候，就要分开讨论
class Solution {
public:
    int search(vector<int>& nums, int t) {
        int n=nums.size();
        if(!n)return -1;
        int i=0;
        while(i+1<n&&nums[i]<=nums[i+1])i++; //找出分界点
        int left=i+1,right=i+n;              //假定把分界前面的数都移动到最后去，那最小取到i+1，最大取到i+n
       
        while(left<right){
            int mid=left+right>>1;
            int k=0;
            if(mid>=n){k=1;mid-=n;}		//如果分界点超过了实际数组大小，就减去n，就是实际的中间点的位置
            if(nums[mid]>=t){
                right=mid;
                if(k)right+=n;			//前面减过n，后面就得加上n,保持一致
            }
            else{ 
                left=mid+1;
                if(k)left+=n;
            }
        }
        
        //cout<<right<<" "<<i<<endl;
        if(nums[right%n]==t)return right%n;
        return -1;
    }
};
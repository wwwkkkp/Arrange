
287. 寻找重复数
给定一个包含 n + 1 个整数的数组 nums，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。假设只有一个重复的整数，找出这个重复的数。

示例 1:

输入: [1,3,4,2,2]
输出: 2
示例 2:

输入: [3,1,3,4,2]
输出: 3

说明：
	不能更改原数组（假设数组是只读的）。
	只能使用额外的 O(1) 的空间。
	时间复杂度小于 O(n2) 。
	数组中只有一个重复的数字，但它可能不止重复出现一次。

//二分法：

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n=nums.size();
        int left=1,right=n,mid,cnt;
        while(left<right){
            mid=left+right>>1;
            cnt=0;
            for(int c:nums){ //比中间数小的数的数量大于比中间数大的数的数量，证明重复数在左边
                if(c<=mid)
                    cnt++;
            }
            if(cnt>mid)right=mid;
            else left=mid+1;
        }
        return left;
    }
};
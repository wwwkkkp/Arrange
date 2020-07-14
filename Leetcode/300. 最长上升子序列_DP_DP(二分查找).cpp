/* 300. 最长上升子序列

给定一个无序的整数数组，找到其中最长上升子序列的长度。

示例:

输入: [10,9,2,5,3,7,101,18]
输出: 4 
解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。
说明:

可能会有多种最长上升子序列的组合，你只需要输出对应的长度即可。
你算法的时间复杂度应该为 O(n2) 。

进阶: 你能将算法的时间复杂度降低到 O(n log n) 吗?

*/


//常规思路，时间复杂度是 O(n2) ，动态规划
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int s=nums.size();
        if(s<=1) return s;
        vector<int>Vec(s+1,1);
        Vec[0]=0;
        Vec[1]=1;
        int maxn=1;
        for(int i=1;i<s+1;i++){
            for(int j=1;j<i;j++)
                if(nums[i-1]>nums[j-1]){
                    Vec[i]=max(Vec[i],Vec[j]+1);
                }
            maxn=max(maxn,Vec[i]);  
        }
        return maxn;
    }
};

//DP+二分查找 时间复杂度 O(n log n) 
//具体过程见 https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/dong-tai-gui-hua-er-fen-cha-zhao-tan-xin-suan-fa-p/

class Solution {
public:
    int lengthOfLIS(vector<int> &nums) {
        int len = nums.size();
        if (len < 2) {
            return len;
        }

        vector<int> tail;
        tail.push_back(nums[0]);  //tail中储存的数是每个长度中结尾最小的数，见下面的例子
        // tail 结尾的那个索引
        int end = 0;

        for (int i = 1; i < len; ++i) {
            if (nums[i] > tail[end]) {
                tail.push_back(nums[i]);
                end++;
            } else {
                int left = 0;
                int right = end;
                while (left < right) {  //二分法查找相应的位置
                    int mid = (left + right) >> 1;
                    if (tail[mid] < nums[i]) {
                        left = mid + 1;
                    } else {
                        right = mid;
                    }
                }
                tail[left] = nums[i];
            }
        }
        return end + 1;
    }
};


原数组：

1 3 6 7 9 4 10 5 6

tail数组 ：  //tail中每一个数都是这个数组子序列为改长度的最小结尾，如tail[4]=6,意思是子序列长度为 5 的时候，结尾最小的数字是6

1 3 4 5 6 10


//6.17版本
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size();
        if(!n)return 0;
        
        vector<int>v;
        v.push_back(nums[0]);
        for(int i=1;i<n;i++){
            if(nums[i]>v.back())v.push_back(nums[i]);
            else{
                int l=0,r=v.size()-1;
                while(l<r){
                    int mid=(l+r)>>1;
                    if(v[mid]>=nums[i])r=mid;
                    else l=mid+1;
                }
                v[r]=nums[i];
            }
        }
        return v.size();
    }   
};

//55. 跳跃游戏
给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个位置。

示例 1:

输入: [2,3,1,1,4]
输出: true
解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。
示例 2:

输入: [3,2,1,0,4]
输出: false
解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。

//数组
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n=nums.size();
        if(!n)return 0;
        if(!nums[0]&&n>1)return 0;
        for(int i=0;i<n-1;){
            int res=0,k=0;
            for(int j=1;j<=nums[i];j++){
                if(i+j>=n-1)return true;     //首先要确定能否到达终点的条件，如果当前位置+可移动的位置==n-1,那就是可以的
                if(i+j<n&&res<nums[i+j]+i+j){
                    res=nums[i+j]+i+j;  //res是当前位置的下一个窗口能到达的最远位置，[2,3,1,1,4]，i=0时，下一个位置的最远位置就是在k=1的时候，res=4
                    k=i+j;    			//到达最远的起点，
                }         
            }
            if(res==k)return false;  //不能到达的条件，就是当前位置的下一个位置所能到达的最远位置等于下一个位置的起点，那就不能到达终点了
            i=k;
        }
        return true;
    }
};


class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int rightmost = 0;  //记录到目前为止能到达的最远位置
        for (int i = 0; i < n; ++i) {
            if (i <= rightmost) {
                rightmost = max(rightmost, i + nums[i]);
                if (rightmost >= n - 1) {
                    return true;
                }
            }
        }
        return false; //[3,2,1,0,4]为例，rightmost最大值只能到3，但是n-1是4，所以无法到达，
    }
};


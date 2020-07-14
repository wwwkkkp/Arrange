
//416. 分割等和子集

给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

注意:

每个数组中的元素不会超过 100
数组的大小不会超过 200
示例 1:

输入: [1, 5, 11, 5]

输出: true

解释: 数组可以分割成 [1, 5, 5] 和 [11].
 

示例 2:

输入: [1, 2, 3, 5]

输出: false

解释: 数组不能分割成两个元素和相等的子集.





//0-1背包问题 注意剪枝技巧
class Solution {
public:
    
    int sum;
    bool canPartition(vector<int>& nums) {
        sort(nums.rbegin(),nums.rend()); //要从最大的开始选择，剪枝技巧

        for(int i=0;i<nums.size();i++)
            sum+=nums[i];
        if(sum%2)return false;
        if(nums[0]>sum/2)return false; //最大的数超过了sum/2，那就不可能形成等和
        return dp(nums,0,sum/2);
    }
    bool dp(vector<int>& nums,int i,int s){
        if(s==0)
            return true;
        else if(s<0)
            return false;
        if(i==nums.size())
            return false;
        return dp(nums,i+1,s-nums[i])||dp(nums,i+1,s);//选或者不选
    }
};

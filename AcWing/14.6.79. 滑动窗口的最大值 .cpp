
//14.6.79. 滑动窗口的最大值 

给定一个数组和滑动窗口的大小，请找出所有滑动窗口里的最大值。
例如，如果输入数组[2, 3, 4, 2, 6, 2, 5, 1]及滑动窗口的大小3,那么一共存在6个滑动窗口，它们的最大值分别为[4, 4, 6, 6, 6, 5]。
注意：
数据保证k大于0，且k小于等于数组长度。
样例
输入：[2, 3, 4, 2, 6, 2, 5, 1] , k=3

输出: [4, 4, 6, 6, 6, 5]


//单调栈问题  单调递增是留下最小的，单调递减是留下最大的

class Solution {
public:
    vector<int> maxInWindows(vector<int>& nums, int k) {
        vector<int> v;
        deque<int>q;
        for(int i=0;i<nums.size();i++){
            while(q.size()&&q[0]<i-k+1)q.pop_front();//因为是寻找最近k个数的最大值，那如果当前栈中最大值的位置超过了k，那就要删除
            if(!q.size())q.push_back(i);  //栈中没有值，就添加
            else{
                while(q.size()&&nums[q.back()]<=nums[i]){  //如果当前的栈中最后一个数比新的数小，就删除这个数，最后添加新的数
                    q.pop_back();
                }
                q.push_back(i);
            }
            if(i>=k-1){
               v.push_back(nums[q.front()]); //当前栈中的第一个数，就是最大值
            } 
        }
        return v;
    }
};
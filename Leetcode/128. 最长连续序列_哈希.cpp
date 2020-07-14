


//128. 最长连续序列
给定一个未排序的整数数组，找出最长连续序列的长度。

要求算法的时间复杂度为 O(n)。

示例:

输入: [100, 4, 200, 1, 3, 2]
输出: 4
解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。



//哈希
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n=nums.size();
        if(!n)return 0;
        
        unordered_set<int>us;
        for(auto c:nums)us.insert(c);  //先全部放进哈希表中
        
        int res=0;
        for(auto c:nums){
            int k=1;
            if(!us.count(c-1)){		//因为数组中的数是一串一串的，找出每一串的最左边的数，
                k=1;
                while(us.count(c+1)){  //然后向右遍历，
                    c++;
                    k++;
                }
                res=max(res,k);  //更新最长串
            }
        }
        return res;
    }
};
/*5294. 你能从盒子里获得的最大糖果数
给你一个整数数组 nums 和一个正整数 k，请你判断是否可以把这个数组划分成一些由 k 个连续数字组成的集合。
如果可以，请返回 True；否则，返回 False。

 

示例 1：

输入：nums = [1,2,3,3,4,4,5,6], k = 4
输出：true
解释：数组可以分成 [1,2,3,4] 和 [3,4,5,6]。
示例 2：

输入：nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
输出：true
解释：数组可以分成 [1,2,3] , [2,3,4] , [3,4,5] 和 [9,10,11]。
示例 3：

输入：nums = [3,3,2,2,1,1], k = 3
输出：true
示例 4：

输入：nums = [1,2,3,4], k = 3
输出：false
解释：数组不能分成几个大小为 3 的子数组。
 

提示：

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= k <= nums.length

*/

//unordered_map,总思想是先统计数的数量，然后实行减法，

class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        unordered_map<int,int>cnts;
        for(auto c:nums)
            cnts[c]++;
        while(!cnts.empty()){  //while循环一轮，减去一组相连的数；
            int start=cnts.begin()->first; //从最小的数开始做相连数组的头部
            for(int i=start;i<start+k;i++){
                if(cnts.find(i)==cnts.end()) //如果找不到这个数，就是错误的
                    return false;
                cnts[i]--;
            }
            for(unordered_map<int,int>::iterator it=cnts.begin();it!=cnts.end();it++){  //如果某个数被减到零后，就删除
                if(it->second==0)
                    cnts.erase(it->first);
            }
        }
        return true;
    }
};
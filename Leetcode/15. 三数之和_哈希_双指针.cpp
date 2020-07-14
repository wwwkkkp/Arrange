

//15. 三数之和
给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

 

示例：

给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]


//6.12版本
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n=nums.size();
        if(n<3)return {};
        
        set<vector<int>>sv;
        unordered_map<int,int>um;
        
        sort(nums.begin(),nums.end());
        um[nums[0]]++;
        um[nums[1]]++;
        for(int i=2;i<n;i++){      
            int k=0-nums[i];
            for(auto c:um){			//用哈希表找这两个数
                int p=k-c.first;
                if((p==c.first&&c.second>1)||(p!=c.first&&um.find(p)!=um.end())){
                    vector<int>v={nums[i],p,c.first};
                    sort(v.begin(),v.end());
                    sv.insert(v);
                }      
            }
            um[nums[i]]++;
        }

        vector<vector<int>>v1(sv.begin(),sv.end());
        return v1;
        
        
    }
};


//双指针法

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> res;
        sort(nums.begin(), nums.end());
        if (nums.empty() || nums.back() < 0 || nums.front() > 0) return {};
        for (int k = 0; k < nums.size(); ++k) {
            if (nums[k] > 0) break;
            int target = 0 - nums[k];				//先找出最小的那个数
            int i = k + 1, j = nums.size() - 1;		//然后在比它大的数中用双指针找两个数
            while (i < j) {
                if (nums[i] + nums[j] == target) {
                    res.insert({nums[k], nums[i], nums[j]});
                    while (i < j && nums[i] == nums[i + 1]) ++i;
                    while (i < j && nums[j] == nums[j - 1]) --j;
                    ++i; --j;
                } else if (nums[i] + nums[j] < target) ++i;
                else --j;
            }
        }
        return vector<vector<int>>(res.begin(), res.end());
    }
};
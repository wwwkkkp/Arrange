/* //组合总和   //当拿到一个题的是哦户，要先看能不能转化成更小的相似问题

给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取。

说明：


	所有数字（包括 target）都是正整数。
	解集不能包含重复的组合。 


示例 1:

输入: candidates = [2,3,6,7], target = 7,
所求解集为:
[
  [7],
  [2,2,3]
]


示例 2:

输入: candidates = [2,3,5], target = 8,
所求解集为:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]
*/


//回溯
class Solution {
public:
    vector<vector<int>> out;
    vector<int>tmp;
    void results(int idx,vector<int>& candidates, int target){
        if(target==0)
        {   out.push_back(tmp);
            return;
        }
        if(target<0)
            return;
        for(int i=idx;i<candidates.size();i++){
            tmp.push_back(candidates[i]);
            results(i,candidates,target-candidates[i]);
            tmp.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        results(0,candidates,target);
        return out;
    }
};


//这道题应该还可以用BFS来做；
vector<vector<int>> out;
queue<vector<int>>q;
for(auto k:candidates){
	把k插入到q;  //这里求得是 依次以k为开头的满足条件的数组
	while(!q.empty){
		a=取出q中元素；
		for(auto k:candidates){
			当target-k>0
				加入a;
			target-k==0
				加入out;
		}
		
	}
}
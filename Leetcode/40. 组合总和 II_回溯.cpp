/*40. 组合总和 II
给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

说明：

所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。 
示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
示例 2:

输入: candidates = [2,5,2,1,2], target = 5,
所求解集为:
[
  [1,2,2],
  [5]
]

*/

//回溯
class Solution {
public:
    set<vector<int>> Vec;
    void DFS(vector<int>& candidates, int target,int s,int sum,vector<int>& mus){
        if(s==candidates.size()) return;
        if(sum==target){
            Vec.insert(mus);
            return;
        }
        for(int i=s+1;i<candidates.size();i++){
            if(sum+candidates[i]<=target){
                mus.push_back(candidates[i]);
                DFS(candidates,target,i,sum+candidates[i],mus);
            }
            else
                break;
            mus.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int>mus;
        sort(candidates.begin(),candidates.end());
        DFS(candidates,target,-1,0,mus);
        vector<vector<int>> out;
        for(set<vector<int>>::iterator it=Vec.begin();it!=Vec.end();it++){
            out.push_back(*it);
        }
        return out;
    }
};
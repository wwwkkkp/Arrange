
1014. 最佳观光组合
给定正整数数组 A，A[i] 表示第 i 个观光景点的评分，并且两个景点 i 和 j 之间的距离为 j - i。

一对景点（i < j）组成的观光组合的得分为（A[i] + A[j] + i - j）：景点的评分之和减去它们两者之间的距离。

返回一对观光景点能取得的最高分。

 

示例：

输入：[8,1,5,2,6]
输出：11
解释：i = 0, j = 2, A[i] + A[j] + i - j = 8 + 5 + 0 - 2 = 11
 

提示：

2 <= A.length <= 50000
1 <= A[i] <= 1000

//当发现时间复杂度超时，但是又无法使用二分，DP等方法求最优解的方法的时候，最好仔细看看递推公式，看能不能降维

class Solution {
public:

    int maxScoreSightseeingPair(vector<int>& A) {
        int n=A.size();
        if(!n)return 0;
        
        int res=0,mx=A[0]+0;
        for(int j=1;j<n;j++){
            res=max(res,mx+A[j]-j);		//更新结果
            mx=max(mx,A[j]+j);			//更新A[i]+i
        }
        
        return res;
    }
};
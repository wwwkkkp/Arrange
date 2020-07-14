/*5295. 和为零的N个唯一整数

给你一个整数 n，请你返回 任意 一个由 n 个 各不相同 的整数组成的数组，并且这 n 个数相加和为 0 。

示例 1：

输入：n = 5
输出：[-7,-1,1,3,4]
解释：这些数组也是正确的 [-5,-1,1,2,3]，[-3,-1,2,-2,4]。
示例 2：

输入：n = 3
输出：[-1,0,1]
示例 3：

输入：n = 1
输出：[0]

*/

class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> vec;
        if(n%2)
            vec.push_back(0);
        n--;
        int j=1;
        for(int i=n;i>0;i-=2){
            vec.push_back(j);
            vec.push_back(-1*j);
            j++;
        }
        sort(vec.begin(),vec.end());
        return vec;
    }
};
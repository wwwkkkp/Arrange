/* 5304. 子数组异或查询
有一个正整数数组 arr，现给你一个对应的查询数组 queries，其中 queries[i] = [Li, Ri]。

对于每个查询 i，请你计算从 Li 到 Ri 的 XOR 值（即 arr[Li] xor arr[Li+1] xor ... xor arr[Ri]）作为本次查询的结果。

并返回一个包含给定查询 queries 所有结果的数组。

示例 1：

输入：arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
输出：[2,7,14,8] 
解释：
数组中元素的二进制表示形式是：
1 = 0001 
3 = 0011 
4 = 0100 
8 = 1000 
查询的 XOR 值为：
[0,1] = 1 xor 3 = 2 
[1,2] = 3 xor 4 = 7 
[0,3] = 1 xor 3 xor 4 xor 8 = 14 
[3,3] = 8

示例 2：

输入：arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
输出：[8,0,4,4]

提示：


	1 <= arr.length <= 3 * 10^4
	1 <= arr[i] <= 10^9
	1 <= queries.length <= 3 * 10^4
	queries[i].length == 2
	0 <= queries[i][0] <= queries[i][1] < arr.length

*/


class Solution {
public:
    int orq(vector<int>& arr,int L,int R){ //二分
        if(L==R)
            return arr[L];
        if(R-L==1)
            return arr[L]^arr[R];
        else
            return orq(arr,L,L+(R-L)/2)^orq(arr,L+(R-L)/2+1,R);
    }
    
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& q) {
        int n=arr.size();
        int n1=q.size();
        vector<int> vec(n1,0);
        map<vector<int>,int>up;
        for(int i=0;i<n1;i++){
            int a;
            if(up.find(q[i])==up.end()){
                a=orq(arr,q[i][0],q[i][1]);
                up.insert(make_pair(q[i],a));
            }else{
                a=up[q[i]];
            }
            vec[i]=a;
            
        }
        return vec;
    }
};


//上述办法有点笨，其实可以将所有异或算出来 通过范围直接得出结果
class Solution {
 public:
  vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
    int dp[arr.size()];
    dp[0] = arr[0];

    for (int i = 1; i < arr.size(); ++i) { //0到i每一位的异或运算
      dp[i] = dp[i - 1] ^ arr[i];
    }

    vector<int> res;
    for (int i = 0; i < queries.size(); ++i) {
      int l = queries[i][0];
      int r = queries[i][1];
      int num = l == 0 ? dp[r] : dp[r] ^ dp[l - 1];//异或的异或相当于没有异或
      res.push_back(num);
    }
    return res;
  }
};

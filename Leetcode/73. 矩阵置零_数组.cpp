


//73. 矩阵置零
给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。请使用原地算法。

示例 1:

输入: 
[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
输出: 
[
  [1,0,1],
  [0,0,0],
  [1,0,1]
]
示例 2:

输入: 
[
  [0,1,2,0],
  [3,4,5,2],
  [1,3,1,5]
]
输出: 
[
  [0,0,0,0],
  [0,4,5,0],
  [0,3,1,0]
]
进阶:

一个直接的解决方案是使用  O(mn) 的额外空间，但这并不是一个好的解决方案。
一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案。
你能想出一个常数空间的解决方案吗？


class Solution {
public:
    void setZeroes(vector<vector<int>>& v) {
        int n=v.size();
        if(!n)return ;
        queue<pair<int,int>>q;
        int m=v[0].size();
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(v[i][j]==0)q.push({i,j});
            }
        }
        while(q.size()){
            auto w=q.front();
            q.pop();
            int a=w.first;
            int b=w.second;
            
            for(int i=0;i<m;i++)v[a][i]=0;
            for(int i=0;i<n;i++)v[i][b]=0;
        }
    }
};
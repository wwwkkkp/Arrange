

//74. 搜索二维矩阵
编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：

每行中的整数从左到右按升序排列。
每行的第一个整数大于前一行的最后一个整数。
示例 1:

输入:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 3
输出: true
示例 2:

输入:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 13
输出: false


//二分
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& v, int t) {
        int n=v.size();
        if(!n)return false;
        int m=v[0].size();
        if(!m)return false;
        if(t<v[0][0]||t>v[n-1][m-1])return false;
        int left=0,right=n-1;
        while(left<right){
            int mid=left+right+1 >> 1;   //这里两个都是下取整
            if(v[mid][0]>t)right=mid-1;
            else left=mid;
        }
        if(t>v[right][m-1]){return false;}
        int l=0,r=m-1;
        while(l<r){						//这个可以是下取整，但是要把判断改成v[right][mid]>=t
            int mid=l+r+1 >> 1;
            if(v[right][mid]>t){r=mid-1;}
            else {l=mid;}
        }
        if(v[right][r]==t)return true;  //这里判断是否相等要在外面判断，不要再while中判断
        return false;
    }
};
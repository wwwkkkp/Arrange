

378. 有序矩阵中第K小的元素
给定一个 n x n 矩阵，其中每行和每列元素均按升序排序，找到矩阵中第 k 小的元素。
请注意，它是排序后的第 k 小元素，而不是第 k 个不同的元素。

 

示例：

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

返回 13。
 

提示：
你可以假设 k 的值永远是有效的，1 ≤ k ≤ n2 。

class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        int n=mat.size();
        
        long long l=-200000000000,r=200000000000;
        while(l<r){
            long long  mid=l+r>>1;
            if(work(mat,mid)>=k)r=mid;
            else l=mid+1;
        }
        return r;
    }
    int work(vector<vector<int>>&v,long long m){
        int n=v.size();
        int res=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(v[i][j]<=m)
                    res++;
            }
        }
        return res;
    }
};
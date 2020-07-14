
120. 三角形最小路径和
给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。

相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。

 

例如，给定三角形：

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

 

说明：

如果你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题，那么你的算法会很加分。


//杨辉三角逆推比较好，空间复杂度为O(n)
const int N=1010;
class Solution {
public:
    int minimumTotal(vector<vector<int>>& t) {
        int n=t.size();
        if(!n)return 0;
    
        int f[N];
        for(int i=0;i<n;i++){
            f[i]=t[n-1][i];
        }
        for(int i=n-2;i>=0;i--){
            for(int j=0;j<=i;j++){
                f[j]=min(f[j]+t[i][j],f[j+1]+t[i][j]);
            }
        }
        return f[0];
    }
};




//正推
const int N=1010;
class Solution {
public:
    int minimumTotal(vector<vector<int>>& t) {
        int n=t.size();
        if(!n)return 0;

        
        int f[N][N];
        memset(f,0x3f3f3f,sizeof f);
        
        f[0][0]=t[0][0];
        for(int i=0;i<n-1;i++){
            for(int j=0;j<=i;j++){
                f[i+1][j]=min(f[i+1][j],f[i][j]+t[i+1][j]);
                f[i+1][j+1]=min(f[i+1][j+1],f[i][j]+t[i+1][j+1]);
            }
        }
        int res=0x3f3f3f;
        for(int i=0;i<=n;i++){
            res=min(res,f[n-1][i]);
        }
        return res;
    }
};
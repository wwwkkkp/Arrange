


//85. 最大矩形
给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。

示例:

输入:
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
输出: 6



const int N=1000;
class Solution {
public:
    int f[N][N];
    int maximalRectangle(vector<vector<char>>& v) {
        int n=v.size();
        if(!n)return 0;
        int m=v[0].size();
        if(!m)return 0;
        memset(f,0,sizeof f);
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(v[i-1][j-1]=='1')f[i][j]=f[i-1][j]+1;
                else f[i][j]=0;
            }
        }
        int res=0;
        for(int i=1;i<=n;i++){
            res=max(res,work(i,m));
        }
        return res;
    }
    int work(int a,int m){
        int left[N],right[N];
        int q[1000];
        int tt=0;
        q[tt]=0;
        for(int i=1;i<=m;i++){
            //cout<<f[a][i]<<" ";
            while(tt>=1&&f[a][q[tt]]>=f[a][i])tt--;
            left[i]=q[tt];
            q[++tt]=i;
        }
        //cout<<endl;
        tt=0;
        q[tt]=m+1;
        for(int i=m;i>=1;i--){
            while(tt>=1&&f[a][q[tt]]>=f[a][i])tt--;
            right[i]=q[tt];
            q[++tt]=i;
        }    
        int res=0;
        for(int i=1;i<=m;i++){
            //cout<<left[i]<<" "<<right[i]<<endl;
            res=max(res,(right[i]-left[i]-1)*f[a][i]);
        }
        return res;
    }
    
};
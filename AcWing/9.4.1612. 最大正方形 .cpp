//9.4.1612. 最大正方形 

在一个由 0和 1组成的 n×m的二维矩阵内，找到只包含 1的最大正方形，并返回其面积。

输入格式
第一行包含两个整数 n,m，表示二维矩阵大小。
接下来 n行，每行包含 m个整数，每个整数只可能是 0或 1。

输出格式
输出只包含1的最大正方形的面积。
数据范围
1≤n,m≤1000
输入样例：
4 5
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
输出样例：
4


#include<iostream>

using namespace std;
const int N=1010;

int n,m;
int a[N][N];
int f[N][N];//以i,j为右下结点的最大正方形

int main(){

    cin>>n>>m;
    int res=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            if(a[i][j]==1)
                f[i][j]=min(f[i-1][j],min(f[i-1][j-1],f[i][j-1]))+1;//正方形等于左边，上边，左上边的最小值+1
            res=max(res,f[i][j]);
        }
    }
    cout<<res*res<<endl;
    return 0;
}

//注意：这个方法只适用于正方形，不适用于矩形，矩形要用单调栈的方法去做。

//单调栈做法，适用于正方形，只是面积求的方法要变一下
#include<iostream>
#include<algorithm>

using namespace std;
const int N=1010;

int n,m;
int a[N][N];
int f[N][N];
int q[N],l[N],r[N];

int dfs(int h[]){
    h[0]=h[m+1]=-1;
    
    int tt=0;
    q[0]=0;
    for(int i=1;i<=m;i++){
        while(h[q[tt]]>=h[i])tt--;
        l[i]=q[tt];
        q[++tt]=i;
    }
    tt=0;
    q[0]=m+1;
    for(int i=m;i>=1;i--){
        while(h[q[tt]]>=h[i])tt--;
        r[i]=q[tt];
        q[++tt]=i;
    }
    int res=0;
    for(int i=1;i<=m;i++){
        res=max(res,min(h[i],r[i]-l[i]-1));//求得是边长
    }
    return res;
}
int main(){

    cin>>n>>m;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            if(a[i][j]==1) f[i][j]=f[i-1][j]+1;
            else f[i][j]=0;
        }
    }
    int res=0;
    for(int i=1;i<=n;i++)
        res=max(res,dfs(f[i]));
    cout<<res*res<<endl;
    return 0;
}



//15.2.1302. 矩阵 A × B 

矩阵乘法

输入格式
第一行两个数 n,m；
接下来 n行 m列描述一个矩阵A；
接下来一行输入 p；
接下来 m行 p列描述一个矩阵 B。

输出格式
输出矩阵 A与矩阵 B相乘所得的矩阵 C。

数据范围
1≤n,m,p≤100
−10000≤aij,bij≤10000

输入样例：
2 3
1 2 3
3 2 1
2 
1 1
2 2
3 3
输出样例：
14 14
10 10
样例解释
[
14=1×1+2×2+3×3
10=3×1+2×2+1×3
14=1×1+2×2+3×3
10=3×1+2×2+1×3
]



//就是按照矩阵乘法写

#include<iostream>

using namespace std;

const int N=110;

int n,m,p;

int a[N][N],b[N][N],c[N][N];

int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>a[i][j];
    cin>>p;
    for(int i=0;i<m;i++)
        for(int j=0;j<p;j++)
            cin>>b[i][j];
    
    for(int i=0;i<n;i++)
        for(int j=0;j<p;j++)
            for(int k=0;k<m;k++){
                c[i][j]+=a[i][k]*b[k][j];
            }
    for(int i=0;i<n;i++){
        for(int j=0;j<p;j++){
            cout<<c[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
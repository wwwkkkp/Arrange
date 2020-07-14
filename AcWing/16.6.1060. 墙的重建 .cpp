

//16.6.1060. 墙的重建 

一段城墙，连续的称为一段，有不连续的点就是两段，    如1 1 1 2 2 2 就是两段，1个分界点，求将一段数变的有k个分界点的最小修改次数，
如：1 1 2 3, 想变得有1个分界点，也就是2段的最小改变步骤就是将3变成2，数组变成1 1 2 2，即可


输入格式
第一行包含整数T，表示共有 T组测试数据。每组测试数据共两行，第一行包含整数N和 k。
第二行包含 N个整数，其中第 i个整数表示第 i部分墙体的高度 Ai。

输出格式
每组数据输出一个结果，每个结果占一行。
结果表示为“Case #x: y”，其中x是组别编号（从1开始），y为最少需要重建的墙面数量。
数据范围
1≤T≤100
1≤Ai≤1000
0≤k≤N
2≤N≤100
输入样例：
4
8 2
300 100 300 300 200 100 800 500
5 3
100 100 100 100 3
7 3
10 20 40 10 10 30 30
10 2
30 30 60 60 90 90 60 60 30 30
输出样例：
Case #1: 3
Case #2: 0
Case #3: 1
Case #4: 2





#include<iostream>
#include<cstring>

using namespace std;

const int N=110,M=1010;

int n,k,t;
int a[N],b[M]; 
int f[N][N],g[N][N];   //f:前i个数分成j段最少改变步骤，g:i到j变成一段所需要的最少次数，

int main(){
    cin>>t;
    for(int c=1;c<=t;c++){
        cin>>n>>k;
        for(int i=1;i<=n;i++)cin>>a[i];
        

        for(int i=1;i<=n;i++){
            memset(b,0,sizeof b);
            int res=0;
            for(int j=i;j<=n;j++){
                b[a[j]]++;
                res=max(res,b[a[j]]);//众数个数
                g[i][j]=j-i+1-res;
            }
        }
        
        memset(f,0x3f3f3f,sizeof f);
        memset(f[0],0,sizeof f[0]);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=k+1;j++){
                for(int k=0;k<i;k++){//最后一段是从k+1到i的时候需要改变的最少次数，
                    f[i][j]=min(f[i][j],f[k][j-1]+g[k+1][i]);
                }
            }
        }
        
        printf("Case #%d: %d\n",c,f[n][k+1]);
    }
    return 0;
}
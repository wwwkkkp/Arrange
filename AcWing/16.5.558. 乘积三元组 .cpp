
//16.5.558. 乘积三元组 

给定N个整数A1,A2,…,AN，计算能够使得下列条件至少一条得到满足的三元组(x,y,z)有多少个：
Ax=Ay×Az
Ay=Ax×Az
Az=Ax×Ay
要求：x<y<z
输入格式
第一行包含整数T，表示共有T组测试数据。
每组数据占两行，第一行包含整数N。
第二行包含N个整数A1,A2,…,AN。
输出格式
每组数据输出一个结果，每个结果占一行。
结果表示为“Case #x: y”，其中x为组别编号（从1开始），y为满足条件的三元组的数量。
数据范围

1≤T≤30
0≤Ai≤2*10^5
3≤N≤7000

输入样例：
4
6
5 2 4 6 3 1
6
2 4 8 16 32 64
4
1 1 1 1
3
200000 200000 200000
输出样例：
Case #1: 1
Case #2: 6
Case #3: 4
Case #4: 0


//枚举，就是寻找一组数，排好序以后，两个下标小的数相乘=下标大的数，a[i]*a[j]=a[z],i<j<z;遍历i,j,寻找z，具体做法有技巧
#include<iostream>
#include<algorithm>
#include<cstring>
#include<unordered_map>

using namespace std;

const int N=7010,M=200010;
typedef long long ll;

int n,t;
int a[N],b[M];

int main(){
    cin>>t;
    for(int c=1;c<=t;c++){
        cin>>n;

        int zero=0;
        for(int i=0;i<n;i++){
            cin>>a[i];
            if(!a[i])zero++;
        }
        sort(a,a+n);
        memset(b,0,sizeof b);//这里有个技巧，b是某一个数在数组中出现的次数，这个数是在枚举中加入的
        ll res=0;
        for(int i=n-1;i>=0&&a[i]>0;i--){  //枚举数组中非零的数
            for(int j=i-1;j>=0;j--){	  //j<i，寻找下标比i大的数
                if(1ll*a[i]*a[j]<M)		//M是数组中的最大值，乘积不能超过这个数
                    res+=b[a[i]*a[j]];    //第一次循环，这个都是0
            }
            b[a[i]]++;				///精髓，改变i之前，把i指向的数，添加到b中，下次寻找的时候，如果后面有乘积等于这个数，res就加上，最好的例子是第三个例子
        }
        int nzero=n-zero;  //乘数等于0的情况
        res+=1ll*nzero*(zero*(zero-1)/2);
        res+=1ll*zero*(zero-1)*(zero-2)/6;
        
        printf("Case #%d: %lld\n",c,res);
    }
    return 0;
}
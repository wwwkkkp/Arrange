


//16.4.1108. 读书 

Supervin是一名图书管理员，有一本共 N页，页码编号为 1~ N的古书由他管理。
由于书太破旧了，因此其中的 M页处于残缺状态，这 M页的编号分别是 P1,P2,…,PM。
现在，有 Q名十分懒惰的读者对阅读这本书产生了兴趣。因为他们很懒惰，因此他们并不打算将书整本阅读。
现在已知第 i名读者将会阅读所有页面编号能被 Ri整除且没有残缺的书页。Supervin想知道所有读者的实际阅读页数相加的和为多少。

输入格式
第一行包含整数 T，表示共有 T组测试数据。
每组数据占三行，其中第一行包含三个整数N,M,Q，分别表示书的总页数，残缺页数以及读者数。
第二行包含 M个整数，其中第 i个数为 Pi。
第三行包含 Q个整数，其中第 i个数为 Ri。

输出格式
每组数据输出一个结果，每个结果占一行。
结果表示为“Case #x: y”，其中x是组别编号（从1开始），y为所有读者的实际阅读页数相加的和。
数据范围
1≤T≤100
1≤P1<P2<…<PM≤N
1≤Ri≤N
1≤M≤N≤105
1≤Q≤105
输入样例：
3
11 1 2
8
2 3
11 11 11
1 2 3 4 5 6 7 8 9 10 11
1 2 3 4 5 6 7 8 9 10 11
1000 6 1
4 8 15 16 23 42
1
输出样例：
Case #1: 7
Case #2: 0
Case #3: 994



//枚举
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

const int N=100010;

int n,m,t,q;
int a[N];


int main(){
    cin>>t;
    for(int c=1;c<=t;c++){
        cin>>n>>m>>q;
        memset(a,0,sizeof a);
        vector<int>v;
        int x;
        for(int i=0;i<m;i++){
            cin>>x;
            a[x]=1;
        }
        
        for(int i=0;i<q;i++){
            cin>>x;
            v.push_back(x);
        }
        int res=0;
        for(int i=0;i<v.size();i++)//每一个阅读的人
            for(int j=v[i];j<=n;j+=v[i])  //要读哪些页
                if(!a[j])    //这些页有没有
                    res++;

        }
        printf("Case #%d: %d\n",c,res);
    }
    return 0;
}



//下面这个程序和上面的程序时间上的差别主要是res++和res+=r[i],如果n个人的的倍数都是1，那下面的只需要算一次，上面的要算n次，上面不能用哈希表存次数，时间消耗更高，

//这个时间复杂度低一些
#include <iostream>
#include <cstring>

using namespace std;

typedef long long LL;

const int N = 100010;

int n, m, q;
int p[N], r[N];

int main()
{
    int T;
    scanf("%d", &T);

    for (int cases = 1; cases <= T; cases ++ )
    {
        scanf("%d%d%d", &n, &m, &q);

        memset(p, 0, sizeof p);
        memset(r, 0, sizeof r);

        for (int i = 0; i < m; i ++ )
        {
            int x;
            scanf("%d", &x);
            p[x] = 1;
        }

        for (int i = 0; i < q; i ++ )
        {
            int x;
            scanf("%d", &x);
            r[x] ++ ;  //以x为倍数的人
        }

        LL res = 0;
        for (int i = 1; i <= n; i ++ )  //每一页
            for (int j = i; j <= n; j += i)  //以第i页为开始的人
                if (!p[j])  //如果这一页不缺
                    res += r[i];

        printf("Case #%d: %lld\n", cases, res);
    }

    return 0;
}

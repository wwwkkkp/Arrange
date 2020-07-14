
//12.1.1051. 最大的和 

对于给定的整数序列A={a1,a2,…,an}，找出两个不重合连续子段，使得两子段中所有数字的和最大。
我们如下定义函数 
d(A)=max1≤s1≤t1<s2≤t2≤n{∑i=s1t1ai+∑j=s2t2aj}
我们的目标就是求出d(A)。

输入格式
第一行是一个整数 T，代表一共有多少组数据。
接下来是 T组数据。
每组数据的第一行是一个整数，代表数据个数据 n，第二行是 n个整数 a1,a2,…,an。

输出格式
每组数据输出一个整数，占一行，就是 d(A)的值。
数据范围
1≤T≤30
2≤n≤50000
|ai|≤10000
输入样例：
1
10
1 -1 2 2 3 -3 4 -4 5 -5

输出样例：
13

样例解释
在样例中，我们取{2,2,3,-3,4}和{5}两个子段，即可得到答案。

//和3.1. 1056. 股票买卖 III一样，但是略有差别
#include<iostream>
#include<algorithm>

using namespace std;

const int N=50010,M=-10010;
int t,n;
int a[N];
int le[N],ri[N];

int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        le[0]=ri[n+1]=M;
        int res=0;
        for(int i=1;i<=n;i++){
            res=max(a[i],res+a[i]); //注意：res要先更新，res求的是以i结尾的最大和子串
            le[i]=max(le[i-1],res);//从0-i为止的最大和子串
            
        }
        res=0;
        for(int i=n;i>0;i--){
            res=max(a[i],res+a[i]); //注意：res要先更新，res求的是以i开始的最大和子串
            ri[i]=max(ri[i+1],res);//从i-n为止的最大和子串

        }

        res=M;
        for(int i=1;i<=n-1;i++)
            res=max(res,le[i]+ri[i+1]);//求以某一个结点作为分界点的时候的最大值，保证不能重合
        cout<<res<<endl;
    }
    return 0;
}

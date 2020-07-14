//5.3 122. 糖果传递 

有n个小朋友坐成一圈，每人有a[i]个糖果。
每人只能给左右两人传递糖果。
每人每次传递一个糖果代价为1。
求使所有人获得均等糖果的最小代价。
输入格式
第一行输入一个正整数n，表示小朋友的个数。
接下来n行，每行一个整数a[i]，表示第i个小朋友初始得到的糖果的颗数。
输出格式
输出一个整数，表示最小代价。
数据范围

1≤n≤1000000

数据保证一定有解。
输入样例：
4
1
2
5
4
输出样例：
4


#include<iostream>
#include<algorithm>

using namespace std;
const int N=1000010;

int n;
long long a[N],b[N],c[N];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=b[i-1]+a[i];
    }
    long long  cnt=b[n]/n;
    for(int i=2;i<=n;i++){
        c[i]=-1*(b[i]-b[1]-(i-1)*cnt);
        
    }
    sort(c+1,c+1+n);
    long long k=c[(n+1)/2];
    long long res=0;
    for(int i=1;i<=n;i++){
        res+=abs(c[i]-k);
    }
    cout<<res<<endl;
    return 0;
}

//这个问题和上一题差不多，只是换成了环形传递

//假设n个点，a1,a2.....an-1,an,a1和a2之间的移动关系是x1，a2和a3之间是x2，x1,x2....可能是+-0，有关系
a1-x1+xn=^a,(^a为集合a的平均数)
a2-x2+x1=^a,
.
.
.
an-1 - xn-1 + xn-2=^a,
an-xn+xn-1=^a;

变换一下：
x1=x1-0,
x2=a2-^a+x1;
x3=a3+a2-2*^a+x1;
.
.
xn=an + an-1 +.....+a2 - (n-1)*^a +x1;

统计x1,x2...xn之和的最小值，即
min(|x1-c1|+|x1-c2|+...|x1-cn|),
就变成了5.1题，当x1=0的时候最小，取这些数的中间值，然后加上每个数到该中间值的距离，就是最小值
具体为什么x1=0，见视频，没弄明白


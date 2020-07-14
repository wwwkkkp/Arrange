

//12.5.1028. 复制书稿 

现在要把 m本有顺序的书分给 k个人复制（抄写），每一个人的抄写速度都一样，一本书不允许给两个（或以上）的人抄写，分给每一个人的书，必须是连续的，比如不能把第一、第三和第四本书给同一个人抄写。
现在请你设计一种方案，使得复制时间最短。
复制时间为抄写页数最多的人用去的时间。
输入格式
第一行两个整数 m，k。第二行 m个整数，第 i个整数表示第 i本书的页数。
输出格式
共 k行，每行两个整数，第i行表示第 i个人抄写的书的起始编号和终止编号。k行的起始编号应该从小到大排列，如果有多解，则尽可能让前面的人少抄写。

数据范围
k≤m≤500

输入样例：
9 3         
1 2 3 4 5 6 7 8 9
输出样例：
1 5
6 7
8 9


//这道题和剪绳子差不多，也是二分，当最大和是t的时候，可以分成多少堆，如例题，如果分的堆数大于3堆，说明t小了，就增大t,如果小于3,说明t大了，就减小t,求的是等于3的最小值
#include<iostream>

using namespace std;
const int N=510;

int n,m;
int a[N];
int L[N],R[N];//记录左边位置和右边位置

bool check(int t){
    
    int cnt=0,s;
    for(int i=n;i>=1;i--){
       R[cnt]=i;
       s=0;
       s+=a[i];
       while(i-1>=1&&s+a[i-1]<=t){
           s+=a[i-1];
           i--;
       }
       L[cnt]=i;
       cnt++;
    }
    L[cnt]=1;//注意这里，最后一个L[cnt]肯定是1
    if(cnt>m)return false;
    else 
        return true;//因为求得是等于3的最小值，所以相等的时候应该返回true，
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    int le=0,ri=1e9;
    while(le<ri){
        int mid=(le+ri)/2;
        if(check(mid))ri=mid;
        else le=mid+1;
    }
    check(ri);//重新计算一遍，免得分歧
    for(int i=m-1;i>=0;i--)cout<<L[i]<<" "<<R[i]<<endl;
    return 0;
}
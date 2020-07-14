//5.5 146. 序列


给定m个序列，每个包含n个非负整数。 
现在我们可以从每个序列中选择一个数字以形成具有m个整数的序列。 
很明显，我们一共可以得到nm个这种序列， 然后我们可以计算每个序列中的数字之和，并得到nm个值。 
现在请你求出这些序列和之中最小的n个值。

输入格式
第一行输入一个整数T，代表输入中包含测试用例的数量。
接下来输入T组测试用例。
对于每组测试用例，第一行输入两个整数m和n。
接下在m行输入m个整数序列，数列中的整数均不超过10000。
输出格式
对于每组测试用例，均以递增顺序输出最小的n个序列和，数值之间用空格隔开。
每组输出占一行。
数据范围
0<m≤1000
，
0<n≤2000
输入样例：
1
2 3
1 2 3
2 2 3
输出样例：
3 3 4



//这道题的核心思路就是：先从两个行中选出最小的n个数，然后将这n个数作为新的一行和第三行选出n个数，以此类推，最后得到的n个数就是最小的n个数
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;
const int M=1010,N=2010;

int n,m,t;

int a[N],b[N],c[N];
typedef pair<int,int> pii;

void minn(){
    priority_queue<pii,vector<pii>,greater<pii>>pq;
    for(int i=0;i<n;i++){
        c[i]=b[i]+a[0];  //a是从小到大排序的，在b[i]+a[0]中选一个最小数，就是这两行的最小数，然后此时将组成这个最小数的b[i]加上a[1]添加进堆中，选出最小数，以此类推，选出最小n个数
        pq.push({c[i],0});
    }
    for(int i=0;i<n;i++){
        pii p=pq.top();
        pq.pop();
        c[i]=p.first;
        int r=p.second;
        pq.push({p.first-a[r]+a[r+1],r+1});
    }
    for(int i=0;i<n;i++)
        a[i]=c[i];
    
}

int main(){
    cin>>t;
    while(t--){
        cin>>m>>n;
        for(int i=0;i<n;i++)cin>>a[i];
        sort(a,a+n);
        for(int i=0;i<m-1;i++){
            for(int j=0;j<n;j++)
                cin>>b[j];
            minn();
            
        }
        for(int i=0;i<n;i++)cout<<a[i]<<" ";
        cout<<endl;
    }
}

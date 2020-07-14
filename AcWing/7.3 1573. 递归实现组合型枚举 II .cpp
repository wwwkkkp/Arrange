

给定一个长度为 
n
n
的可包含重复数字的序列，从中随机选取 
m
//7.3 1573. 递归实现组合型枚举 II 

m个数字，输出所有可能的选择方案。

输入格式
第一行包含两个整数 n,m。
第二行包含 n个正整数。
输出格式
按照从小到大的顺序输出所有方案，每行 1个。
首先，同一行内的数升序排列，相邻两个数用一个空格隔开。
其次，对于两个不同的行，对应下标的数一一比较，字典序较小的排在前面（例如1 3 5 7排在1 3 6 8前面）。

数据范围
n>0
0≤m≤n
n+(n−m)≤25

序列内所有元素均不大于 n。

输入样例：
5 3
1 2 2 3 3
输出样例：
1 2 2
1 2 3
1 3 3
2 2 3
2 3 3


#include<iostream>
#include<algorithm>

using namespace std;
const int N=30;

int n,m;
int a[N];
int b[N];

void dfs(int k,int t){ //t表示有多少个数被选上
    if(t==m){
        
        for(int i=1;i<=n;i++)
            if(b[i])
                cout<<a[i]<<" ";
        cout<<endl;
        return;
    }
    if(k>n)return;
    
    int u=k;
    while(u<=n&&a[k]==a[u])b[u]=true,u++,t++; //因为是从小到大排列，所以要假定所有相同的数都选了，然后再一个一个的减去
    
    dfs(u,t);				//值为a[k]的数都选，
    for(int i=u-1;i>=k;i--){
        b[i]=false;
        t--;
        dfs(u,t);		//这里以u开始的，从全选到一个都不选的遍历
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);  //从小到大排列
    dfs(1,0);
    return 0;
}
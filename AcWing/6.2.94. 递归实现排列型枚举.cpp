//33.94. 递归实现排列型枚举 


把 1~n 这 n个整数排成一行后随机打乱顺序，输出所有可能的次序。

输入格式
一个整数n。

输出格式
按照从小到大的顺序输出所有方案，每行1个。 
首先，同一行相邻两个数用一个空格隔开。
其次，对于两个不同的行，对应下标的数一一比较，字典序较小的排在前面。

数据范围
1≤n≤9

输入样例：
3
输出样例：
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1


//经典dfs

#include<iostream>
#include<algorithm>

using namespace std;
const int N=10;
int n;
int a[N];     //第i个位置放的数字
bool st[N];  //看第i个数有没有选，

void dfs(int k){
    if(k>n){
        for(int i=1;i<=n;i++)
            cout<<a[i]<<" ";
        cout<<endl;
        return ;
    }
    for(int i=1;i<=n;i++){
        if(!st[i]){
            a[k]=i;
            st[i]=true;
            dfs(k+1);
            st[i]=false;
        }
    }
}

int main(){
    cin>>n;
    dfs(1);
    return 0;
}



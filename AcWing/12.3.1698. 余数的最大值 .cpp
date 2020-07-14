

//12.3.1698. 余数的最大值 
给定一个包含 n个正整数的序列，再给定一个正整数 m。
请你求出该序列的子序列的各元素之和对m取模的最大值。

输入格式
第一行包含两个整数 n和 m。
第二行包含 n个正整数。
输出格式
输出一个整数表示结果。
数据范围
1≤n≤34
1≤ai≤10^9
1≤m≤10^9
输入样例：
3 5
2 7 8
输出样例：
4

//这道题的难点在于要对34个数进行选或不选的组合，一共有2^34种情况，一定是超时的，所以需要用双向dfs来选择，即将34个数平均分成两堆，分别求两堆的排列组合，然后求两堆排列组合后的组合，时间复杂度为2^18,
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
typedef long long LL;
const int N=40,M=1e9;

int n,m;
int a[N];

void dfs(int t,int k,int s,vector<int>&v){//选择第t个数，选择结点终点是k，当前选择的和是s,v是选择完以后s的集合
    if(t==k+1){
        v.push_back(s);
        return;
    }
    dfs(t+1,k,(s+a[t])%m,v);
    dfs(t+1,k,s,v);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    vector<int>A,B;
	
    dfs(1,n/2,0,A);
    dfs(n/2+1,n,0,B);

    
    sort(A.begin(),A.end()); //这个时候的A,B中的数都在[0,m-1]之间，求两边的各选一个数相加的余数最大,相加的范围是[0,2m-2]之间，各自求相加之和在[0,m-1]和[m,2m-2]的最大值
    sort(B.begin(),B.end());
    
    int res=(A.back()+B.back())%m;//在[m,2m-2]的最大值就是A,B最大值之和
    int le=0,ri=B.size()-1;
    for(;le<A.size();le++){
        while(ri>=0&&A[le]+B[ri]>=m)ri--;//双指针法，两个数相加要小于m，遍历一遍就行
        if(ri>=0)res=max(res,(A[le]+B[ri])%m);
    }
    cout<<res<<endl;
    return 0;
}
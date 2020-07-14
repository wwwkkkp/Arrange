


//16.3.1158. H指数 

用堆来做H指数
输入样例：
2
3
5 1 2
6
1 3 3 2 2 15
输出样例：
Case #1: 1 1 2
Case #2: 1 1 2 2 2 3


#include<iostream>
#include<queue>

using namespace std;

int t;
int main(){
    cin>>t;
    for(int c=1;c<=t;c++){
        printf("Case #%d:",c);
        int n;
        int res=0;
        priority_queue<int,vector<int>,greater<int>>pg;//最小堆
        cin>>n;
        for(int i=0;i<n;i++){
            int x;
            cin>>x;
            if(res<x)   //如过当前数比h数要大，就添加进堆
                pg.push(x);
            while(pg.size()&&pg.top()<=res)pg.pop();  //删除所有比h数要小的数，
            if(pg.size()>res)res++;    //h数每次最多加1，如果堆中的数多了，才能加，保证堆中的最小值>=堆中数的个数
            cout<<" "<<res;
        }
        cout<<endl;
    }
    return 0;
}
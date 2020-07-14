//32.92. 递归实现指数型枚举 

从 1~n 这 n 个整数中随机选取任意多个，输出所有可能的选择方案。
输入格式
输入一个整数n。
输出格式
每行输出一种方案。
同一行内的数必须升序排列，相邻两个数用恰好1个空格隔开。
对于没有选任何数的方案，输出空行。
本题有自定义校验器（SPJ），各行（不同方案）之间的顺序任意。
数据范围
1≤n≤15

输入样例：
3
输出样例：

3
2
2 3
1
1 3
1 2
1 2 3


//经典的DFS，对于某个数，要么选要么不选，

#include<iostream>
#include<algorithm>

using namespace std;
const int N=20;
int n;

bool b[N]; //第i个数有没有选

void dfs(int k){
    if(k>n){
        for(int i=1;i<=n;i++)
            if(b[i])
                cout<<i<<" ";
        cout<<endl;
        return;
    }
    b[k]=true;
    dfs(k+1);
    b[k]=false;
    dfs(k+1);
}

int main(){
    cin>>n;
    dfs(1);
    return 0;
}


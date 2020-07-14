

//13.5.1114. 棋盘问题 
在一个给定形状的棋盘（形状可能是不规则的）上面摆放棋子，棋子没有区别。
要求摆放时任意的两个棋子不能放在棋盘中的同一行或者同一列，请编程求解对于给定形状和大小的棋盘，摆放 k个棋子的所有可行的摆放方案数目 C。
输入格式
输入含有多组测试数据。
每组数据的第一行是两个正整数 n,k，用一个空格隔开，表示了将在一个 n*n的矩阵内描述棋盘，以及摆放棋子的数目。当为-1 -1时表示输入结束。
随后的 n行描述了棋盘的形状：每行有 n个字符，其中 # 表示棋盘区域， . 表示空白区域（数据保证不出现多余的空白行或者空白列）。
输出格式
对于每一组数据，给出一行输出，输出摆放的方案数目 C（数据保证 C<231）。数据范围n≤8,k≤n

输入样例：
2 1
#.
.#
4 4
...#
..#.
.#..
#...
-1 -1

输出样例：
2
1


//dfs
#include<iostream>

using namespace std;

const int N=10;

int n,m;
char a[N][N];
bool r[N];

int dfs(int t,int k){//选择第t行，已经填了k个棋子
    if(k==m)return 1;
    if(t==n)return 0;
    int s=0;
    for(int i=0;i<n;i++){
        if(a[t][i]=='#'&&!r[i]){
            r[i]=true;//该列已经占用
            s+=dfs(t+1,k+1);
            r[i]=false;
        }
    }
    s+=dfs(t+1,k);//该行没有填
    return s;
}

int main(){
    while(cin>>n>>m,n>0){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>a[i][j];
            }
        }
        cout<<dfs(0,0)<<endl;
    }
    return 0;
}
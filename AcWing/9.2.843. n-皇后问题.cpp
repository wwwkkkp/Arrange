//9.2.843. n-皇后问题 
n-皇后问题是指将 n 个皇后放在 n∗n 的国际象棋棋盘上，使得皇后不能相互攻击到，/**即任意两个皇后都不能处于同一行、同一列或同一斜线上*/。
 
现在给定整数n，请你输出所有的满足条件的棋子摆法。
输入格式
共一行，包含整数n。
输出格式
每个解决方案占n行，每行输出一个长度为n的字符串，用来表示完整的棋盘状态。
其中”.”表示某一个位置的方格状态为空，”Q”表示某一个位置的方格上摆着皇后。
每个方案输出完成后，输出一个空行。
输出方案的顺序任意，只要不重复且没有遗漏即可。
数据范围1≤n≤9

输入样例：
4
输出样例：
.Q..
...Q
Q...
..Q.

..Q.
Q...
...Q
.Q..


//暴搜
#include<iostream>
using namespace std;

const int N=10;

int n;
char g[N][N];
bool col[N],op[N],uop[N];//col:第i列能不能存，op：正斜杠能不能存 ，uop：反斜杠能不能存    true不能，false可以


void dfs(int u){//第i行放数
    if(u==n+1){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                cout<<g[i][j];
            cout<<endl;
        }
        cout<<endl;
    }
    for(int i=1;i<=n;i++){
        if(!col[i]&&!op[u+i]&&!uop[u-i+n]){
            col[i]=op[u+i]=uop[u-i+n]=true; //当第i列放下皇后，那这一列 正斜杠 反斜杠 都不能存了，注意：正斜杠反斜杠利用了坐标之间的关系区分开的即y=x+b,y=-x+b;b就是对应的斜杠编号
            g[u][i]='Q';
            dfs(u+1);
            g[u][i]='.';
            col[i]=op[u+i]=uop[u-i+n]=false;
        }
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g[i][j]='.';
    dfs(1);
    return 0;
}

//13.2.1102. 移动骑士 
给定一个 n*n的棋盘，以及一个开始位置和终点位置。
棋盘的横纵坐标范围都是 0-n。
将一个国际象棋中的骑士放置在开始位置上，请问将它移动至终点位置至少需要走多少步。
一个骑士在棋盘上可行的移动方式如下图所示：
 
输入格式
第一行包含整数 T，表示共有 T组测试数据。
每组测试数据第一行包含整数n，表示棋盘大小。
第二行包含两个整数 x,y用来表示骑士的开始位置坐标 (x,y)。
第三行包含两个整数 x,y用来表示骑士的终点位置坐标 (x,y)。
输出格式
每组数据输出一个整数，表示骑士所需移动的最少步数，每个结果占一行。
数据范围
4≤n≤300
0≤x,y≤n
输入样例：
3
8
0 0
7 0
100
0 0
30 50
10
1 1
1 1
输出样例：
5
28
0

//典型bfs,和上一题一样
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

const int N=310;

int n,t;
int dx[]={1,2,2,1,-1,-2,-2,-1};
int dy[]={2,1,-1,-2,-2,-1,1,2};
int d[N][N]; 

int main(){
    cin>>t;
    while(t--){
        cin>>n;
        int ib,jb,ie,je;
        cin>>ib>>jb>>ie>>je;
        if(ib==ie&&jb==je){
            cout<<0<<endl;
            continue;
        }
        queue<pair<int,int>>q;
        q.push({ib,jb});
        memset(d,0xffff,sizeof d);
        d[ib][jb]=0;
        int k=0;
        while(q.size()&&k==0){
            auto w=q.front();
            q.pop();
            int a=w.first;
            int b=w.second;
            for(int i=0;i<8;i++){
                int aa=a+dx[i];
                int bb=b+dy[i];
                if(aa>=0&&aa<n&&bb>=0&&bb<n&&d[aa][bb]==-1){
                    if(aa==ie&&bb==je){
                        cout<<d[a][b]+1<<endl;
                        k=1;
                        break;
                    }else{
                        d[aa][bb]=d[a][b]+1;
                        q.push({aa,bb});
                    }
                }
            }
        }
    }
    return 0;
}
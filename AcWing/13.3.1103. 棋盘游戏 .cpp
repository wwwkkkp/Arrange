
//13.3.1103. 棋盘游戏 

在一个4×4的棋盘上有 8个黑棋和 8个白棋，当且仅当两个格子有公共边，这两个格子上的棋是相邻的。
移动棋子的规则是交换相邻两个棋子。
给出一个初始棋盘和一个最终棋盘，请找出一个最短的移动序列使初始棋盘变为最终棋盘。
输入格式
第一行到第四行，每行 4个数字（0 或者 1），描述了初始棋盘；
接着是一个空行；
第六行到第九行，每行4个数字（0 或者 1），描述了最终棋盘。数字 0表示白棋，数字 1表示黑棋。

输出格式
输出一个整数，表示最少的移动步数。数据保证有解。
输入样例:
1111
0000
1110
0010

1010
0101
1010
0101
输出样例：
4


//暴力bfs，这道题两个核心：1.对棋盘的存储方式是二进制存储，2，暴力搜索并不超时，因为是4*4,的矩阵，所以总共16位，二进制来说最多65535种情况，不算多
#include<cstring>
#include<iostream>
#include<queue>

using namespace std;

const int N=1<<16;

int d[N];//是否出现过
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

int input(){
    int a=0;
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            char c;
            cin>>c;
            a=(a<<1)+c-'0';//注意这里的计算优先级，<<的优先级是最低的，所以要加上括号
        }
    }
    return a;
}

int bit_swap(int w,int a,int b){ //按位交换，值得借鉴
    int r=w>>a&1,g=w>>b&1; //选出两个要交换位置的数
    w-=r<<a;//减去这两个位置的数
    w-=g<<b;
    w+=r<<b;//加上对方位置的数
    w+=g<<a;
    return w;
}
int main(){
    int a=input();
    int b=input();
    if(a==b){
        cout<<0<<endl;
        return 0;
    }
    memset(d,-1,sizeof d);
    queue<int>q;
    q.push(a);
    d[a]=0;
	
    while(q.size()){
        int w=q.front();
        q.pop();
        
        for(int i=0;i<4;i++){ //对某一个棋盘上的所有相邻位进行翻转，然后依次压入队列
            for(int j=0;j<4;j++){
                for(int k=0;k<4;k++){
                    int x=i+dx[k];
                    int y=j+dy[k];
                    if(x>=0&&x<4&&y>=0&&y<4){
                        int m=bit_swap(w,i*4+j,x*4+y);
                        if(d[m]==-1){
                            if(m==b){
                                cout<<d[w]+1<<endl;
                                return 0;
                            }else{
                                d[m]=d[w]+1;
                                q.push(m);
                            }
                        }
                    }
                }
            }
        }
    }
    cout<<-1<<endl;
    return 0;
}
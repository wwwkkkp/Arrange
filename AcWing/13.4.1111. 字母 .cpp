
//13.4.1111. 字母 

给定一个R×S的大写字母矩阵，你的起始位置位于左上角，你可以向上下左右四个方向进行移动，但是不能移出边界，或者移动到曾经经过的字母（左上角字母看作第一个经过的字母）。
请问，你最多可以经过几个字母。
输入格式
第一行包含两个整数 R和 S，表示字母矩阵的行和列。
接下来 R行，每行包含一个长度为 S的大写字母构成的字符串，共同构成字母矩阵。
输出格式
输出一个整数，表示最多能够经过的字母个数。
数据范围
1≤R,S≤20
输入样例：
3 6
HFDFFB
AJHGDH
DGAGEH
输出样例：
6

//dfs 自己的写法有点笨拙
#include<iostream>

using namespace std;

const int N=21;

int n,m;
bool st[30];
char a[N][N];

int dx[]={0,-1,0,1};
int dy[]={1,0,-1,0};

int dfs(int x,int y){ //在x,y这个位置所能到的最远距离
    int ju=0;
    for(int i=0;i<4;i++){
        int t=x+dx[i];
        int b=y+dy[i];
        if(t>=0&&t<n&&b>=0&&b<m){
            if(st[a[t][b]-'A'])
                ju++;
        }
    }
    if(ju==4)return 1; //如果上下左右都访问过了，那就返回1，
    
    int s=1;//初始值是1
    for(int i=0;i<4;i++){
        int t=x+dx[i];
        int b=y+dy[i];
        if(t>=0&&t<n&&b>=0&&b<m){
            if(!st[a[t][b]-'A']){
                st[a[t][b]-'A']=true;
                s=max(s,dfs(t,b)+1);//四个方向所能到的最远值+1=当前位置的最远值
                st[a[t][b]-'A']=false;
            }
        }
    }
    return s;
}

int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>a[i][j];
        }
    }
    st[a[0][0]-'A']=true;
    cout<<dfs(0,0)<<endl;
    return 0;
}

//y总写法
#include <iostream>
#include <cstring>

using namespace std;

const int N = 30;

int n, m;
char g[N][N];
bool st[N];
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

int dfs(int x, int y)
{
    int u = g[x][y] - 'A';
    st[u] = true;

    int sum = 0;
    for (int i = 0; i < 4; i ++ )
    {
        int a = x + dx[i], b = y + dy[i];
        if (a >= 0 && a < n && b >= 0 && b < m)
        {
            int t = g[a][b] - 'A';
            if (!st[t]) sum = max(sum, dfs(a, b));
        }
    }

    st[u] = false;
    return sum + 1;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i ++ ) cin >> g[i];

    cout << dfs(0, 0) << endl;

    return 0;
}


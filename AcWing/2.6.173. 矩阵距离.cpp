//12.173. 矩阵距离

给定一个N行M列的01矩阵A，A[i][j] 与 A[k][l] 之间的曼哈顿距离定义为：
dist(A[i][j],A[k][l])=|i−k|+|j−l|

输出一个N行M列的整数矩阵B，其中：

B[i][j]=min(1≤x≤N,1≤y≤M,A[x][y]=1⁡) dist(A[i][j],A[x][y])
输入格式
第一行两个整数n,m。
接下来一个N行M列的01矩阵，数字之间没有空格。
输出格式
一个N行M列的矩阵B，相邻两个整数之间用一个空格隔开。
数据范围
1≤N,M≤1000
输入样例：
3 4
0001
0011
0110
输出样例：
3 2 1 0
2 1 0 0
1 0 0 1

//通俗的说就是矩阵总各位置距离1的最近距离
//BFS

#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;
const int N=1010;

int n,m;
char mat[N][N];
int out[N][N];
int visit[N][N];

int main(){
	cin>>n>>m;
	queue<pair<int,int>>q;
	memset(out,-1,sizeof(out));
	memset(visit,0,sizeof(visit));
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>mat[i][j];
			if(mat[i][j]=='1'){
				q.push({i,j});
				out[i][j]=0;
				visit[i][j]=1;
			}
				
		}
	}
	int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
	while(q.size()){
		auto p=q.front();
		q.pop();
		int x=p.first;
		int y=p.second;
		for(int i=0;i<4;i++){
			int a=x+dx[i];
			int b=y+dy[i];
			if(a>=0&&a<n&&b>=0&&b<m&&0==visit[a][b]){
				out[a][b]=out[x][y]+1;
				visit[a][b]=1;
				q.push({a,b});
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<out[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
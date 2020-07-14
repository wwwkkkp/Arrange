//螺旋矩阵
样例：
输入：
3 3
输出：
1 2 3
8 9 4
7 6 5

//代码

#include <iostream>
#include <algorithm>

using namespace std;

int n,m;
int res[110][110];

int main(){
	cin>>n>>m;
	int dx[4]={0,1,0,-1};
	int dy[4]={1,0,-1,0};
	int k=1;
	for(int x=0,y=0,d=0;k<=n*m;k++){
		res[x][y]=k;
		int a=x+dx[d];//注意这里：在原来的方向上走一步
		int b=y+dy[d];
		if(a<0||a>=n||b<0||b>=m||res[a][b]){  //走到头
			d=(d+1)%4;  //换方向
			a=x+dx[d];  //走一步
			b=y+dy[d];
		}
		x=a;  //更新
		y=b;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<res[i][j]<<' ';
		}
		cout<<endl;
	}
	return 0;
}
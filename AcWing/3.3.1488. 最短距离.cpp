//15.1488. 最短距离 

有 N个村庄，编号 1到 N。
村庄之间有 M条无向道路，第 i条道路连接村庄 ai和村庄 bi，长度是 ci。
所有村庄都是连通的。
共有 K个村庄有商店，第 j个有商店的村庄编号是 xj。
然后给出Q个询问，第 k个询问给出一个村庄的编号 yk，问该村庄距离最近的商店有多远？

输入格式
第一行包含两个整数 N,M。
接下来 M行，每行包含三个整数 ai,bi,ci，表示第 i条道路连接村庄 ai和村庄 bi，长度是 ci。再一行包含整数 K。接下来 K行，每行包含一个整数 xj，表示第 j个有商店的村庄编号是xj。再一行包含整数 Q。接下来 Q行，每行包含一个整数 yk，表示询问编号为 yk的村庄与其距离最近的商店之间的距离。

输出格式
对于每个询问，输出该询问的结果。
数据范围2≤N≤10^5,N−1≤M≤min(N(N−1)2,10^5),1≤Q≤10^5,1≤K≤N,1≤ci≤10000
输入样例：
7 7
1 2 5
1 4 3
2 3 2
2 5 1
3 6 7
5 6 8
6 7 6
3
7
5
4
7
1
2
3
4
5
6
7
输出样例：
3
1
3
0
0
6
0




//


#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;
const int N = 1e5 + 5,M = N * 3;

int n, m, k, p;
int h[N], ne[M], u[M], w[M], idx = 0;
int dist[N]；
bool v[N];

void add(int a, int b, int c) {   //邻接表的数组表示，https://www.cnblogs.com/codingmengmeng/p/5645073.html
	u[idx] = b, w[idx] = c, ne[idx] = h[a] ,h[a] = idx, idx++;//idx是线段的编号，h[a]是以a为起点的线段的编号，ne是并查集，表示上一次以a为起点的线段编号，注意，h的初始化必须是-1，这样顶到并查集中的头就是-1，u是第idx条线段的终点，如 t,e[h[t]]就是一条边
}
void spfa() {   //sfpa()算法，当某个结点距离更新，就添加进队列，去改变该结点的周围结点，比dj算法要好
	memset(dist, 0x3f, sizeof(dist));
	
    queue<int>q;
    q.push(0);
    
	dist[0] = 0;
	v[0] = true;  //判断i是否在队列中，不要二次添加

	while (q.size()) {
        int t=q.front();
        q.pop();

        v[t]=false;
		for (int i = h[t]; ~i ; i = ne[i]) {
			int j = u[i];
			if (dist[j] > dist[t] + w[i]) {
				dist[j] = dist[t] + w[i];
				if (!v[j]) {
					v[j] = true;
					q.push(j);

				}
			}

		}
	}
}

int main() {

	cin >> n >> m;
	memset(h, -1, sizeof(h));
	
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		add(a, b, c);
		add(b, a, c);
	}
	cin >> k;
	while(k--) {
		int a;
		cin >> a;

		add(0, a, 0);  //超级起点，把所有商店合并在一个点，这个点到各商店的距离为0，
	}
	
	spfa();
	
	cin >> p;

	while(p--) {
		int a;
		cin >> a;
		cout << dist[a] << endl;
	}

	return 0;
}

 


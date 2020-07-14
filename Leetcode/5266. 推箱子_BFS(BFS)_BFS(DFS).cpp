/*5266. 推箱子
推箱子」是一款风靡全球的益智小游戏，玩家需要将箱子推到仓库中的目标位置。

游戏地图用大小为 n * m 的网格 grid 表示，其中每个元素可以是墙、地板或者是箱子。

现在你将作为玩家参与游戏，按规则将箱子 'B' 移动到目标位置 'T' ：

玩家用字符 'S' 表示，只要他在地板上，就可以在网格中向上、下、左、右四个方向移动。
地板用字符 '.' 表示，意味着可以自由行走。
墙用字符 '#' 表示，意味着障碍物，不能通行。 
箱子仅有一个，用字符 'B' 表示。相应地，网格上有一个目标位置 'T'。
玩家需要站在箱子旁边，然后沿着箱子的方向进行移动，此时箱子会被移动到相邻的地板单元格。记作一次「推动」。
玩家无法越过箱子。
返回将箱子推到目标位置的最小 推动 次数，如果无法做到，请返回 -1。
输入：grid = [["#","#","#","#","#","#"],
             ["#","T","#","#","#","#"],
             ["#",".",".","B",".","#"],
             ["#",".","#","#",".","#"],
             ["#",".",".",".","S","#"],
             ["#","#","#","#","#","#"]]
输出：3
解释：我们只需要返回推箱子的次数。

示例 2：

输入：grid = [["#","#","#","#","#","#"],
             ["#","T","#","#","#","#"],
             ["#",".",".","B",".","#"],
             ["#","#","#","#",".","#"],
             ["#",".",".",".","S","#"],
             ["#","#","#","#","#","#"]]
输出：-1

示例 3：

输入：grid = [["#","#","#","#","#","#"],
             ["#","T",".",".","#","#"],
             ["#",".","#","B",".","#"],
             ["#",".",".",".",".","#"],
             ["#",".",".",".","S","#"],
             ["#","#","#","#","#","#"]]
输出：5
解释：向下、向左、向左、向上再向上。

示例 4：

输入：grid = [["#","#","#","#","#","#","#"],
             ["#","S","#",".","B","T","#"],
             ["#","#","#","#","#","#","#"]]
输出：-1
*/

/*
方法一：广度优先搜索

对于二维矩阵中求最短路的问题，我们一般可以使用广度优先搜索 + 队列的方法解决。
在本题中，如果没有玩家，而是箱子每一步可以自行向四个方向移动一格，那么我们就可以从箱子的初始位置开始，
使用二元组 (x, y)，即箱子的坐标表示状态，通过广度优先搜索，直至搜索到目标位置。然而本题需要玩家推动箱子，
因此只用二元组 (x, y) 表示一个状态是不够的，因为玩家的可移动范围是随着箱子位置的变化而变化的。
因此我们可以考虑用四元组 (bx, by, mx, my) 表示一个状态，其中 (bx, by) 表示箱子的位置，(mx, my) 表示玩家的位置。

对于当前的状态 (bx, by, mx, my)，它可以向最多四个新状态进行搜索，即将玩家 (mx, my) 向四个方向移动一格。
假设移动的方向为 (dx, dy)，那么玩家的新位置为 (mx + dx, my + dy)。如果该位置为地板且箱子不在此处，那么根据题目要求，
玩家移动到新位置不计入推动次数。如果该位置为箱子 (bx, by)，那么箱子可能的新位置为 (bx + dx, bx + dy)，如果该位置为地板，
那么箱子会被推动，根据题目要求，计入一次推动次数。当箱子到达了目标位置，我们就得到了最小推动次数。

注意到上面的方法存在一个小问题，假设状态 S 可以向两个状态 S1 和 S2 进行搜索，S1 中箱子被推动，S2 中箱子未被推动。
由于 S1 相较于 S2 先进入队列，因此我们并没有按照广度优先搜索的要求，先搜索小状态，后搜索大状态。因此当我们有搜索队列 q 时，
对于 q 中的每一个状态 S 可以得到的新状态 Sx，如果 Sx 中箱子未被推动，那么可以直接将 Sx 加入队列末尾；如果 Sx 中箱子被推动，
那么需要将 Sx 加入一个新的队列 nq 中。可以发现，q 中所有的状态都有着相同的推动次数 k，而 nq 中所有的状态都有着相同的推动次数 k + 1。
在 q 中所有状态都搜索完毕，即 q 为空时，我们将 nq 赋予 q，再开始新的一轮广度优先搜索。这样我们就保证了先搜索小状态，后搜索大状态的策略。


*/
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
#include<queue>
using namespace std;
struct Dwell {
	int box_x, box_y;
	int man_x, man_y;
	Dwell(int _bx, int _by, int _mx, int _my) : box_x(_bx), box_y(_by), man_x(_mx), man_y(_my) {}
};


static constexpr int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };


int minPushBox(vector<vector<char>>& grid) {
	int m = grid.size();
	int n = grid[0].size();
	int dist[10][10][10][10];
	memset(dist, -1, sizeof(dist));

	int box_x, box_y;
	int start_x, start_y;
	int end_x, end_y;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (grid[i][j] == 'B') {
				box_x = i;
				box_y = j;
				grid[i][j] = '.';
			}
			else if (grid[i][j] == 'S') {
				start_x = i;
				start_y = j;
				grid[i][j] = '.';
			}
			else if (grid[i][j] == 'T') {
				end_x = i;
				end_y = j;
				grid[i][j] = '.';
			}
		}
	}

	queue<Dwell> q;
	q.emplace(box_x, box_y, start_x, start_y);
	dist[box_x][box_y][start_x][start_y] = 0;

	while (!q.empty()) {
		queue<Dwell> nq;
		while (!q.empty()) {
			Dwell cur = q.front();
			q.pop();

			for (int i = 0; i < 4; ++i) {
				int nxt_x = cur.man_x + dirs[i][0];
				int nxt_y = cur.man_y + dirs[i][1];//人移步
				if (nxt_x >= 0 && nxt_x < m && nxt_y >= 0 && nxt_y < n) {//在界内
					if (cur.box_x == nxt_x && cur.box_y == nxt_y) {//如果人和箱子重合，箱子要挪步
						int nxt_box_x = cur.box_x + dirs[i][0];
						int nxt_box_y = cur.box_y + dirs[i][1];//箱子挪步
						if (nxt_box_x >= 0 && nxt_box_x < m && nxt_box_y >= 0 && nxt_box_y < n) {//是否在范围内
							if (grid[nxt_box_x][nxt_box_y] == '.' && dist[nxt_box_x][nxt_box_y][nxt_x][nxt_y] == -1) {
								nq.emplace(nxt_box_x, nxt_box_y, nxt_x, nxt_y);    //如果推动了箱子，把该状态计入nq，只把改动后的坐标添加进nq,本身是不动的
								dist[nxt_box_x][nxt_box_y][nxt_x][nxt_y] = dist[cur.box_x][cur.box_y][cur.man_x][cur.man_y] + 1;//记步数
								if (nxt_box_x == end_x && nxt_box_y == end_y) {
									return dist[nxt_box_x][nxt_box_y][nxt_x][nxt_y];
								}
							}
						}
					}
					else {
						if (grid[nxt_x][nxt_y] == '.' && dist[cur.box_x][cur.box_y][nxt_x][nxt_y] == -1) {//该状态是否走过
							q.emplace(cur.box_x, cur.box_y, nxt_x, nxt_y);  //人挪步，把该状态计入q
							dist[cur.box_x][cur.box_y][nxt_x][nxt_y] = dist[cur.box_x][cur.box_y][cur.man_x][cur.man_y];
						}
					}
				}
			}
		}
		q = nq;   //再次遍历本次遍历中推动箱子的步数
	}


	return -1;
}




int main()
{
	vector<vector<char>> nums = { {'#', '#','#', '#','#', '#'},
	{'#', '#', '#', '#','T', '#'},
	{'#', '.', '.', 'B', '.', '#'},
	{'#', '.', '#', '#', '.', '#'},
	{'#', '.', '.', '.','S', '#'},
{'#', '#','#', '#', '#','#'}};


	int a= minPushBox(nums);
	return 0;
}



//BFS+DFS
//DFS是 定位到位置可推动箱子的地方 ，然后BFS就开始推箱子，推一步又调用DFS，找出可能的可推的位置

#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<algorithm>
#include<queue>
using namespace std;

	// 人的位置 (sx, sy)
	// 箱子的位置 (bx, by)
	struct Node {
		// 用来表示状态
		int sx, sy, bx, by;
	};
	// 去掉 人 箱子 目的地 位置的图
	vector<vector<char>> G_;
	int M_;
	int N_;
	bool valid(int x, int y) {
		return x >= 0 && x < M_ && y >= 0 && y < N_ && G_[x][y] == '.';
	}
	// 记录状态，避免重复访问
	int flag[21][21][21][21];
	void dfs(const Node& cur, vector<Node>& cand, vector<vector<bool>> &vis) {
		// 已经有了下一步的所有可能，返回
		if (cand.size() == 4) return;
		int sx = cur.sx, sy = cur.sy;
		int bx = cur.bx, by = cur.by;
		vis[sx][sy] = true;
		int d[4][2] = { {0,1},{0,-1},{-1,0},{1,0} };
		for (int k = 0; k < 4; ++k) {
			int nx = sx + d[k][0];
			int ny = sy + d[k][1];
			if (nx == bx && ny == by) {
				// 抵达推箱子的位置
				int pushToX = nx + d[k][0];
				int pushToY = ny + d[k][1];
				if (valid(pushToX, pushToY) && flag[nx][ny][pushToX][pushToY] == 0) {
					flag[nx][ny][pushToX][pushToY] = 1;
					cand.push_back(Node{ nx, ny, pushToX, pushToY });
				}
			}
			else if (valid(nx, ny) && !vis[nx][ny]) {
				// 未抵达推箱子位置，继续查找
				dfs(Node{ nx, ny, bx, by }, cand, vis);
			}
		}
	}

	int minPushBox(vector<vector<char>>& A) {
		memset(flag, 0, sizeof(flag));
		G_ = A;
		M_ = A.size(), N_ = A[0].size();
		int sx, sy, bx, by;
		int tx, ty;
		for (int i = 0; i < M_; ++i) {
			for (int j = 0; j < N_; ++j) {
				if (A[i][j] == 'S') {
					sx = i, sy = j;
				}
				if (A[i][j] == 'B') {
					bx = i, by = j;
				}
				if (A[i][j] == 'T') {
					tx = i, ty = j;
				}
			}
		}
		// 将 人 箱子 目的地置为空，方便后续遍历
		G_[sx][sy] = '.';
		G_[bx][by] = '.';
		G_[tx][ty] = '.';

		queue<Node> qu;
		qu.push(Node({ sx,sy,bx,by }));
		int depth = 0;
		while (!qu.empty()) {
			int len = (int)qu.size();
			while (len--) {
				// 类似层次遍历，每个循环都要去找下一步可能的方向
				auto nd = qu.front(); qu.pop();
				if (nd.bx == tx && nd.by == ty) {
					// 抵达目的地
					return depth;
				}
				vector<Node> cand;
				vector<vector<bool>> vis(M_, vector<bool>(N_));
				// dfs查找，人是否可以到对应的推箱子的方向的位置，可以的话，将方向放入候选方向 cand
				dfs(nd, cand, vis);
				for (auto nd : cand) {
					qu.push(nd);
				}
			}
			// 完成了一次推动
			depth++;
		}
		return -1;
	}


int main()
{
	vector<vector<char>> nums = { {'#', '#','#', '#','#', '#'},
	{'#', '#', '#', '#','T', '#'},
	{'#', '.', '.', 'B', '.', '#'},
	{'#', '.', '#', '#', '.', '#'},
	{'#', '.', '.', '.','S', '#'},
{'#', '#','#', '#', '#','#'}};


	int a= minPushBox(nums);
	return 0;
}
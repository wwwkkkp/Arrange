/* 130. 被围绕的区域

给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。

找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。

示例:

X X X X
X O O X
X X O X
X O X X
运行你的函数后，矩阵变为：

X X X X
X X X X
X X X X
X O X X
解释:

被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。

*/


//BFS
class Solution {
public:
    int dis[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
    void solve(vector<vector<char>>& board) {
        if(!board.size())return ;
        int x=board.size();
        int y=board[0].size();
        vector<vector<int>> visit(x,vector<int>(y,0));
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(board[i][j]=='O'&&visit[i][j]==0){
                    visit[i][j]=1;
                    vector<vector<int>> zb;
                    queue<vector<int>> q;
                    zb.push_back({i,j});
                    q.push({i,j});
                    int juice=0;
                    while(!q.empty()){
                        vector<int> a=q.front();
                        q.pop();
                        for(int k=0;k<4;k++){
                            int m=a[0]+dis[k][0];
                            int n=a[1]+dis[k][1];
                            if(m<0||m>=x||n<0||n>=y) {                      
                                juice=1;
                                continue;
                            }
                            if(board[m][n]=='O'&&visit[m][n]==0){
                                zb.push_back({m,n});
                                q.push({m,n});
                                visit[m][n]=1;
                            }
                        }
                    }
                    if(juice==0){
                        for(int k=0;k<zb.size();k++){
                            board[zb[k][0]][zb[k][1]]='X';
                        }
                    }
                }
            }
        }
    }
};

//并查集
class Solution:
    def solve(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        f = {}
        def find(x):
            f.setdefault(x, x)
            if f[x] != x:
                f[x] = find(f[x])
            return f[x]
        def union(x, y):
            f[find(y)] = find(x)   
            
        if not board or not board[0]:
            return
        row = len(board)
        col = len(board[0])
        dummy = row * col
        for i in range(row):
            for j in range(col):
                if board[i][j] == "O":
                    if i == 0 or i == row - 1 or j == 0 or j == col - 1:
                        union(i * col + j, dummy)
                    else:
                        for x, y in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                            if board[i + x][j + y] == "O":
                                union(i * col + j, (i + x) * col + (j + y))
        for i in range(row):
            for j in range(col):
                if find(dummy) == find(i * col + j):
                    board[i][j] = "O"
                else:
                    board[i][j] = "X"


//并查集 C++版
class Solution {
public:
    int dis[4][2] = { {0,1},{0,-1},{-1,0},{1,0} };
    int Find(vector<int>& and_cheak, int n) {
        if (and_cheak[n] ==n)
            return n;
        else
            return and_cheak[n] = Find(and_cheak, and_cheak[n]);//路径压缩+查找;
    }
    void acunion(vector<int>& and_cheak, int i, int j) {
        and_cheak[Find(and_cheak, j)] = Find(and_cheak,i); //j的源头指向i;
		//注意，并查集的头结点之间的合并，不是单个的数之间合并，已存在连接是不会改变的;
    }
    void solve(vector<vector<char>>& board) {
        if(!board.size()) return;
        int x = board.size();
        int y = board[0].size();
        vector<int>and_cheak(x*y + 1);
        for (int i = 0; i < x*y + 1; i++)
            and_cheak[i]=i;
		
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if (board[i][j] == 'O') {
                    if (i == 0 || i == x - 1 || j == 0 || j == y - 1) {
                        acunion(and_cheak, i*y + j, x*y);
                    }
					
                    else {
                        for (int k = 0; k < 4; k++) {
                            int m = i + dis[k][0];
                            int n = j + dis[k][1];
                            if (board[m][n] == 'O')
                                acunion(and_cheak, i*y + j, m*y + n);
                        }
                    }
                }
            }
        }
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if (Find(and_cheak, i*y + j) == Find(and_cheak, x*y) )  //最后所有不用修改的'O'都连在一起了
                    board[i][j] = 'O';
                else
                    board[i][j] = 'X';
            }
        }
    }
};
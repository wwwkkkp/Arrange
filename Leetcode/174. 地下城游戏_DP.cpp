


174. 地下城游戏
一些恶魔抓住了公主（P）并将她关在了地下城的右下角。地下城是由 M x N 个房间组成的二维网格。我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。

骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。

有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；其他房间要么是空的（房间里的值为 0），要么包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。

为了尽快到达公主，骑士决定每次只向右或向下移动一步。

 

编写一个函数来计算确保骑士能够拯救到公主所需的最低初始健康点数。

例如，考虑到如下布局的地下城，如果骑士遵循最佳路径 右 -> 右 -> 下 -> 下，则骑士的初始健康点数至少为 7。

-2 (K)	-3	3
-5	-10	1
10	30	-5 (P)
 

说明:

骑士的健康点数没有上限。

任何房间都可能对骑士的健康点数造成威胁，也可能增加骑士的健康点数，包括骑士进入的左上角房间以及公主被监禁的右下角房间。

//递推
const int N=1010;
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& v) {
        int n=v.size();
        if(!n)return 0;
        int m=v[0].size();
        
        int f[N][N];
        memset(f,0x3f3f3f,sizeof(f));
        f[n-1][m-1]=v[n-1][m-1]>=0?1:1-v[n-1][m-1];
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                if(i==n-1&&j==m-1)continue;
                f[i][j]=min(f[i+1][j]-v[i][j],f[i][j+1]-v[i][j]);  //到每个房间所需要的最小血量，才能通过这个房间，
                if(f[i][j]<=0)f[i][j]=1;				//如果这个房间是小于等于零的，就不行，至少是1，
            }
        }
        return f[0][0];
    }
};




//典型题
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[m][n - 1] = 1; dp[m - 1][n] = 1;
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                dp[i][j] = max(1, min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j]);
                //dp这个数组的意思是进入某个房间之前至少需要的血量，这里的递归思想是倒推 逆向动态规划
            }
        }
      return dp[0][0] ;
    }
};
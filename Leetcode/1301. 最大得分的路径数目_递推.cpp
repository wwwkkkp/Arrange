

//1301. 最大得分的路径数目
给你一个正方形字符数组 board ，你从数组最右下方的字符 'S' 出发。

你的目标是到达数组最左上角的字符 'E' ，数组剩余的部分为数字字符 1, 2, ..., 9 或者障碍 'X'。在每一步移动中，你可以向上、向左或者左上方移动，可以移动的前提是到达的格子没有障碍。

一条路径的 「得分」 定义为：路径上所有数字的和。

请你返回一个列表，包含两个整数：第一个整数是 「得分」 的最大值，第二个整数是得到最大得分的方案数，请把结果对 10^9 + 7 取余。

如果没有任何路径可以到达终点，请返回 [0, 0] 。

 

示例 1：

输入：board = ["E23","2X2","12S"]
输出：[7,1]
示例 2：

输入：board = ["E12","1X1","21S"]
输出：[4,2]
示例 3：

输入：board = ["E11","XXX","11S"]
输出：[0,0]
 

提示：

2 <= board.length == board[i].length <= 100



class Solution {
public:
    int f[110][110],p[110][110];
    int mod=1e9+7;
    vector<int> pathsWithMaxScore(vector<string>& b) {
        memset(f,0,sizeof f);   //到i,j点 和的最大值，
        memset(p,0,sizeof p);   //到这个最大值的个数
        
        int n=b.size();
        //if(bfs(b)==false)return {0,0};
        p[n-1][n-1]=1;
        for(int i=n-1;i>=0;i--){
            for(int j=n-1;j>=0;j--){
                if(b[i][j]>='0'&&b[i][j]<='9'||b[i][j]=='E'){
                    if(i+1<n&&j+1<n){
                        f[i][j]=max(f[i+1][j],max(f[i+1][j+1],f[i][j+1]));		//是从哪个方向到这个点的
                        if(f[i][j]==f[i+1][j])p[i][j]=(p[i][j]+p[i+1][j])%mod;	//如果这个点是从下方来的，就加上下方的p
                        if(f[i][j]==f[i][j+1])p[i][j]=(p[i][j]+p[i][j+1])%mod;
                        if(f[i][j]==f[i+1][j+1])p[i][j]=(p[i][j]+p[i+1][j+1])%mod;
                        if(b[i][j]!='E')f[i][j]+=b[i][j]-'0';
                    }
                    else if(i+1<n){
                        f[i][j]=f[i+1][j]+b[i][j]-'0';

                        p[i][j]=p[i+1][j];
                    }else if(j+1<n){
                        f[i][j]=f[i][j+1]+b[i][j]-'0';
                        p[i][j]=p[i][j+1];
                    }
                }
                if(b[i][j]=='S'||b[i][j]=='X'){
                    b[i][j]='0';
                }
            }
        }
        if(p[0][0]==0)return {0,0};
        return  {f[0][0],p[0][0]};
    }
	/* //判断是否能到达0,0这个点，但是后面发现没有必要
    int idx[3]={-1,-1,0};
    int idy[3]={0,-1,-1};
    bool k[110][110];
    bool bfs(vector<string>& b){
        int n=b.size();
        queue<pair<int,int>>q;
        q.push({n-1,n-1});
        while(q.size()){
            auto w=q.front();q.pop();
            int x=w.first,y=w.second;
            for(int i=0;i<3;i++){
                int xx=x+idx[i];
                int yy=y+idy[i];
                if(xx>=0&&xx<n&&yy>=0&&yy<n&&!k[xx][yy]&&(b[xx][yy]>='0'&&b[xx][yy]!='X')){
                    k[xx][yy]=1;
                    
                    if(xx==0&&yy==0) return true;
                    q.push({xx,yy});
                }
            }
        }
        return false;
    }
	*/
};
//407.接雨水II

给你一个 m x n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度，请计算图中形状最多能接多少体积的雨水。

 

示例：

给出如下 3x6 的高度图:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

返回 4 。

class Solution {
public:
    int trapRainWater(vector<vector<int>>& h) {
        priority_queue< pair<int,pair<int,int>> ,vector< pair<int,pair<int,int>> >,greater< pair<int,pair<int,int>> > >pq; //存高度，位置
        int n=h.size();
        int m=h[0].size();
        int id[]={-1,0,1,0,-1};
        bool visit[1000][1000];
        memset(visit,0,sizeof visit);
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i==0||i==n-1||j==0||j==m-1){
                    pq.push({h[i][j],{i,j}});
                    visit[i][j]=true;
                }
            }
        }
        int res=0;
        while(pq.size()){
            auto w=pq.top();
            pq.pop();
            int k=w.first;
            int x=w.second.first;
            int y=w.second.second;
            
            for(int i=0;i<4;i++){
                int xx=x+id[i];
                int yy=y+id[i+1];
                if(xx>=0&&xx<n&&yy>=0&&yy<m&&!visit[xx][yy]){  //因为每次出来的都是最小高度h，所以如果他周围的高度比h低，那就肯定可以积水到h,那加上差值，然后把高度调到h高度，
                    if(k>h[xx][yy])res+=k-h[xx][yy];
                    visit[xx][yy]=true;
                    h[xx][yy]=max(k,h[xx][yy]);
                    pq.push({h[xx][yy],{xx,yy}});
                }
            }
        }
        return res;
    }
};



接雨水I中，我们维护了左右两个最高的墙，那么在这里，就是维护周围一个圈，用堆来维护周围这一圈中的最小元素。为什么是维护最小的元素不是最大的元素呢，因为木桶原理呀。这个最小的元素从堆里弹出来，和它四个方向的元素去比较大小，看能不能往里灌水，怎么灌水呢，如果用方向就比较复杂了，我们可以用visited数组来表示哪些遍历过，哪些没遍历过。如果当前弹出来的高度比它周围的大，那就是能灌水，把下一个柱子放进去的时候，放的高度要取两者较大的，也就是灌水后的高度，而不是它原来矮的高度了，如果不能灌水，继续走

Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]
就拿这个例子来说，第一圈，最小值是1（遍历时候标记为访问过），1从堆里弹出来，比如弹出来左上角的1，它下方的3没有被访问过，3入堆，然后继续弹最小的，然后放进去，比如说，我此时弹出来一个3（坐标[1,0]），它能向右边2(坐标[1,1])灌水，那这边就可以统计了，然后我们要插入2(坐标[1,1])这个位置，但是插入的时候，要记得你得是插入的高度得是灌水后的高度，而不是原来的高度了

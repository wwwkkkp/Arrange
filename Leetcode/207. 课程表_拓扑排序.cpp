/*207. 课程表
现在你总共有 n 门课需要选，记为 0 到 n-1。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]

给定课程总量以及它们的先决条件，判断是否可能完成所有课程的学习？

示例 1:

输入: 2, [[1,0]] 
输出: true
解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。
示例 2:

输入: 2, [[1,0],[0,1]]
输出: false
解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。
说明:

输入的先决条件是由边缘列表表示的图形，而不是邻接矩阵。详情请参见图的表示法。
你可以假定输入的先决条件中没有重复的边。
提示:

这个问题相当于查找一个循环是否存在于有向图中。如果存在循环，则不存在拓扑排序，因此不可能选取所有课程进行学习。
通过 DFS 进行拓扑排序 - 一个关于Coursera的精彩视频教程（21分钟），介绍拓扑排序的基本概念。
拓扑排序也可以通过 BFS 完成。


*/

//BFS+入度表  拓扑排序

typedef struct GNode *ProToGNode;
struct GNode{
    int val;
    ProToGNode next;
};

typedef struct GHead *ProToGHead;
struct GHead{
    int val;
    ProToGNode G;
};
class Solution {
public:
    ProToGHead CreateGHead(int n){
        ProToGHead s=(ProToGHead)malloc(sizeof(struct GHead));
        s->G=(ProToGNode)malloc(n*sizeof(struct GHead));
        s->val=n;
        for(int i=0;i<n;i++)
            s->G[i].next=NULL;
        return s;
    }
    bool canFinish(int num, vector<vector<int>>& pre) {
        if(!pre.size()) return true;
        ProToGHead s=CreateGHead(num);
        int x=pre.size();
        int y=pre[0].size();
        
        int dis[num];
        memset(dis,0,sizeof(dis));
        queue<int> q;
        int juice=0;
        for(int i=0;i<x;i++){
            for(int j=y-2;j>=0;j--){
                ProToGNode t=(ProToGNode)malloc(sizeof(struct GNode));
                t->val=pre[i][j];
                t->next=NULL;
                t->next=s->G[pre[i][j+1]].next;
                s->G[pre[i][j+1]].next=t;
                dis[pre[i][j]]++;  //入度表
            }
        }
        for(int i=0;i<num;i++){
            if(!dis[i])
                q.push(i);
        }
        while(!q.empty()){
            int m=q.front();
            q.pop();
            juice++;
            for(ProToGNode n=s->G[m].next;n!=NULL;n=n->next){
                dis[n->val]--;
                if(!dis[n->val])
                    q.push(n->val);
            }
        }
        if(juice==num)
            return true;
        return false;
    }
};



//DFS

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
          //拓扑排序
        //使用标志数组进行访问判别
        //标志数组如果是1/0的，则会产生重复遍历的消耗
        //如果是-1/0/1的，就可以避免重复计算。
        //1：从当前结点开始的拓扑是无环的
        //0：还未遍历过
        //-1：正在遍历
        vector<int> flag(numCourses,0);//标志
        vector<vector<int> > tmp(numCourses);
        if(prerequisites.empty()) return true; 
        for(int i=0;i<prerequisites.size();i++)
        {
            tmp[prerequisites[i][0]].push_back(prerequisites[i][1]);//对于该课程来说需要修的课，prerequisites[0].size()=2;
        }
        bool ans=true;;
        for(int i=0;i<numCourses;i++)
        {
            ans=ans&&dfs(i,flag,tmp);
        }
        return ans;
    }
	
    bool dfs(int i,vector<int> &flag,vector<vector<int> > &tmp)
    {
        if(flag[i]==-1)//回路.有环
        {
            return false;
        }
        if(flag[i]==1)
        {
            return true;//可以确定从该结点出发没有回路   
        }
        //第一次访问
        flag[i]=-1;//正在访问                  //这里相当于标记，访问过的结点就置-1，如果后面访问到结点是-1的，就证明有环；
        for(int j=0;j<tmp[i].size();j++)
        {
            if(dfs(tmp[i][j],flag,tmp))
            {
                continue;//这个地方没有回路
            }
            return false;
        }
        flag[i]=1;//该结点出去的每一个结点都访问完了，没有回路
        return true;
    }
};



//14.2.1255. 医院设置 


设有一棵二叉树（如下图），其中圈中的数字表示结点中居民的人口，圈边上数字表示结点编号。
现在要求在某个结点上建立一个医院，使所有居民所走的路程之和为最小，同时约定，相邻结点之间的距离为 1。
就本图而言，若医院建在 1处，则距离和为 4+12+2×20+2×40=136；若医院建在 3处，则距离和为 4×2+13+20+40=81。
 
输入格式
第一行一个整数 n，表示树的结点数。接下来的 n行每行描述了一个结点的状况，其中第 i行，描述结点 i的具体状况，包含三个整数，整数之间用空格（一个或多个）分隔，
其中：第一个数为居民人口数；第二个数为左链接结点编号，为 0表示无链接；第三个数为右链接结点编号，为 0表示无链接。
树的结点编号从 1到 n。输出格式一个整数，表示最小距离和。数据范围1≤n≤100，
每个地点的居民人口数均不超过100。
输入样例：
5
13 2 3
4 0 0
12 4 5
20 0 0
40 0 0
输出样例：
81


//这道题的核心是邻接表的数组表示方法
#include<iostream>
#include<cstring>

using namespace std;

const int N=10000;

int n;
int h[N],e[N],ne[N],idx,w[N];
int dist[N];

void add(int a,int b){//原理见 https://www.cnblogs.com/codingmengmeng/p/5645073.html ,3.3也是相关题
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

void dfs(int t,int s,int pre){
    if(h[t]==-1)return ;
    for(int i=h[t];~i;i=ne[i]){
        int j=e[i];
        if(j!=pre){
            dist[j]=s+1;
            dfs(j,s+1,t);
        }
    }

}

int main(){
    int a,b,c;
    memset(h,-1,sizeof h);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a>>b>>c;
        w[i]=a;
        if(b) add(i,b),add(b,i);
        if(c) add(i,c),add(c,i);
    }
    int p=1e9;
    for(int i=1;i<=n;i++){
        dfs(i,0,0);
        int m=0;
        for(int j=1;j<=n;j++){
            if(j!=i){
                m+=dist[j]*w[j];
            }
        }
        p=min(p,m);
    }
    cout<<p<<endl;
    return 0;
}
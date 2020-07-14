
//14.1.1254. 找树根和孩子 

给定一棵树，输出树的根root，孩子最多的结点max以及他的孩子。
输入格式
第一行：n，m，表示树的节点数和边数。
以下m行：每行两个结点x和y，表示y是x的孩子。
输出格式
第一行：树根：root；
第二行：孩子最多的结点max；
第三行：max的孩子（按编号由小到大输出）。
数据范围
1≤n≤100
m=n−1
1≤x,y≤1000
,
数据保证孩子最多的结点唯一。
输入样例1：
8 7
4 1
4 2
1 3
1 5
2 6
2 7
2 8
输出样例1：
4
2 
6 7 8
输入样例2：
10 9
661 43
43 270
43 155
155 691
661 201
661 768
661 889
43 302
201 98
输出样例2：
661
661
43 201 768 889 

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int N=110,M=1100;

int n,m;
bool f[M];  //第i个结点有没有父结点
vector<vector<int>>v(M,vector<int>());  //各个结点的子结点

int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        v[a].push_back(b);
        f[b]=true;
    }
    int root;   //存放根结点，根结点的特点就是没有父结点，
    int res=-1;//存放结点最多的点
    for(int i=0;i<M;i++){
        
        if(v[i].size()>v[res].size())
            res=i;

        if(v[i].size()&&!f[i])//有子结点但是没有父结点
            root=i;
    }

    cout<<root<<endl;
    cout<<res<<endl;
    sort(v[res].begin(),v[res].end());
    for(int i=0;i<v[res].size();i++){
        cout<<v[res][i]<<" ";
    }
    
    cout<<endl;
    return 0;
}



//图有三种表示：矩阵，链表，vector， 


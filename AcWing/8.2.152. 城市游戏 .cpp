//8.2.152. 城市游戏 

有一天，小猫rainbow和freda来到了湘西张家界的天门山玉蟾宫，玉蟾宫宫主蓝兔盛情地款待了它们，并赐予它们一片土地。
这片土地被分成N*M个格子，每个格子里写着’R’或者’F’，R代表这块土地被赐予了rainbow，F代表这块土地被赐予了freda。
现在freda要在这里卖萌。。。它要找一块矩形土地，要求这片土地都标着’F’并且面积最大。
但是rainbow和freda的OI水平都弱爆了，找不出这块土地，而蓝兔也想看freda卖萌（她显然是不会编程的……），所以它们决定，如果你找到的土地面积为S，它们将给你3*S两银子。
输入格式
第一行包括两个整数N,M，表示矩形土地有N行M列。
接下来N行，每行M个用空格隔开的字符’F’或’R’，描述了矩形土地。
每行末尾没有多余空格。
输出格式
输出一个整数，表示你能得到多少银子，即(3*最大’F’矩形土地面积)的值。
数据范围
1≤N,M≤1000
输入样例：
5 6
R F F F F F
F F F F F F
R R R F F F
F F F F F F
F F F F F F
输出样例：
45  (左右边的3行)



//这道题是上一题 直方图中最大矩形 的升级版，对每一行求最大值，如例题中第一行相当于是0 1 1 1 1 1，第二行相当于是1 2 2 2 2 2，一个F相当于高度1，就看这个数上面有几个F
#include<iostream>
using namespace std;

const int N=1010;
int n,m;

int s[N][N];  //s[i][j]是直方图集合，表示第i行第j列的高度是多少
int q[N],l[N],r[N];

int work(int h[]){ //和上一题的函数体一样
    h[0]=h[m+1]=-1;
    
    int tt=0;
    q[tt]=0;
    for(int i=1;i<=m;i++){
        while(h[q[tt]]>=h[i])tt--;
        l[i]=q[tt];
        q[++tt]=i;
    }
    tt=0;
    q[tt]=m+1;//单调栈开始的位置
    for(int i=m;i>=1;i--){
        while(h[q[tt]]>=h[i])tt--;//注意这里是等号，相同的数也要延伸
        r[i]=q[tt];
        q[++tt]=i;
    }
    int res=0;
    for(int i=1;i<=m;i++)
        res=max(res,h[i]*(r[i]-l[i]-1));
    return res;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='R') s[i][j]=0;
            else s[i][j]=s[i-1][j]+1;
        }
    }
    int res=0;
    for(int i=1;i<=n;i++){
        res=max(res,work(s[i]));
    }
    cout<<res*3<<endl;
    return 0;
}
//35.145. 超市 

超市里有N件商品，每件商品都有利润pi和过期时间di,每天只能卖一件商品，过期商品不能再卖。
求合理安排每天卖的商品的情况下，可以得到的最大收益是多少。
输入格式
输入包含多组测试用例。
每组测试用例，以输入整数N开始，接下来输入N对pi和di，分别代表第i件商品的利润和过期时间。
在输入中，数据之间可以自由穿插任意个空格或空行，输入至文件结尾时终止输入，保证数据正确。
输出格式
对于每组产品，输出一个该组的最大收益值。
每个结果占一行。
数据范围
0≤N≤10000
,
1≤pi,di≤10000
输入样例：
4  50 2  10 1   20 2   30 1

7  20 1   2 1   10 3  100 2   8 2
   5 20  50 10
输出样例：
80
185




// 典型贪心算法
#include<iostream>
#include<algorithm>
#include<queue>

#define x first
#define y second

using namespace std;
typedef pair<int,int> pii;
const int N=10010;
int n;

bool coms(const pii &a,const pii &b){  //重载排序，以第二个数作为排序对象
    if(a.y<b.y)
        return true;
    else
        return false;
}

int main(){
    while(cin>>n){
        vector<pii>v(n);
        for(int i=0;i<n;i++)
            cin>>v[i].x>>v[i].y;
            
        sort(v.begin(),v.end(),coms); //按天数从小大排列
        
        priority_queue<int,vector<int>,greater<int>>pq;  //最小堆
        for(int i=0;i<n;i++){
            pq.push(v[i].x);  //一次放入优先队列，如果当前队列里面的数大于当前数的天数，就要舍弃一个最小利润
            if(pq.size()>v[i].y)pq.pop();
        }
        
        int res=0;
        while(pq.size()){
            int m=pq.top();
            pq.pop();
            res+=m;
        }
        cout<<res<<endl;
    }
}
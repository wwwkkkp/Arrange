//5.4 106. 动态中位数 


依次读入一个整数序列，每当已经读入的整数个数为奇数时，输出已读入的整数构成的序列的中位数。
输入格式
第一行输入一个整数P，代表后面数据集的个数，接下来若干行输入各个数据集。
每个数据集的第一行首先输入一个代表数据集的编号的整数。
然后输入一个整数M，代表数据集中包含数据的个数，M一定为奇数，数据之间用空格隔开。
数据集的剩余行由数据集的数据构成，每行包含10个数据，最后一行数据量可能少于10个，数据之间用空格隔开。

输出格式
对于每个数据集，第一行输出两个整数，分别代表数据集的编号以及输出中位数的个数（应为数据个数加一的二分之一），数据之间用空格隔开。
数据集的剩余行由输出的中位数构成，每行包含10个数据，最后一行数据量可能少于10个，数据之间用空格隔开。
输出中不应该存在空行。
数据范围
1≤P≤1000
,
1≤M≤9999
输入样例：
3 
1 9 
1 2 3 4 5 6 7 8 9 
2 9 
9 8 7 6 5 4 3 2 1 
3 23 
23 41 13 22 -3 24 -31 -11 -8 -7 
3 5 103 211 -311 -45 -67 -73 -81 -99 
-33 24 56
输出样例：
1 5
1 2 3 4 5
2 5
9 8 7 6 5
3 12
23 23 22 22 13 3 5 5 3 -3 
-7 -3



//动态中位数的原理就是维护两个堆，一个最大堆，一个最小堆，中位1数存在最大堆的堆顶，然后通过堆中元素个数来输出，转换

#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int N=1010,M=10010;

int n,m;
int a[M];

int main(){
    cin>>n;

    while(n--){
        int k;
        cin>>k>>m;
        for(int i=0;i<m;i++)
            cin>>a[i];
        cout<<k<<" "<<(m+1)/2<<endl;
        priority_queue<int> maxq;
        priority_queue<int ,vector<int>,greater<int>> minpq;
        int v=0;
        for(int i=0;i<m;i++){
            if(maxq.size()==0&&minpq.size()==0) maxq.push(a[i]);
            else if(a[i]>maxq.top()) minpq.push(a[i]);  //选择放在哪个堆中，
            else maxq.push(a[i]);
            
            
            if(maxq.size()==1+minpq.size()) {//最大堆比最小堆的数量多一个，说明目前是奇数。。最大堆的堆顶就是中位数
                cout<<maxq.top()<<" ";
                v++;
            }
            else if(maxq.size()<minpq.size()) { //最小堆的大小大于最大堆的大小
                int r=minpq.top();
                minpq.pop();
                maxq.push(r);
                cout<<maxq.top()<<" ";
                v++;
            }
            else if(maxq.size()==minpq.size()+2){ //最大堆比最小堆的数量多两个，要转换一下
                int r=maxq.top();
                maxq.pop();
                minpq.push(r);
            }
            if(v%10==0&&i%2==0)cout<<endl;//因为是每十个换行，所以需要判断一下  i%2==0：只有奇数的时候才输出，偶数是不输出的
        }
        if(v%10)cout<<endl;    //如果上一个输出的中位数刚好10个，这里就不换行了，因为已经换过了
    }
    return 0;
}


//模板
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        int id, n;
        scanf("%d%d", &id, &n);
        printf("%d %d\n", id, (n + 1) / 2);

        priority_queue<int> down;     //最大堆
        priority_queue<int, vector<int>, greater<int>> up;   //最小堆

        int cnt = 0;
        for (int i = 0; i < n; i ++ )
        {
            int x;
            scanf("%d", &x);

            if (down.empty() || x <= down.top()) down.push(x);
            else up.push(x);

            if (down.size() > up.size() + 1) up.push(down.top()), down.pop();
            if (up.size() > down.size()) down.push(up.top()), up.pop();   //两个堆的数量关系只能是最大堆的个数和最小堆的个数相等，或者比最小堆大1

            if (i % 2 == 0)
            {
                printf("%d ", down.top());
                if ( ++ cnt % 10 == 0) puts("");
            }
        }

        if (cnt % 10) puts("");
    }

    return 0;
}

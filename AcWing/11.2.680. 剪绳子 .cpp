
//11.2.680. 剪绳子 

有N根绳子，第i根绳子长度为Li，现在需要M根等长的绳子，你可以对N根绳子进行任意裁剪（不能拼接），请你帮忙计算出这M根绳子最长的长度是多少。

输入格式
第一行包含2个正整数N、M，表示原始绳子的数量和需求绳子的数量。
第二行包含N个整数，其中第 i 个整数Li表示第 i 根绳子的长度。

输出格式
输出一个数字，表示裁剪后最长的长度，保留两位小数。
数据范围
1≤N,M≤100000
0<Li<109
输入样例：
3 4
3 5 4
输出样例：
2.50
样例解释
第一根和第三根分别裁剪出一根2.50长度的绳子，第二根剪成2根2.50长度的绳子，刚好4根。


//二分：一般有二分，就需要出现单调性，在这个题中，分的长度越长，分的根数越短，有单调性，单调递减
//初始状态，le=0,ri=1e9，如果mid=(le+ri)/2,mid长度能分2根，目标是4根，则需要把ri=mid，减小分的长度，以增加根数，反之亦然

#include<iostream>

using namespace std;

const int N=100010,M=1e9;

int n,m;
int a[N];

bool check(double u){
    int k=0;
    for(int i=0;i<n;i++){
        k+=a[i]/u;
    }
    if(k>=m)return true;//注意这里：因为求得是最长分的长度，所以这里是>=，如果要求是最短分的长度，就是>；
    else return false;
}

int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++)
        cin>>a[i];
    double le=0,ri=M;
    while(ri-le>=1e-4){ //如果精度保证是小数点后k位，一般要计算到小数点后k+2位
        double mid=(le+ri)/2;
        if(check(mid)) le=mid;//分的多了就是增加le，
        else ri=mid;//分的少了就减少ri
    }
    printf("%.2f\n",ri);
    return 0;
}

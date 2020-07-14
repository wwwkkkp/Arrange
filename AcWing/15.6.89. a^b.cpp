
//15.6.89. a^b 

求 a的 b次方对 p取模的值。

输入格式
三个整数 a,b,p,在同一行用空格隔开。
输出格式
输出一个整数，表示a^b mod p的值。

数据范围
0≤a,b,p≤109
数据保证 
p≠0

输入样例：
3 2 7
输出样例：
2



#include<iostream>

using namespace std;

int main(){
    long long a,b,p;
    cin>>a>>b>>p;
    long long res=1;
    if(!b){
        cout<<1%p<<endl;
        return 0;
    }
    while(b>0){ //看b的哪些位是1，是1的话就乘上a的这一位次方，
        if(b&1) res=(res*(a%p))%p;
        a=(a%p)*(a%p);
        b=b>>1;
    }
    cout<<res<<endl;
    return 0;
}
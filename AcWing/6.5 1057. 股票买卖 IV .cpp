//6.5 1057. 股票买卖 IV 

给定一个长度为 N的数组，数组中的第 i个数字表示一个给定股票在第 i天的价格。
设计一个算法来计算你所能获取的最大利润，你最多可以完成 k笔交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。一次买入卖出合为一笔交易。
输入格式
第一行包含整数 N和 k，表示数组的长度以及你可以完成的最大交易数量。
第二行包含 N个不超过 10000的正整数，表示完整的数组。

输出格式
输出一个整数，表示最大利润。
数据范围
1≤N≤10^5
1≤k≤100

输入样例1：
3 2
2 4 1
输出样例1：
2
输入样例2：
6 2
3 2 6 5 0 3
输出样例2：
7
样例解释
样例1：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4) 的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
样例2：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。共计利润 4+3 = 7.



//状态机问题
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;
const int N=100010,K=110;
int n,k;
int a[N],f[N][K][2]; //f的意思是前i天完成j笔交易，手上是否持股，的最大收益
//按照手上是否持股，可分为两种状态，持股(1)和不持股(0),持股状态(f[i][j][1])只能是(前一天持股，当天不做变化(f[i-1][j][1]))和(前一天不持股，当天买入(f[i-1][j][0]-a[i]))两种情况转变而来;   不持股(f[i][j][0])只能是(前一天持股，当天卖出(f[i-1][j-1][1]+a[i]))和(前一天不持股，当天不做变化(f[i][j][0]))两种情况转变而来。所以只需要求这些情况的最大值即可
int main(){
   cin>>n>>k;
   for(int i=1;i<n;i++)cin>>a[i];
   memset(f,-0x3f,sizeof(f)); //注意这个题的初始值
   f[0][0][0]=0;
   
   for(int i=1;i<=n;i++){
       for(int j=0;j<=k;j++){
           f[i][j][0]=f[i-1][j][0];
           if(j)f[i][j][0]=max(f[i][j][0],f[i-1][j-1][1]+a[i]);
           f[i][j][1]=max(f[i-1][j][1],f[i-1][j][0]-a[i]);
       }
   }
   int res=0;
   for(int i=0;i<=k;i++){
       res=max(f[n][i][0],res); //因为是最多完成k比交易，所以求这些交易中的最大值
   }
   cout<<res<<endl;
   return 0;
}


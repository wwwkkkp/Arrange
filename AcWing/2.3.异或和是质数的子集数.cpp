//9.1454. 异或和是质数的子集数 
给出 n个互不相同的正整数。
问存在多少个子集，使得子集中所有数的异或和是质数。
由于答案可能很大，请你输出对 109+7取模后的结果。
输入格式
第一行包含整数 n
第二行包含 n个正整数。

输出格式
输出一个整数，表示满足条件的子集数量对 109+7取模后的结果。
数据范围
1≤n≤5000
1≤给定正整数 ≤5000。

输入样例：
3
1 2 3
输出样例：
4

//背包问题，在一个范围内选择一堆数(个数不确定)的结果

#include<iostream>
#include<algorithm>

using namespace std;
const int N=5010,M=8192,MOD=1e9+7;  //注意：因为N最大是5000，所以整个集合取异或的最大值是8191(2^13-1),
int f[N][M];  //dp[i][j]：前i个数中，选择一堆数，结果为j的集合的个数

int n;
int a[N];

bool IsZ(int i){
	for(int k=2;k*k<=i;k++){  //注意，检测质数条件必须是k*k<=i,如果不加等号要漏掉9这些数字
		if(i%k==0)
			return false;
	}
	return true;
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	dp[0][0]=1;
    dp[1][a[1]]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<M;j++){
			dp[i][j]=(dp[i-1][j]+dp[i-1][j^a[i]])%MOD;//前i个数中异或为j的集合数,等于，不选第i个数dp[i-1][j]，选第i个数dp[i-1][j^a[i]]，j^a[i]就是j去掉a[i]后剩下的值的异或值
		}
	}
	int res=0;
	for(int i=2;i<M;i++){
		if(IsZ(i))
			res=(res+dp[n][i])%MOD;
	}
	cout<<res<<endl;
	return 0;
}



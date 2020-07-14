//10.797. 差分 

输入一个长度为n的整数序列。
接下来输入m个操作，每个操作包含三个整数l, r, c，表示将序列中[l, r]之间的每个数加上c。
请你输出进行完所有操作后的序列。
输入格式
第一行包含两个整数n和m。
第二行包含n个整数，表示整数序列。
接下来m行，每行包含三个整数l，r，c，表示一个操作。
输出格式
共一行，包含n个整数，表示最终序列。
数据范围 
1≤n,m≤100000,
1≤l≤r≤n,
−1000≤c≤1000,
−1000≤整数序列中元素的值≤1000
输入样例：
6 3
1 2 2 1 2 1
1 3 1
3 5 1
1 6 1
输出样例：
3 4 5 3 4 2



//差分数组是前缀和的逆运算，
#include<iostream>
#include<algorithm>

using namespace std;
int n,m;
const int N=100010;
int a[N];
int b[N];

void CF(int l,int r,int c){  //差分数组的性质：l和r之间的数加上c,差分数组就是计算公式如下
	b[l]+=c;    //因为b是a的前缀和，那b某个数+c,那相当于a对应这一位后面的数都+c
	b[r+1]-=c;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	b[1]=a[1];
	for(int i=2;i<=n;i++){
		b[i]=a[i]-a[i-1]; //差分数组b[i]，a[i]=b[0]+b[1]+...b[i];，a数组就是b数组的前缀和
	}


	for(int i=0;i<m;i++){
		int l,r,c;
		cin>>l>>r>>c;
		CF(l,r,c);
	}

	a[1]=b[1];
	cout<<a[1]<<" ";
	for(int i=2;i<=n;i++){
	    a[i]=a[i-1]+b[i];
		cout<<a[i]<<" ";
	}
	cout<<endl;
	return 0;
}
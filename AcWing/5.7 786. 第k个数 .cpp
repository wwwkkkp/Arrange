//5.7 786. 第k个数 


给定一个长度为n的整数数列，以及一个整数k，请用快速选择算法求出数列的第k小的数是多少。
输入格式
第一行包含两个整数 n 和 k。
第二行包含 n 个整数（所有整数均在1~10^9范围内），表示整数数列。
输出格式
输出一个整数，表示数列的第k小数。
数据范围
1≤n≤100000
，
1≤k≤n
输入样例：
5 3
2 4 1 5 3
输出样例：
3


//stl标准库做法
#include<iostream>
#include<algorithm>

using namespace std;
const int N=100010;

int n,m;
int a[N];

int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++)cin>>a[i];
	
    nth_element(a,a+m-1,a+n);//这个函数是将数组第m-1个数大的数放在m-1的位置上，中间的那个数相当于索引号
	
    cout<<a[m-1]<<endl;
    return 0;
}



//快排方法
#include<iostream>
#include<algorithm>

using namespace std;
const int N = 100010;

int n, m;
int a[N];

void merge(int le, int ri) {
	if (le == ri) { cout << a[le] << endl; return; }
	int cnt = (a[le] +a[ ri]) / 2;
	int i = le - 1, j = ri + 1;
	while (i < j) {
		while (a[++i] < cnt);
		while (a[--j] > cnt);
		if (i < j)swap(a[i], a[j]);
		else break;
	}
	if (j >= m-1) merge(le, j );//注意 快排的分界线是以j为准的，而且a[j]是小于比较值cnt的
	else if (j < m-1) merge(j + 1, ri);

}
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)cin >> a[i];

	merge(0, n - 1);
	return 0;
}

//7.1 1572. 递归实现指数型枚举 II 

给定一个长度为 n的可包含重复数字的序列，从中随机选取任意多个数字，输出所有可能的选择方案。
输入格式
第一行包含一个整数 n，表示序列长度。
第二行包含 n个正整数。
输出格式
每行输出一种方案。
同一行内的数必须升序排列，相邻两个数用恰好1个空格隔开。
对于没有选任何数的方案，输出空行。
本题有自定义校验器（SPJ），各行（不同方案）之间的顺序任意。
数据范围1≤n≤15,
序列内所有元素均不大于 n。
输入样例：
3
1 2 2
输出样例：

1
2
1 2
2 2
1 2 2

#include<iostream>
#include<algorithm>

using namespace std;
const int N=20;

int n;
int a[N];
bool b[N]; //某个数是否选择

void dfs(int k){
    if(k==n){
        for(int i=0;i<n;i++)
            if(b[i])
                cout<<a[i]<<" ";
        cout<<endl;
        return ;
    }
    b[k]=false;
    dfs(k+1);
    b[k]=true;
    while(k+1<n&&a[k+1]==a[k])k++; //这里要注意一下，这里的这个和6.3排序中的相对应的句子有不同，因为这里了涉及到相同的数选几个的问题，而6.3中的是该数后面相同的数不能选，
	//这里是不能把b[k]回溯成false，由1 2 2举例，第一次执行的时候选的2是最后一个2，执行完之后，第二次选择的第一个2，因为没有回溯，所以两个2都选了，所以这里这个语句选的是：相同的数中，选后几个的问题，下面的例子选的前几个的问题，可以参考
    dfs(k+1);
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    sort(a,a+n);
    dfs(0);
    return 0;
}



#include<iostream>
#include<algorithm>

using namespace std;
const int N=20;

int n;
int a[N];
bool b[N]; //某个数是否选择

void dfs(int k){
	if(k==n){
		for(int i=0;i<n;i++)
			if(b[i])
				cout<<a[i]<<" ";
		cout<<endl;
		return ;
	}
	int u=k;
	while(u<n&&a[u]==a[k]) u++;  //注意这里有点不同
	
	dfs(u);
	for(int i=k;i<u;i++){
		b[i]=true;
		dfs(u);
	}
	for(int i=k;i<u;i++)b[i]=false;  //注意这里要回溯，因为如果不回溯，这个段的前面的数改变的时候，这个段都为true
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    sort(a,a+n);
    dfs(0);
    return 0;
}



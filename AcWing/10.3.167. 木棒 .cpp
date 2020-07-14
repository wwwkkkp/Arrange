
//10.3.167. 木棒 
乔治拿来一组等长的木棒，将它们随机地砍断，使得每一节木棍的长度都不超过50个长度单位。
然后他又想把这些木棍恢复到为裁截前的状态，但忘记了初始时有多少木棒以及木棒的初始长度。
请你设计一个程序，帮助乔治计算木棒的可能最小长度。
每一节木棍的长度都用大于零的整数表示。
输入格式
输入包含多组数据，每组数据包括两行。
第一行是一个不超过64的整数，表示砍断之后共有多少节木棍。
第二行是截断以后，所得到的各节木棍的长度。
在最后一组数据之后，是一个零。
输出格式
为每组数据，分别输出原始木棒的可能最小长度，每组数据占一行。
数据范围
数据保证每一节木棍的长度均不大于50。
输入样例：
9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0
输出样例：
6
5

//暴搜 精髓在剪枝

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int N = 65;

int n;
int a[N];
bool b[N];
int sum = 0, ml = 0;

bool dfs(int k,int u ,int c,int t){ //如果拼成长度为k的木棍，开始拼第u根，当前拼的这根目前长度是c，从第t个木棒开始枚举选择还是不选择，最终返回能不能成功
    if(u*k==sum)return true;  //已经拼完了，返回真
    if(c==k) return dfs(k,u+1,0,0); //拼完当前根，开始拼下一根
    for(int i=t;i<n;i++){  //从第t个数开始选择
        if(b[i])continue;
        int r=a[i];
        if(c+r<=k){
            b[i]=true;
            if(dfs(k,u,c+r,t+1))return true; //当第t个数被选上以后，就顺次递归第t+1个数，如果选择该数不能成功，则放弃这个数，继续选择下一个数
            b[i]=false;
        }
		//执行到这里都是dfs(k,u,c+r,t+1)返回假的
        if(!c||c+r==k)return false;//因为是从大到小开始选择，执行到这里，c=0说明目前可选的最大的那个数不能选，那k就不正确，返回假，c+l=k:当前根拼完了，但是返回假，说明k不正确，
		
        int j=i;//循环执行到这里，说明第t个数是没有选，那后面和第t个数相同的数都不能选
        while(j<n&&r==a[j])j++;
        i=j-1;
    }
    return false;
}



int main() {
	while (cin >> n, n) {
    	sum = 0;
		ml = 0;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			sum += a[i];
			ml = max(ml, a[i]);
		}

		sort(a, a+n);
		reverse(a,a+n);
        memset(b, false, sizeof b);
		for (int i = ml; i <= sum; i++) {
			if (sum%i==0&&dfs(i,0, 0,0)) {
				cout << i << endl;
				break;
			}
		}
	}
}
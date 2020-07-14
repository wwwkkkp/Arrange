//20.1259. 二叉树遍历 

//要想恢复二叉树，必须有中序遍历，然后加上一个前序或后序或层序，或者是只有一个带null的中序也可以

树和二叉树基本上都有先序、中序、后序、按层遍历等遍历顺序，给定中序和其它一种遍历的序列就可以确定一棵二叉树的结构。
假定一棵二叉树一个结点用一个字符描述，现在给出中序和按层遍历的字符串，求该树的先序遍历字符串。
输入格式
两行，每行是由大写字母组成的字符串（一行的每个字符都是唯一的），分别表示二叉树的中序遍历和按层遍历的序列。
输出格式
一行，表示二叉树的先序序列。
数据范围
输入字符串的长度均不超过26。
输入样例：
DBEAC
ABCDE
输出样例：
ABDEC


//层序+中序推出二叉树

//方法：遍历 层序序列，然后在中序序列中找打位置，看左右儿子是否存在，
样例：
1.层序遍历第一个数A，在中序中的位置是3，左边有数，并且没有被访问过，所以有左儿子B，右边有数，并且没有被访问过，所有有右儿子C，
2.第二个遍历的是B，在中序中的位置是1，左右两边都有数，并且没有被访问过，所以B左右儿子都有，D和E，
3.因为层序中最后一个数都被确认了，所以遍历结束


#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<cstring>

using namespace std;
struct node{
	char val;
	node* left;
	node* right;
	node(int n):val(n),left(NULL),right(NULL){}
};
string out;

void dfs(node *q){
	if(q==NULL)
		return ;
		
	out+=q->val;
	dfs(q->left);
	dfs(q->right);
}


int main(){
	string smid,sfl;
	cin>>smid>>sfl;
	
	unordered_map<char,int>up;
	int v[30]={0};
	
	int n=smid.size();
	for(int i=0;i<n;i++)
		up[smid[i]]=i;   //用哈希表查找在中序的位置，更快
	
	node* q[30];
	q[0]=new node(sfl[0]);

	for(int i=0,j=1;j<n;){  //   i代表当前访问的层的起点  ，  j代表下一层访问的层的起点
	
		for(int end=j;i<j;i++){   //这个方法是按照层序遍历重建的，中序遍历的作用是判断当前有没有左右儿子
		    
			int p=up[sfl[i]];
			v[p]=1;
			if( p-1>=0 && v[p-1]==0 ){  //判断有没有左儿子
				q[i]->left=new node(sfl[j]);
				q[j++]=q[i]->left;  //把整个树放到队列q中去
				
			}
			if( p+1<n && v[p+1]==0 ){   //判断有没有右儿子
				q[i]->right=new node(sfl[j]);
				q[j++]=q[i]->right;
			}	
			
		}		
	}	
	dfs(q[0]);
	cout<<out<<endl;
	return 0;	
}


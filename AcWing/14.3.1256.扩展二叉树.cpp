



//14.3.1256.扩展二叉树

由于先序、中序和后序序列中的任一个都不能唯一确定一棵二叉树，所以对二叉树做如下处理，将二叉树的空结点用·补齐，如图所示。
我们把这样处理后的二叉树称为原二叉树的扩展二叉树，扩展二叉树的先序和后序序列能唯一确定其二叉树。
 
现给出扩展二叉树的先序序列，要求输出原二叉树中序和后序序列。
输入格式
扩展二叉树的先序序列。
输出格式
输出其中序和后序序列。
数据范围
原二叉树的结点数不超过26，且均由大写字母表示。
输入样例：
ABD..EF..G..C..
输出样例：
DBFEGAC
DFGEBCA

/**简单的说就是给出带null的前序遍历，求这颗树*/

#include<iostream>

using namespace std;

int n,k;
string pre,mid,ba;

void dfs(){
    if(k==n)return;
    char c=pre[k++];  //k是全局变量，
    
    if(c=='.')return ;
    dfs();  //左子树
    mid+=c;  //在左子树求出来的情况下，添加当前元素，就是中序遍历
    dfs();  //右子树
    ba+=c;  //后序遍历
    
}

int main(){
    cin>>pre;
    n=pre.size();
    k=0;
    dfs();
    cout<<mid<<endl<<ba<<endl;
    return 0;
}
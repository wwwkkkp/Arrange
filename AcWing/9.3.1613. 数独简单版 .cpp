//9.3.1613. 数独简单版 

数独是一种传统益智游戏，你需要把一个 9×9 的数独补充完整，使得图中每行、每列、每个 3×3的九宫格内数字 1∼9均恰好出现一次。
请编写一个程序填写数独。
 
输入格式
输入共 9行，每行包含一个长度为 9的字符串，用来表示数独矩阵。
其中的每个字符都是 1∼9或 ..（表示尚未填充）。

输出格式
输出补全后的数独矩阵。
数据保证有唯一解。

输入样例：
.2738..1.
.1...6735
.......29
3.5692.8.
.........
.6.1745.3
64.......
9518...7.
.8..6534.

输出样例：
527389416
819426735
436751829
375692184
194538267
268174593
643217958
951843672
782965341

//暴搜
#include<iostream>

using namespace std;

const int N=11;

char g[N][N];
bool col[N][N],row[N][N],su[N][N];//col:第i列的第j个数是否出现，row:第i行的第j个数是否出现，su:每个方框中的数字j是否出现过

bool dfs(int x,int y){//对第x行第y行进行插入
    if(y==9) {
        if(dfs(x+1,0))return true;//换行
        return false;
    }   
    if(x==9){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++)
                cout<<g[i][j];//输出
            cout<<endl;
        }
        return true;//因为只需要输出一个就行了，所以只要返回true，就停止遍历
    }
    if(g[x][y]!='.')return  dfs(x,y+1);//如果这个点的数已经存在，遍历下一个点
    for(int i=1;i<=9;i++){
        if(!col[y][i]&&!row[x][i]&&!su[(x/3)*3+y/3][i]){//某个数在行 列 方框中都没有出现过，才可以填入
            col[y][i]=row[x][i]=su[(x/3)*3+y/3][i]=true;
            g[x][y]=i+'0';
            if(dfs(x,y+1)) return true;//因为只需要输出一个就行了，所以只要返回true，就停止遍历
            g[x][y]='.';
            col[y][i]=row[x][i]=su[(x/3)*3+y/3][i]=false;
        }
    }

    return false;
    
}

int main(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cin>>g[i][j];

            if(g[i][j]!='.'){
                row[i][g[i][j]-'0']=true;
                col[j][g[i][j]-'0']=true;
                su[(i/3)*3+j/3][g[i][j]-'0']=true;
            }

        }

    }
    dfs(0,0);
    return 0;
}
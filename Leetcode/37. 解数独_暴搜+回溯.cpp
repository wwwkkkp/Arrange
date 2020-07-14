
//37. 解数独

编写一个程序，通过已填充的空格来解决数独问题。

一个数独的解法需遵循如下规则：

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
空白格用 '.' 表示。



Note:

给定的数独序列只包含数字 1-9 和字符 '.' 。
你可以假设给定的数独只有唯一解。
给定数独永远是 9x9 形式的。


//暴搜+回溯
class Solution {
public:
    bool row[9][10],lie[9][10],sq[9][10];
    vector<vector<char>>b;
    void solveSudoku(vector<vector<char>>& ba) {
        b=ba;
        memset(row,0,sizeof row);
        memset(lie,0,sizeof lie);
        memset(sq,0,sizeof sq);
        
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(b[i][j]!='.'){
                    row[i][b[i][j]-'0']=1;
                    lie[j][b[i][j]-'0']=1;
                    sq[(i/3)*3+j/3][b[i][j]-'0']=1;
                }
            }
        }
        if(dfs(0,0)){
            ba=b;
            return ;
        }
    }
    int dfs(int i,int j){  
        if(i==9)return 1;
        if(j==9){
            i++;
            j=0;
            return dfs(i,j);
        }
        int ju=0;
        if(b[i][j]=='.'){  
            for(int k=1;k<10;k++){
                if(!row[i][k]&&!lie[j][k]&&!sq[(i/3)*3+j/3][k]){
                    row[i][k]=lie[j][k]=sq[(i/3)*3+j/3][k]=1;
                    b[i][j]='0'+k;
                    ju=dfs(i,j+1);
                    if(ju)break;
                    b[i][j]='.';
                    row[i][k]=lie[j][k]=sq[(i/3)*3+j/3][k]=0;
                } 
            }   
        }
        else ju=dfs(i,j+1);
        if(ju)
            return 1;
        return 0;
    }  
};
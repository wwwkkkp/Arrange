




//546. 移除盒子
给出一些不同颜色的盒子，盒子的颜色由数字表示，即不同的数字表示不同的颜色。
你将经过若干轮操作去去掉盒子，直到所有的盒子都去掉为止。每一轮你可以移除具有相同颜色的连续 k 个盒子（k >= 1），这样一轮之后你将得到 k*k 个积分。
当你将所有盒子都去掉之后，求你能获得的最大积分和。

示例 1：
输入:

[1, 3, 2, 2, 2, 3, 4, 3, 1]
输出:

23
解释:

[1, 3, 2, 2, 2, 3, 4, 3, 1] 
----> [1, 3, 3, 4, 3, 1] (3*3=9 分) 
----> [1, 3, 3, 3, 1] (1*1=1 分) 
----> [1, 1] (3*3=9 分) 
----> [] (2*2=4 分)



//这道题和其他典型的区间dP不太一样，多了一维，不知道这个方法是怎么得出的，姑且记下   https://blog.csdn.net/qq_41855420/article/details/89215104
class Solution {
public:

    int removeBoxes(vector<int>& v) {
        int n=v.size();
        if(!n)return 0;
        
        int f[110][110][110]; //区间[i,j](在i的前面有k个和v[i]相同的数)
        memset(f,0,sizeof f);
        for(int i=0;i<n;i++){
            for(int j=0;j<=i;j++){
                f[i][i][j]=(1+j)*(1+j);
            }
        }
        
        for(int len=1;len<n;len++){
            for(int i=0;i+len<n;i++){
                int j=i+len;
                for(int k=0;k<=i;k++){ 		//左边有k个与v[i]相同的数，
                    int res=(1+k)*(1+k)+f[i+1][j][0];      //将[i,j]分成i+[i+1,j];
                    for(int m=i+1;m<=j;m++){
                        if(v[m]==v[i]){
                            res=max(res,f[i+1][m-1][0]+f[m][j][1+k]);  //按照与v[i]相等位置划分
                        }
                    }
                    f[i][j][k]=res;
                }
                
            }
        }
        return f[0][n-1][0];
    }

}; 	
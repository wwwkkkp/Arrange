/*54. 螺旋矩阵

给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。

示例 1:

输入:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
输出: [1,2,3,6,9,8,7,4,5]
示例 2:

输入:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
输出: [1,2,3,4,8,12,11,10,9,5,6,7]

*/


//数组


class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& mat) {
        int n=mat.size();
        if(!n)return {};
        int m=mat[0].size();
        if(!m)return {};
        
        int x1=0,x2=m-1,x3=n-1,x4=0;
        int k=1;
        vector<int>v;
        while(k<=n*m){
            for(int i=x4;i<=x2;i++){v.push_back(mat[x1][i]);k++;}
            x1++;
            if(k>n*m)break;
            for(int i=x1;i<=x3;i++){v.push_back(mat[i][x2]);k++;}
            x2--;
            if(k>n*m)break;
            for(int i=x2;i>=x4;i--){v.push_back(mat[x3][i]);k++;}
            x3--;
            if(k>n*m)break;
            for(int i=x3;i>=x1;i--){v.push_back(mat[i][x4]);k++;}
            x4++;       
            
        }
        return v;
    }
};



class Solution {
public:
    int dis[4][2] = { {0,-1},{0,1},{1,0},{-1,0} };
    bool Isvisit(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& visit) {
        int x = matrix.size();
        int y = matrix[0].size();
        for (int k = 0; k < 4; k++) {
            int m = i + dis[k][0];
            int n = j + dis[k][1];
            if (m < 0 ||m >= x || n< 0 ||n >= y)
                continue;
            else
                if (!visit[m][n])
                    return true;
        }
        return false;

    }
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int>vec;
        if(!matrix.size())return vec;
        int x = matrix.size();
        int y = matrix[0].size();
        vector<vector<int>> visit(x, vector<int>(y, 0));
        int i = 0, j = -1, k = 0;
        while (Isvisit(matrix, i, j, visit)) {
            j++;
            while (i >= 0 && i < x&&j >= 0 && j < y&& visit[i][j] == 0) {
                vec.push_back(matrix[i][j]);
                visit[i][j] = 1;
                j++;
                k++;
            }
            if (k) {
                j--;
                k = 0;
            }
            i++;
            while (i >= 0 && i < x&&j >= 0 && j < y&&visit[i][j] == 0) {
                vec.push_back(matrix[i][j]);
                visit[i][j] = 1;
                i++;
                k++;
            }
            if (k) {
                i--;
                k = 0;
            }
            j--;
            while (i >= 0 && i < x&&j >= 0 && j < y&&visit[i][j] == 0) {
                vec.push_back(matrix[i][j]);
                visit[i][j] = 1;
                j--;
                k++;
            }
            if (k) {
                j++;
                k = 0;
            }
            i--;
            while (i >= 0 && i < x&&j >= 0 && j < y&&visit[i][j] == 0) {
                vec.push_back(matrix[i][j]);
                visit[i][j] = 1;
                i--;
                k++;
            }
            if (k) {
                i++;
                k = 0;
            }
        }
        return vec;
    }
};

//数组
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector <int> ans;
        if(matrix.empty()) return ans; //若数组为空，直接返回答案
        int u = 0; //赋值上下左右边界
        int d = matrix.size() - 1;
        int l = 0;
        int r = matrix[0].size() - 1;
        while(true)
        {
            for(int i = l; i <= r; ++i) ans.push_back(matrix[u][i]); //向右移动直到最右
            if(++ u > d) break; //重新设定上边界，若上边界大于下边界，则遍历遍历完成，下同
            for(int i = u; i <= d; ++i) ans.push_back(matrix[i][r]); //向下
            if(-- r < l) break; //重新设定有边界
            for(int i = r; i >= l; --i) ans.push_back(matrix[d][i]); //向左
            if(-- d < u) break; //重新设定下边界
            for(int i = d; i >= u; --i) ans.push_back(matrix[i][l]); //向上
            if(++ l > r) break; //重新设定左边界
        }
        return ans;
    }
};

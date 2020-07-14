
//10.2.845. 八数码 

在一个3×3的网格中，1~8这8个数字和一个“x”恰好不重不漏地分布在这3×3的网格中。
例如：
1 2 3
x 4 6
7 5 8
在游戏过程中，可以把“x”与其上、下、左、右四个方向之一的数字交换（如果存在）。
我们的目的是通过交换，使得网格变为如下排列（称为正确排列）：
1 2 3
4 5 6
7 8 x
例如，示例中图形就可以通过让“x”先后与右、下、右三个方向的数字交换成功得到正确排列。
交换过程如下：
1 2 3   1 2 3   1 2 3   1 2 3
x 4 6   4 x 6   4 5 6   4 5 6
7 5 8   7 5 8   7 x 8   7 8 x
现在，给你一个初始网格，请你求出得到正确排列至少需要进行多少次交换。
输入格式
输入占一行，将3×3的初始网格描绘出来。
例如，如果初始网格如下所示：
1 2 3 
x 4 6 
7 5 8 
则输入为：1 2 3 x 4 6 7 5 8
输出格式
输出占一行，包含一个整数，表示最少交换次数。
如果不存在解决方案，则输出”-1”。
输入样例：
2  3  4  1  5  x  7  6  8 
输出样例
19



//BFS
#include<iostream>
#include<cstring>
#include<vector>
#include<unordered_map>
#include<queue>

using namespace std;

string en="12345678x"; //对于字符型输入，最好用string 或者是char ，不要用vector
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

int main() {
    string s;
    char c;
	for (int i = 0; i < 9; i++){
	    cin>>c;
	    s=s+c;
	}
	unordered_map<string, int>ump;
	queue<pair<string,int>>q;
	if(strcmp(s.c_str(),en.c_str())==0)return 0;  //strcmp参数是const char*,不是string，所以要转换一下，s.c_str();
	q.push({s,0});
	ump[s] = 1;
	while (q.size()) {
		auto w = q.front();
		string v = w.first;
		int kk = w.second;
		q.pop();
		
		for (int i = 0; i < 9; i++) {
			if (v[i] =='x') {

				for (int j = 0; j < 4; j++) {
					int ii = i / 3 + dx[j];
					int jj = i % 3 + dy[j];

					if (ii >= 0 && ii < 3 && jj >= 0 && jj < 3) {
						swap(v[i],v[ii*3+jj]);
						if(strcmp(v.c_str(),en.c_str())==0){
						    cout<<kk+1<<endl;
						    return 0;
						}
						if (ump.find(v) == ump.end()) {
							q.push({ v ,kk+1});
							ump[v] = 1;
						}
                        swap(v[i],v[ii*3+jj]);
					}

				}
			}

		}
	}
	cout << -1 << endl;
	return 0;
}

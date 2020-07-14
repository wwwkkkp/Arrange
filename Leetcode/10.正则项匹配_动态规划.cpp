//10. 正则表达式匹配
/*
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

说明:

s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
示例 1:

输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
示例 2:

输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
示例 3:

输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
示例 4:

输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
示例 5:

输入:
s = "mississippi"
p = "mis*is*p*."
输出: false

*/

bool isMatch(string s, string p) {
	if (p.empty()) return s.empty(); //p,s同时为空时，输出true
	if (p.size() == 1) {
		return (s.size() == 1 && (s[0] == p[0] || p[0] == '.')); //当p为一个字符时，看s是否是是相等的字符或者是.。因为.可以代表所有数。
	}
	if (p[1] != '*') {   //当p不复制前面的数时
		if (s.empty()) return false;  //s为空，返回false
		return (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));  //第一个数是否相等 && 第二个数是否相等
	}
	//能进这个循环的是s,p的第一个数相等，p第二个数是*，这时候已经不用考虑p前两个数
	while (!s.empty() && (s[0] == p[0] || p[0] == '.')) {
		if (isMatch(s, p.substr(2))) return true;   //从第二个数进行匹配。
		s = s.substr(1);
		printf("%s\n", s.c_str()); // s.c_str():s的首地址
	}
	return isMatch(s, p.substr(2));
}

bool isMatch(const string s, const string p)
{
	vector<int8_t> res((s.size() + 1) * 2);//8个全为零的vector
	auto *pre = res.data() + 1;  //地址赋给pre
	printf("%d\n",* pre);
	auto *cur = pre + s.size() + 1;
	pre[-1] = 1;
	for (auto *pp = p.c_str(); *pp; ++pp) {
		// 针对从一开始就出现的可变数量字符
		cur[-1] = pre[-1] && (pp[1] == '*');
		if (pp[1] == '*') {
			// 可变数量字符
			for (int i = 0; i < s.size(); ++i) {
				// 可以不要, 要的话必须与当前字符相等且前面已经匹配好了
				cur[i] = pre[i] || ((*pp == '.' || *pp == s[i]) && (pre[i - 1] || cur[i - 1]));
			}
			++pp;
		}
		else {
			// 固定数量字符
			for (int i = 0; i < s.size(); ++i) {
				cur[i] = pre[i - 1] && (*pp == '.' || *pp == s[i]);
			}
		}
		std::swap(pre, cur);
	}
	return pre[s.size() - 1];
}

bool isMatch(string s, string p) {
	int m = s.size(), n = p.size();
	vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false)); //二维矩阵（m+1，n+1）值全是
	dp[0][0] = true;
	for (int i = 0; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			//cout << bool(dp[i][j - 2]) << endl;
			if (p[j - 1] == '*') {
				cout<<i<<" "<<j<<" "<< dp[i][j - 2] << endl;
				dp[i][j] = dp[i][j - 2] || (i && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
			}
			else {
				dp[i][j] = i && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
			}
		}
	}
	for (int a = 0; a < m+1; a++) {
		for (int b = 0; b < n + 1; b++) {
			cout << dp[a][b] << " ";
		}
		cout << endl;
	}
	return dp[m][n];
}
int main()
{
	string s = "aab", p = "c*a*b";
	bool a = isMatch(s, p); 
	printf("%d\n", a);
}


bool isMatch(string s, string p) {
	int m = s.size(), n = p.size();
	vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false)); //二维矩阵（m+1，n+1）值全是false
	dp[0][0] = true;
	for (int i = 0; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (p[j - 1] == '*') {
				dp[i][j] = dp[i][j - 2] || (i && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
			}
			else {
				dp[i][j] = i && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
			}
		}
	}
	return dp[m][n];
}




//6.20版
class Solution {
public:
    bool isMatch(string s, string p) {
        int n=s.size();
        int m=p.size();
        if(!n&&!m)return true;

        
        s='0'+s;p='0'+p;
        
        bool f[1000][1000];
        memset(f,0,sizeof f);
        f[0][0]=1;

        for(int i=0;i<=n;i++){   //s可以是空，当p="c*",的时候，就和""匹配
            for(int j=1;j<=m;j++){

                //if(j+1<=m&&p[j+1]=='*')continue;    //加这句话的意思是把a*作为一个整体来看，但是没有必要
                
                if(i>0&&(s[i]==p[j]||p[j]=='.'))
                    f[i][j]=f[i-1][j-1];			//当前数不是*，那就是最后一个数是否相等&&最后一个数之前是否匹配
                else if(p[j]=='*'){
                    f[i][j]=(i>0&&(p[j-1]==s[i]||p[j-1]=='.')&&f[i-1][j])||f[i][j-2];   
					//如果当前数是星，则要看 * 代表了多少个数，有可能是0个，有可能是1个.....，只需要看当前p和s[1-(i-1)]是否匹配

                }
            }
        }
        return f[n][m];    
    }
};

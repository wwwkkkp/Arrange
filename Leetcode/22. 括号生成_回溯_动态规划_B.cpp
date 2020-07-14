//括号生成；
给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。

例如，给出 n = 3，生成结果为：

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]

这道题可以用 回溯算法 DFS BFS 动态规划，下面是 回溯算法 和 动态规划 的解法，DFS和BFS见图/22.括号生成  见图可写

//自己写的方法，回溯算法
/*
“回溯”算法的基本思想是“尝试搜索”，一条路如果走不通（不能得到想要的结果），就回到上一个“路口”，尝试走另一条路。

因此，“回溯”算法的时间复杂度一般不低。如果能提前分析出，走这一条路并不能得到想要的结果，可以跳过这个分支，这一步操作叫“剪枝”。
*/

class Solution {
public:
    vector<string> LaVec;
		//当前括号生成     填充第m位   '('还剩i个   ')'还剩j个    2*n为字符串目标长度
    string func(string s,   int m,     int i,       int j,        int n) {  //这个函数的意思是还剩 i个'(' 和 j个')' 时的s
        if (m == 2 * n) return s;//填充位数等于目标长度，返回s
        if (i > j) return s;     //剩的'(' 比 ')'多，就错误了，返回
        if (j < 0 || i<0) return s;  //如果是3个，那当填充四个的时候就会返回
        for (int k = 0; k < 2; k++) {  //两种情况，加'(‘或者')'
            if (k == 0) {
                s.push_back('(');  //如果添加'('
                i--;  
                s = func(s, m + 1, i, j, n);
                i++;
                s.erase(m, 1);    //不添加时，把添加的删掉，这就是回溯过程
				
            }
            else {
                s.push_back(')'); //如果添加')'
                j--;
                s = func(s, m + 1, i, j, n);
                if (s.size() == 2 * n&&i == 0 && j == 0)  //如果s的大小等于2n，i和j已经没有了
                    LaVec.push_back(s); //生成了一个s，
                j++;
                s.erase(m , 1);    //不添加的情况   
            }
        }	
        return s;
    }
    vector<string> generateParenthesis(int n) {
        string s = "";
        func(s, 0, n , n , n);
        return LaVec;
    }
};
//JAVA的写法，用递归函数，可以参考一下
    private void dfs(String curStr, int left, int right, List<String> res) { //left是(剩的数量，right是)剩的数量
        // 因为是递归函数，所以先写递归终止条件
        if (left == 0 && right == 0) {
            res.add(curStr);
            return;
        }

        // 因为每一次尝试，都使用新的字符串变量，所以没有显式的回溯过程
        // 在递归终止的时候，直接把它添加到结果集即可，与「力扣」第 46 题、第 39 题区分

        // 如果左边还有剩余，继续递归下去
        if (left > 0) {
            // 拼接上一个左括号，并且剩余的左括号个数减 1
            dfs(curStr + "(", left - 1, right, res);
        }
        // 什么时候可以用右边？例如，(((((()，此时 left < right，
        // 不能用等号，因为只有先拼了左括号，才能拼上右括号
        if (right > 0 && left < right) {
            // 拼接上一个右括号，并且剩余的右括号个数减 1
            dfs(curStr + ")", left, right - 1, res);
        }
    }

//动态规划，比较巧妙
/*
思路：
当我们清楚所有 i<n 时括号的可能生成排列后，对与 i=n 的情况，我们考虑整个括号排列中最左边的括号。
它一定是一个左括号，那么它可以和它对应的右括号组成一组完整的括号 "( )"，我们认为这一组是相比 n-1 增加进来的括号。

那么，剩下 n-1 组括号有可能在哪呢？

【这里是重点，请着重理解】

剩下的括号要么在这一组新增的括号内部，要么在这一组新增括号的外部（右侧）。

既然知道了 i<n 的情况，那我们就可以对所有情况进行遍历：

"(" + 【i=p时所有括号的排列组合】 + ")" + 【i=q时所有括号的排列组合】

其中 p + q = n-1，且 p q 均为非负整数。

事实上，当上述 p 从 0 取到 n-1，q 从 n-1 取到 0 后，所有情况就遍历完了。

注：上述遍历是没有重复情况出现的，即当 (p1,q1)≠(p2,q2) 时，按上述方式取的括号组合一定不同。

*/
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		if (n == 0) return {};
		if (n == 1) return { "()" };
		vector<vector<string>> dp(n+1);
		dp[0] = { "" };
		dp[1] = { "()" };
		for (int i = 2; i <= n; i++) {  //i就是n
			for (int j = 0; j <i; j++) {
				for (string p : dp[j])   //(这两个循环是保证 j + i-j-1=i-1)
					for (string q : dp[i - j - 1]) {
						string str = "(" + p + ")" + q;   //n就是在n-1的基础上加一个(),或者n-2的基础上加两个()
						dp[i].push_back(str);
					}
			}
		}
		return dp[n];
	}
};



//调用全排列函数：
/*
找到所有括号的组合方式看起来比较复杂。
所以我们可以尝试换个思路：如果“(”对应数字1，“)”对应数字-1呢？
通过观察我们可以发现这样一个规律：
凡是有效的括号组合，转化成数字，任意前n项和都不小于0！
比如：“（）（）（）”
前1位：1>=0;前2位：1+(-1)=0>=0;前3位：1+(-1)+1=1>=0;
......以此类推，前n位数字和均大于等于0.
又比如：“（（（）））”
前3位：1+1+1=3>=0;前4位：1+1+1+(-1)=2>=0;前5位：1+1+1+(-1)+(-1)=1>=0;
......依然满足规律。
至此，我们就能想到这样一个思路：
1.目标为n时，可以转化为n个-1和n个1
2.求这串数字的所有排列
3.满足以上规律的就是有效的括号组合
4.最后一步再将数字组合转化成括号组合

整个过程需要一些小的工具：
1.求全排列的函数：next_permutation
2.数字转化成括号：容器map
*/
//以下是代码：

class Solution {
public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> result;
        if(n == 0){return result;}
        vector<vector<int>> mid;
        vector<int> temp;
        for(int i = 0 ; i < n ; i ++)
        {
            temp.push_back(-1); //先放所有的-1
        }
        for(int i = 0 ; i < n ; i ++)
        {
            temp.push_back(1);  //再放所有的+1（这样的原因是因为全排列需要从小到大的顺序）
        }
        while(next_permutation(temp.begin(),temp.end()))    //求全排列，对vector数组进行全排列新函数
        {
            int target = 0;
            int judg = 1;
            for(auto i:temp)
            {
                target+=i;
                if(target < 0)
                {
                    judg = 0;break; //是否满足前n项之和不小于0
                }
            }
            if(judg == 1){mid.push_back(temp);}
        }
        map<int,string> invert;
        invert.insert(map<int,string>::value_type(1,"("));  //1对应左括号
        invert.insert(map<int,string>::value_type(-1,")")); //-1对应右括号
        for(auto i:mid)
        {
            string s;
            for(auto j:i)
            {
                s += invert[j]; //数字组合转化成字符串
            }
            result.push_back(s);
        }
        return result;
    }
};





/*
5249. 移除无效的括号 显示英文描述 

给你一个由 '('、')' 和小写字母组成的字符串 s。

你需要从字符串中删除最少数目的 '(' 或者 ')' （可以删除任意位置的括号)，使得剩下的「括号字符串」有效。

请返回任意一个合法字符串。

有效「括号字符串」应当符合以下 任意一条 要求：

空字符串或只包含小写字母的字符串
可以被写作 AB（A 连接 B）的字符串，其中 A 和 B 都是有效「括号字符串」
可以被写作 (A) 的字符串，其中 A 是一个有效的「括号字符串」
 

示例 1：

输入：s = "lee(t(c)o)de)"
输出："lee(t(c)o)de"
解释："lee(t(co)de)" , "lee(t(c)ode)" 也是一个可行答案。
示例 2：

输入：s = "a)b(c)d"
输出："ab(c)d"
示例 3：

输入：s = "))(("
输出：""
解释：空字符串也是有效的
示例 4：

输入：s = "(a(b(c)d)"
输出："a(b(c)d)"

*/

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int a=s.size();
        int ju[a],juR[a];
        int n=0;
        for(int i=0;i<a;i++){
            ju[i]=0;
            juR[i]=0;
            if(s[i]=='('){
                ju[i]=1;  //记录前括号的位置
            }
            if(s[i]==')'){
                int j;
                for(j=i;j>=0;j--){
                    if(ju[j]==1){
                        ju[j]=0; //遇到合适的匹配，就消除该前括号的位置
                        break;
                    }
                }
                if(j==-1){
                    juR[i]=1;//记录多余后括号的位置
                }
                    
            }
        }
        int m=0;
        for(int i=0;i<a;i++){  //统一删减多的前括号和后括号
            if(ju[i]==1||juR[i]==1){
                s.erase(i-m,1);
                m++;
            }
        }
        return s;
    }
};

//堆栈做法
string minRemoveToMakeValid(string s) {
	stack<int> S;
	vector<bool> flag(s.size(), false);
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			S.push(i);  //把前括号的索引压入堆栈
		}
		else if (s[i] == ')') {
			if (S.empty()) {  //堆栈不为空就意味着有前括号对应
				continue;
			}
			flag[i] = true;  //前后括号对应索引位置 置1
			flag[S.top()] = true;
			S.pop();
		}
		else {

		}
	}
	string ret = ""; //重新生成一个字符串，这种情况下不要删除，要重新生成
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(' || s[i] == ')') {
			if (flag[i]) {
				ret.push_back(s[i]);//flag等于1的位置才加括号
			}
		}
		else {
			ret.push_back(s[i]);
		}
	}
	return ret;
}



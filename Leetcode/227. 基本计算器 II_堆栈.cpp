/*  227. 基本计算器 II

实现一个基本的计算器来计算一个简单的字符串表达式的值。

字符串表达式仅包含非负整数，+， - ，*，/ 四种运算符和空格  。 整数除法仅保留整数部分。

示例 1:

输入: "3+2*2"
输出: 7
示例 2:

输入: " 3/2 "
输出: 1
示例 3:

输入: " 3+5 / 2 "
输出: 5

*/
//普通方法，最好不要在for循环里面去改变i(循环变量)的值
class Solution {
public:
    int calculate(string s) {
        stack<int>num;
        stack<char>logo;
        int size=s.size();
        for(int i=0;i<size;i++){  //注意，当循环中出现对i的改变，要格外注意i所指，很容易导致错误
            string s1;
            while(s[i]<=57&&s[i]>=48)
                s1.push_back(s[i++]);
            if(s1.size())
                num.push(atoi(s1.c_str()));
            if(s[i]=='+'||s[i]=='-')
                logo.push(s[i]);
            if(s[i]=='*'||s[i]=='/'){
                char f=s[i++];
                while(s[i++]==' ');
                string s2;
                while(s[i]<=57&&s[i]>=48){
                    s2.push_back(s[i++]);
                }
                int n2=atoi(s2.c_str());
                int t=num.top(),num.pop();
                if(f=='*')
                    num.push(t*n2);
                else if(f=='/')
                    num.push(t/n2);
                i--;  //这里要减去i，因为这时候的i指向一个没有处理的符号，如果直接循环回去，i++,就把这个符号漏了
            }    
        }
        while(!num.empty()&&!logo.empty()){
            int a=num.top();
            num.pop();
            int b=num.top();
            num.pop();
            char f1=logo.top();
            logo.pop();
            if(f1=='+'){
                if(!logo.empty()&&logo.top()=='-'){
                    logo.pop();
                    logo.push('+');
                    num.push(-b+a);
                }
                else
                    num.push(a+b);
            }
            if(f1=='-'){
                if(!logo.empty()&&logo.top()=='-'){   //这里因为用的是堆栈，所以是倒这算的，需要知道头一个数前的符号是'+'还是'-'
                    logo.pop();
                    logo.push('+');
                    num.push(-b-a);
                }
                else
                    num.push(b-a);
            }
        }
        return num.top();
    }
};

//简洁做法

int calculate(string s) {
	s += "+";
	if (s.empty()) return 0;
	stack<int> vals;
	stack<char> ops;
	int val = 0;
	for (auto c : s) {
		if (c == ' ') {
			continue;
		} else if (c >= '0' && c <= '9') {
			val *= 10;
			val += c - '0';
		} else {
			vals.push(val);
			val = 0;
			if (!ops.empty() && (ops.top() == '*' || ops.top() == '/')) {
				int v1 = vals.top();
				vals.pop();
				int v2 = vals.top();
				vals.pop();
				char op = ops.top();
				ops.pop();
				int v = (op == '*') ? (v2 * v1) : (v2 / v1);
				vals.push(v);
			}
			ops.push(c);
		}
	}
	vals.push(val);
	int res = 0;
	while (!ops.empty()) {
		int sign = ops.top() == '-' ? -1 : 1;
		ops.pop();
		int v = vals.top();
		vals.pop();
		res += sign * v;
	}
	if (!vals.empty()) res += vals.top();
	return res;
}


//本题还可以使用双向队列来做


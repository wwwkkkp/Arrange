
//150. 逆波兰表达式求值
根据逆波兰表示法，求表达式的值。

有效的运算符包括 +, -, *, / 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

说明：

整数除法只保留整数部分。
给定逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。
示例 1：

输入: ["2", "1", "+", "3", "*"]
输出: 9
解释: ((2 + 1) * 3) = 9
示例 2：

输入: ["4", "13", "5", "/", "+"]
输出: 6
解释: (4 + (13 / 5)) = 6
示例 3：

输入: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
输出: 22
解释: 
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

//栈，其实这道题的思路应该是 先判断是不是运算，是哪种运算符，然后剩下的肯定是数字
class Solution {
public:
    int evalRPN(vector<string>& v) {
        stack<int>ss;
        int n=v.size();
        if(!n)return 0;
        for(auto c:v){
            if(c[0]>='0'&&c[0]<='9'){
                int res=0;
                for(auto c1:c){
                        res=res*10+c1-'0';
                }
                ss.push(res);
            }
            else if(c[0]=='-'){
                if(c.size()==1){
                    int a=ss.top();ss.pop();
                    int b=ss.top();ss.pop();
                    ss.push(b-a);
                }else{
                    int res=0;
                    for(int i=1;i<c.size();i++){
                        res=res*10+c[i]-'0';
                    }
                    ss.push(-1*res);
                }
            }
            else{
                int a=ss.top();ss.pop();
                int b=ss.top();ss.pop();                
                if(c=="*"){ss.push(a*b);}
                else if(c=="+"){ss.push(a+b);}
                else if(c=="/"){ss.push(b/a);}
            }
        }
        return ss.top();
    }
};
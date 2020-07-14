
//8.5.454. 表达式求值 
给定一个只包含加法和乘法的算术表达式，请你编程计算表达式的值。
输入格式
输入仅有一行，为需要你计算的表达式，表达式中只包含数字、加法运算符“+”和乘法运算符“*”，且没有括号，所有参与运算的数字均为0到2^31−1之间的整数。
输入数据保证这一行只有0~9、+、*这12种字符。
输出格式
输出只有一行，包含一个整数，表示这个表达式的值。
注意：当答案长度多于4位时，请只输出最后4位，前导0不输出。
数据范围
0≤表达式中加法运算符和乘法运算符的总数≤10^5

输入样例：
1+1000003*1
输出样例：
4

//表达式固定写法
#include<iostream>
#include<stack>
using namespace std;

const int M=10000;
stack<int> num;
stack<char> ops;

void work(){
    int b=num.top();num.pop();
    int c=num.top();num.pop();
    char e=ops.top();ops.pop();
    if(e=='+')
        num.push((b+c)%M);
    else
        num.push(b*c%M);
}

int main(){
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++){
        int a=0;
        while(i<s.size()&&s[i]>='0'&&s[i]<='9'){  //表达式固定写法
            a=a*10+s[i]-'0';
            i++;
        }
        num.push(a%M);
        if(s[i]=='+'){
            while(ops.size()&&ops.top()=='*')//加法的上一个符号是乘法，就把前面的数全计算
                work();
            ops.push(s[i]);
        }
        else if(s[i]=='*'){
            if(ops.size()&&ops.top()=='*')//乘法前面是乘法的话，只计算前面那个乘法
                work();
			ops.push(s[i]);
        }
    }
    while(ops.size())work();
    cout<<num.top()<<endl;
    return 0;
}

//拓展，如果是有+=*/^，那就要确定优先级(用哈希表存储+=*/^的优先级)，优先级低的前面是优先级高的，全计算，优先级相同，只计算上一个，
//如果有(),就涉及到递归。
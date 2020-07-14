
//65. 有效数字
验证给定的字符串是否可以解释为十进制数字。

例如:

"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
" -90e3   " => true
" 1e" => false
"e3" => false
" 6e-1" => true
" 99e2.5 " => false
"53.5e93" => true
" --6 " => false
"-+3" => false
"95a54e53" => false

说明: 我们有意将问题陈述地比较模糊。在实现代码之前，你应当事先思考所有可能的情况。这里给出一份可能存在于有效十进制数字中的字符列表：

数字 0-9
指数 - "e"
正/负号 - "+"/"-"
小数点 - "."
当然，在输入中，这些字符的上下文也很重要。

//状态机，这道题可以把整个s都变成状态机
class Solution {
public:
    bool isNumber(string s) {
        if(!s.size())return false;
        
        while(s.size()&&s[0]==' ')s.erase(s.begin());//去除首位空格
        while(s.size()&&s[s.size()-1]==' ')s.erase(s.end()-1);
        int n=s.size();
        if(!n)return false;
        
        int i=0;
        for(;i<n;i++){
            if(s[i]>='0'&&s[i]<='9'||s[i]=='e'||s[i]=='+'||s[i]=='-'||s[i]=='.')
            {if(s[i]=='e')break;}
            else return false;
        }
        string s1=s.substr(0,i);
        if(i==n)return isn(s1)>0;
        string s2=s.substr(i+1);
        int a=isn(s1);
        int b=isn(s2);
        return a>0&&b>2;
    }
	/*
	isn返回状态：
	-1：不是数
	0：空
	1：带符号小数
	2：不带符号小数
	3：带符号整数
	4：不带符号整数
	*/
    int isn(string s){//是否是数，有无小数点
        int  n=s.size();
        if(!n)return 0;
        if(s[0]=='+'||s[0]=='-'){
            if(n==1)return -1;
            int a=isn(s.substr(1));
            if(a==4)return 3;
            if(a==3||a==1||a==-1||a==0)return -1;
            if(a==2)return 1;
        }
        if(s[0]=='.'){
            if(n==1)return -1;
            int a=isn(s.substr(1));
            if(a==4)return 2;
            else return -1;
        }
        int i=0;
        for(;i<n;i++){
            if(s[i]>='0'&&s[i]<='9'||s[i]=='.'){
                if(s[i]=='.')break;
            }else return -1;
        }
        if(i==n)return 4;
        string s1=s.substr(0,i);
        string s2=s.substr(i+1);
        int a=isn(s1);
        int b=isn(s2);
        if(a==4&&b==4||a==0&&b==4||a==4&&b==0)return 2;
        else return -1;
    }
};


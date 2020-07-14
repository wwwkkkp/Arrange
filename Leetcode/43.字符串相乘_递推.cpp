/*  字符串相乘.cpp
给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

示例 1:

输入: num1 = "2", num2 = "3"
输出: "6"
示例 2:

输入: num1 = "123", num2 = "456"
输出: "56088"
说明：

num1 和 num2 的长度小于110。
num1 和 num2 只包含数字 0-9。
num1 和 num2 均不以零开头，除非是数字 0 本身。
不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。


*/

//具体见图集 

class Solution {
public:
    string multiply(string num1, string num2) {
        int size1=num1.size();
        int size2=num2.size();
        if(num1=="0"||num2=="0")
            return "0";
        string sum(size1+size2,'0');    //这个用来储存位置，
        int  n=0;
        int  k=0;
        for(int i=size1-1;i>=0;i--){
            for(int j=size2-1;j>=0;j--){
                n=(num1[i]-'0')*(num2[j]-'0');
                sum[i+j]+=(sum[i+j+1]-'0'+n)/10;   //这意味是多少即使是11，后面也会除以10 ，所以不用担心进位的问题
                sum[i+j+1]=(sum[i+j+1]-'0'+n)%10+'0'; //两数相乘的个位
            }
        }
        if(sum[0]=='0')
            sum.erase(0,1);
        return sum;
    }
};

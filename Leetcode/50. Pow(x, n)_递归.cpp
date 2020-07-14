

//50. Pow(x, n)
实现 pow(x, n) ，即计算 x 的 n 次幂函数。

示例 1:

输入: 2.00000, 10
输出: 1024.00000
示例 2:

输入: 2.10000, 3
输出: 9.26100
示例 3:

输入: 2.00000, -2
输出: 0.25000
解释: 2-2 = 1/22 = 1/4 = 0.25
说明:

-100.0 < x < 100.0
n 是 32 位有符号整数，其数值范围是 [−2^31, 2^31 − 1] 。


//递归
class Solution {
public:
    double myPow(double x, int n1) {
        if(!n1)return 1;
        if(n1==1)return x;
        long long n=n1;   //先把n1转换成长整型，这样可以避免极端情况n=-2^31 但是n不能取2^31，
        if(n<0){x=1/x;n*=-1;}

        double a;
        
        if(n%2) a=x*myPow(x*x,n/2);
        else a=myPow(x*x,n/2);
        return a;
    }
};


class Solution {  
public:
    double myPow(double x, long long n) {  //或者直接转换
        if(!n)return 1;
        if(n==1)return x;

        if(n<0){x=1/x;n*=-1;}

        double a;
        
        if(n%2) a=x*myPow(x*x,n/2);
        else a=myPow(x*x,n/2);
        return a;
    }
};
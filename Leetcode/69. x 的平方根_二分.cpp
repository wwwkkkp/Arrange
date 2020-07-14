

//69. x 的平方根
实现 int sqrt(int x) 函数。

计算并返回 x 的平方根，其中 x 是非负整数。

由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。

示例 1:

输入: 4
输出: 2
示例 2:

输入: 8
输出: 2
说明: 8 的平方根是 2.82842..., 
     由于返回类型是整数，小数部分将被舍去。

//硬算
class Solution {
public:
    int mySqrt(long long x) {
        int  i=0;
        for(;1ll*(i+1)*(i+1)<=x;i++);
        return i;
    }
};

//二分  下面的方法是取较小值，区分看35题
class Solution {
public:
    int mySqrt(long long x) {
        int left=0,right=x;
        while(left<right){
            int mid=1ll*(left+right)+1>>1;
            if((long long)mid*mid>x)right=mid-1;
            else left=mid;
        }
        return right;
    }
};
/*357. 计算各个位数不同的数字个数
给定一个非负整数 n，计算各位数字都不同的数字 x 的个数，其中 0 ≤ x < 10n 。

示例:

输入: 2
输出: 91 
解释: 答案应为除去 11,22,33,44,55,66,77,88,99 外，在 [0,100) 区间内的所有数字。

*/

//DP

class Solution {
public:
    int Array(int a,int b){
        int x=1;
        while(b--)
            x*=a--;
        return x;
    }
    int countNumbersWithUniqueDigits(int n) {
        int a=1;
        for(int i=1;i<=n;i++)
            a+=(i-1)*Array(9,i-1)+Array(9,i);  
        return a;
    }
};

/*
//公式：
当首位是0的时候，就是n-1时的数，
当首位不是0的时候，其他位是0的时候，(n-1)*Array(9,n-1)  //n-1,0的位置的选择，Array(9,n-1)其他位的选择(排列，第一位有9种可能，以此类推，然后再插入0，就是这个数)
当没有0的时候，Array(9,i)
*/
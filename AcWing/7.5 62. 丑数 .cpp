//7.5 62. 丑数 


我们把只包含质因子2、3和5的数称作丑数（Ugly Number）。
例如6、8都是丑数，但14不是，因为它包含质因子7。
求第n个丑数的值。
样例
输入：5

输出：5
注意：习惯上我们把1当做第一个丑数。




class Solution {
public:
    int getUglyNumber(int n) {
        int a[n];
        a[0]=1;
        int i=0,j=0,k=0; //因为丑数只能由2 3 5 组成 ，那后面的丑数一定是前面的丑数乘以2 3 5组成，因为从小到大排列，所以按序求最小值
        for(int m=1;m<n;m++){
            a[m]=min(a[i]*2,min(a[j]*3,a[k]*5));
            if(a[m]==a[i]*2) i++;
            if(a[m]==a[j]*3) j++;
            if(a[m]==a[k]*5) k++;
        }
        return a[n-1];
    }
};



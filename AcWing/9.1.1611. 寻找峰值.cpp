
//9.1.1611. 寻找峰值

峰值定义为比左右相邻元素大的元素。
给定一个长度为 n的数组nums，数组下标从0开始，保证 nums[i]≠nums[i+1]，请找出该数组的峰值，并返回峰值的下标。
数组中可能包含多个峰值，只需返回任意一个即可。
假定 nums[-1] = nums[n] = -∞。
本题中数组是隐藏的，你可以通过我们预设的 int 函数 query 来获得数组中某个位置的数值是多少。
例如，query(a) 即可获得下标为 a的元素的值。

注意：
query 函数的调用次数不能超过 min(3×log2n,10)。
数据范围1≤n≤105，数组中的整数在 int 范围内。

输入样例1：
[1, 2, 3, 1]
输出样例1：
2
输入样例2：
[1, 2, 1, 3, 5, 6, 4]
输出样例2：
1

样例解释
对于样例 1，3是峰值，其下标为 2。
对于样例 2，2 和 6是峰值，下标为 1和 5，输出任意一个均可。

// Forward declaration of queryAPI.
// int query(int x);
// return int means nums[x].

class Solution {
public:
    int findPeakElement(int n) {
        int l=0;
        int r=n-1;
        while(l<r){//因为query的访问限制，mid是去小数点后的数，所以只需要比较mid和mid+1，
            int mid=(l+r)/2;
            if( query(mid) > query(mid+1) ) r=mid;
            else l=mid+1;
            
        }
        return l;
    }
};
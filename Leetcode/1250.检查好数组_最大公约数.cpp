//检查好数组  求数组的最大公约数
/*
给你一个正整数数组 nums，你需要从中任选一些子集，然后将子集中每一个数乘以一个 任意整数，并求出他们的和。

假如该和结果为 1，那么原数组就是一个「好数组」，则返回 True；否则请返回 False。


示例 1：

输入：nums = [12,5,7,23]
输出：true
解释：挑选数字 5 和 7。
5*3 + 7*(-2) = 1
示例 2：

输入：nums = [29,6,10]
输出：true
解释：挑选数字 29, 6 和 10。
29*1 + 6*(-3) + 10*(-1) = 1
示例 3：

输入：nums = [3,6]
输出：false

*/

//该程序实际是求数组的最大公约数
class Solution {
public:
    int gcd(int a,int b){  //求最大公约数
        if(b==0)
            return a;
        else
            return gcd(b,a%b);
    }
    bool isGoodArray(vector<int>& nums) {
        int size=nums.size();
        int d=nums[0];
        for(int i=1;i<size;i++){
            d=gcd(d,nums[i]);
        }
        return d==1;
    }
};


//拓展 求数组的最小公倍数


int LCM(int x,int y){
	return x/gcd(x,y)*y;   //在去掉最大公约数之后相乘
}
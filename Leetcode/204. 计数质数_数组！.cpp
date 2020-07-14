
//204. 计数质数
统计所有小于非负整数 n 的质数的数量。

示例:

输入: 10
输出: 4
解释: 小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。



class Solution {
public:
    int countPrimes(int n) {
        if(n<2)return 0;
        bool f[1500000];
        memset(f,1,sizeof f);
        
        for(int i=2;i<=sqrt(n);i++){//要判断n以下的质数，只需要判断到sqrt(n)就行；
            if(f[i]){				//这个数是质数
                for(int j=i*i;j<n;j+=i){  //以i为因子的数都不是质数，，比如i=2时，所有小于n的偶数都被标记不是质数，为什么以i*i开始，因为如i=5,5*2、5*3、5*4已经被标记过了
                    f[j]=false;
                }
            }
        }
        int res=0;
        for(int i=2;i<n;i++){ //剔除所有不是质数的数，剩下的就是质数
            if(f[i])res++;
        }
        return res;
    }
};
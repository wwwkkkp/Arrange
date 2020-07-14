/*279. 完全平方数

给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。

示例 1:

输入: n = 12
输出: 3 
解释: 12 = 4 + 4 + 4.
示例 2:

输入: n = 13
输出: 2
解释: 13 = 4 + 9.

*/

//宝藏解法：数学公式
//4 ms	8.1 MB
/*
数学解法是在评论区看到的，也就是有个理论：任何一个数，都可以由小于等于4个的完全平方数相加得到。

然后根据这个理论，有个推论（我也不知道这个推论怎么来的）：

当\(n \)满足如下公式时，才只能由4个完全平方数得到, \(a \)和\(b \)为某个整数：

n = 4^a * (8b + 7)

否则，就是只能由1-3个完全平方数得到。

由一个完全平方数得到就非常好验证了。。。这个大家都懂，直接开方。。。

由两个完全平方数相加，其实也很好懂，直接从小到大循环，直接看他是不是等于两个完全平方数相加就行了。

也就是：
*/
class Solution {
public:
    int numSquares(int n) {
        // 验证1
        int m = static_cast<int>(sqrt(n));
        // 验证2
        if (m * m == n) return 1; 
        for (int i = 1; i * i <= n; i++) {
            int j = static_cast<int>(pow(n - i * i, 0.5));
            if (j * j + i * i == n) return 2;
        }
        // 验证4
        while (n % 4 == 0) n /= 4;
        if (n % 8 == 7) return 4;
		//剩下的情况就是3
        return 3;
    }
};


//动态规划，效果一般，自己写的
//232 ms	11.3 MB
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1,INT_MAX);
        dp[0]=0;
        dp[1]=1;
        for(int  i=2;i<n+1;i++){
            int a=sqrt(i);         
            int j=0;
            while(a-j>0){
                int b=i-pow(a-j,2);
                dp[i]=min(dp[b]+1,dp[i]);，//递推公式：dp(n)=min{dp(n),dp(n−i∗i)+1}，递推的核心就是转化为比他小的数
                j++;
            }
        }
        return dp[n];
    }
};

//动态规划 改良版
//176 ms	11.3 MB

class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1);
        for (int i = 1; i <= n; i++) {
            dp[i] = i;
            for (int j = 1; j * j <= i; j++) 
                dp[i] = min(dp[i], dp[i - j * j] + 1);
        }
        return dp[n];
    }
};

//6.12版本
class Solution {
public:
    int f[500000];
    int numSquares(int n) {
        if(!n)return 0;
        
        memset(f,0x3f3f3f,sizeof f);
        f[0]=0;
        for(int i=1;i<=n;i++){
            int j=1;
            while(j*j<=i){
                f[i]=min(f[i],f[i-j*j]+1);
                j++;
            }
        }

        return f[n];
    }
};

// BFS 效果更差
//304 ms	50 MB
class Solution {
public:
    //对于完全平方数，我们要理解到
    // 13它题意说明是经过若干个完全平方数之和，因此每次我们可以减去一个平方数
    //并且记录减去多少个平方数，使得结果为0
    //我们想到广度优先遍历，就是记录层数，从当前位置到目标位置需要经过多少层
    //13 （12,9,4）12（11,8,3）9（8,5,0）由此我们知道13=4+9
    int numSquares(int n) {
        if(n==0)
            return 0;
        queue<pair<int,int>> v;
        v.push(make_pair(n,0));
        vector<bool> sp(n+1,false);
        sp[n]=true;
        while(v.size())
        {
            int size=v.size();
            while(size--)
            {
                auto pt=v.front();
                v.pop();
                int d=pt.first;
                sp[d]=true;
                for(int i=1;d-i*i>=0;++i)
                {
                    int a=d-i*i;
                    if(a==0)
                    {
                        int k=pt.second;
                        k++;
                        return k;
                    }
                    if(sp[a]==false) //做的优化，如果这个数，在前面已经访问过了，就不要将它入队列，因为后续结果一样
                    v.push(make_pair(a,pt.second+1));
                }
            }
        }
        return 0;
    }
};

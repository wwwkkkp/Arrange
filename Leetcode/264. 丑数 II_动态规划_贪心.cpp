/* 264. 丑数 II

编写一个程序，找出第 n 个丑数。

丑数就是只包含质因数 2, 3, 5 的正整数。

示例:

输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
说明:  

1 是丑数。
n 不超过1690。

*/

//动态规划，遇到这种情况的时候，不能用排除法，因为计算量太大了，只能考虑这些数是怎么组成的，然后来找出规律，递推方法

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int>Vec={1};
        int i1=0;
        int i2=0;
        int i3=0;
        while(Vec.size()<n){
            int L1=Vec[i1]*2;  //遍历方法，用Vec中的数 自我遍历
            int L2=Vec[i2]*3;  //顺序不能改变
            int L3=Vec[i3]*5;

            int min1=min(L1,min(L2,L3));  //这个方法要好好想想，最小值
            if(min1==L1) i1++;
            if(min1==L2) i2++;
            if(min1==L3) i3++;
            Vec.push_back(min1);
        }
        return Vec[n-1];
    }
};

//贪心算法

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int>nums;
        
        for(long a=1;a<=INT_MAX;a*=2)   //暴力搜索，就是看有多少个 2 多少个3 多少个5，把所有的情况都组成起来，就是结果
            for(long b=a;b<=INT_MAX;b*=3)
                for(long c=b;c<=INT_MAX;c*=5)
                    nums.push_back(c);
        
        sort(nums.begin(),nums.end());
        
        return nums[n-1];
        
    }
};

//筛选法是走不通的  //只能算200个数左右
int nthUglyNumber(int n) {
	unordered_map<int, int>um;
	vector<int>Vec(1700, 0);
	um[1] = 1, um[2] = 1, um[3] = 1, um[4] = 1, um[5] = 1;
	Vec[0] = 1, Vec[1] = 2, Vec[2] = 3, Vec[3] = 4, Vec[4] = 5;
	int i = 5;
	for (int j = 6; i < n; j++) {
		int m2 = j % 2, m3 = j % 3, m5 = j % 5;
		int n2 = j / 2, n3 = j / 3, n5 =j / 5;
		if (m2 == 0&& um[n2]) {
				Vec[i++] = j;
				um[j] = 1;
		}
		else if (m3 == 0 && um[n3]) {
			Vec[i++] = j;
			um[j] = 1;
		}
		else if (m5 == 0 && um[n5]) {
			Vec[i++] = j;
			um[j] = 1;
		}
	}
	return Vec[n - 1];
}

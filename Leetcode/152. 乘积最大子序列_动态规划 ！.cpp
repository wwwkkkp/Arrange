// 152. 乘积最大子序列
/*

给定一个整数数组 nums ，找出一个序列中乘积最大的连续子序列（该序列至少包含一个数）。

示例 1:

输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。
示例 2:

输入: [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

*/






//分段

/*
* 以0为分界成一段一段分析
* 在一段中负数的个数要么为偶数要么为奇数
* 倘若负数的个数为偶数，那么直接相乘必然是最大值，因为偶数个负数相乘为正数
* 倘若负数有奇数个，设为n个的话，那么n-1个负数则为偶数个
* 那么这个减一因为是连续的子序列，所以要么是不包含最左边的负数，要么是不包含最右边的负数，只有这两种情况
* 那么只需要从左往右遍历一次，从右往左遍历一次，求最大值就可以了
* 注意为0的时候，虽然product要设置回1，但是有可能最大值就是0(每段都只有1个负数)，那么需要判断下answer是否更新为0
*/
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int nums_size=nums.size(),product=1,answer=INT_MIN;
        for (int i=0;i<nums_size;++i)
        {
            if (nums.at(i)==0) //以0为界限分段
            {
                product=1;
                if (0>answer) 
                    answer=0;
                continue;
            }
            product=product*nums.at(i); //从左到右依次相乘，每乘一个数，和最大值比较
            if (product>answer)         
                answer=product;  //answer是最大值
        }
        product=1;
        for (int i=nums_size-1;i>=0;--i)  
        {
            if (nums.at(i)==0) //以0为界限分段
            {
                product=1;
                if (0>answer)
                    answer=0;
                continue;
            }
            product=product*nums.at(i);
            if (product>answer)    ////从右到左依次相乘，每乘一个数，和最大值比较，从左到右和从右到左是不一样的，因为负数的分布不是对称的，依次选哪些负数结果是不一样的
                answer=product;
        }
        return answer;
    }
};


//动态规划
//因为一旦出现负数的话，最大就会变成最小，或者最小变成最大，所以，最大和最小应该同时更新，然后和当前值得正负做判断。当最大和最小反复横跳的时候，这个例子很适合
//要充分考虑动态规划的影响因素 
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int size=nums.size();
        if(size==0)
            return 0;
        int minB=nums[0];// 以 nums[i] 为结尾的数 的最小乘积
        int maxB=nums[0];//以 nums[i] 为结尾的数 的最大乘积
        int ret=nums[0]; //到nums[i]为止的最大乘积
        for(int i=1;i<size;i++){
            int tmp=maxB;
            maxB=max(nums[i],max(nums[i]*maxB,minB*nums[i])); //这一时刻的最大值，等于上一时刻的 最大值和最小值 和当前值相乘，然后和 当前值 三个数比较的最大
            minB=min(nums[i],min(nums[i]*tmp,minB*nums[i])); //这一时刻的最小值，等于上一时刻的 最大值和最小值 和当前值相乘，然后和 当前值 三个数比较的最小
            ret=max(ret,maxB);
        }
        return ret;
    }
};


//自己写的，这个方法有点缺陷，就是占用空间大，用时长，有一个例子过不了
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int size=nums.size();
        if(size==0)
            return 0;
        vector<int> nums_n;
        int flag=0;
        for (int i = 0; i < size; i++) 
            if (nums[i] != 1)
                nums_n.push_back(nums[i]);
            else
                flag=1;
        int n_size=nums_n.size();
        vector<vector<int>> out1(n_size, vector<int>(n_size,0));
        int max_num=-(1<<30);
        for(int i=0;i<n_size;i++){
            out1[i][i]=nums_n[i];
            max_num=max(max_num,out1[i][i]);
        }
        for(int i=0;i<n_size;i++){
            for(int j=i+1;j<n_size;j++){
                out1[i][j]=out1[i][j-1]*nums_n[j];
                max_num=max(max_num,out1[i][j]);
            }            
        }
        if(flag=1)
            return max(max_num,1);  
        return max_num;  
    }
    
};
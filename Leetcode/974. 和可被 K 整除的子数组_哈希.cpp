

//974. 和可被 K 整除的子数组
给定一个整数数组 A，返回其中元素之和可被 K 整除的（连续、非空）子数组的数目。

 

示例：

输入：A = [4,5,0,-2,-3,1], K = 5
输出：7
解释：
有 7 个子数组满足其元素之和可被 K = 5 整除：
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]

//暴搜，过不了
class Solution {
public:
    int subarraysDivByK(vector<int>& A, int k) {
        int n=A.size();
        if(!n)return 0;
        int f[30010];
        f[0]=A[0];
        int res=0;
        for(int i=1;i<A.size();i++)f[i]=(f[i-1]+A[i])%k;
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if((f[j]-f[i]+A[i])%k==0)res++;
            }
        }
        return  res;
    }
};


//同余定理
class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        unordered_map<int,int>um;  //统计各个余数的个数
        um[0]++;
        int sum=0;
        for(auto c:A){   //求前缀和的余数，如果两个前缀和的余数相同，那他们中间相夹的数的和一定是能被整除的，
            sum+=c;
            int y=((sum%K)+K)%K;
            um[y]++;
        }
        int cnt=0;
        for(auto c:um){
            cnt+=(c.second*(c.second-1)/2);  //组合取两个，然后相加就是结果
        }
        return cnt;
    }
};

//134. 加油站
在一条环路上有 N 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。

说明: 

如果题目有解，该答案即为唯一答案。
输入数组均为非空数组，且长度相同。
输入数组中的元素均为非负数。
示例 1:

输入: 
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

输出: 3

解释:
从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
因此，3 可为起始索引。
示例 2:

输入: 
gas  = [2,3,4]
cost = [3,4,3]

输出: -1

解释:
你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
因此，无论怎样，你都不可能绕环路行驶一周。



//方法1：暴力
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n=gas.size();
        if(!n)return -1;
        
        for(int k=0;k<n;k++){
            int cnt=0;
            for(int i=k;i<k+n;i++){
                int j=i;
                if(j>=n)j-=n;
                cnt+=gas[j]-cost[j];
                if(cnt<0)break;
            }
            if(cnt>=0)return k;
        }
        return -1;
    }
};

//方法二：一次遍历

可以将两个数组 gasgas 和 costcost 看成一个数组，即 a[i]=gas[i]-cost[i]a[i]=gas[i]−cost[i]，从某点出发，统计 aa 的连续和 sumsum，当此时的 sum<0sum<0 时说明无法通行.

从每一个点出发，依次扫描复杂度是 O(n^2)O(n 
2
 )，可以进行如下优化.

假设结点总数为 nn，从结点 0 出发，sumsum 即为 aa 的前缀和，即 sum[i]=a[0]+a[1]+...a[i]sum[i]=a[0]+a[1]+...a[i].

求出 sumsum 的最小值，假设为 sum[i]sum[i]，如果此时的 sum[n-1]>=0sum[n−1]>=0 那么只需要从 i+1i+1 位置出发，一定是合法的.

反证法证明如下：

假设从 i+1i+1 出发，如果在 i+1i+1 的右边某个位置 jj 出现了无法通行的情况，即 sum[j]-sum[i]<0sum[j]−sum[i]<0，移项得 sum[j]<sum[i]sum[j]<sum[i]，这是不可能的，因为 sum[i]sum[i] 是最小值，前后矛盾.

如果在 i+1i+1 的左边某个位置 jj 出现了无法通行的情况，即 sum[n-1]-sum[i]+sum[j]<0sum[n−1]−sum[i]+sum[j]<0，移项得 (sum[j]-sum[i])+sum[n-1]<0(sum[j]−sum[i])+sum[n−1]<0，也是不可能的，因为假设中 sum[n-1]>=0sum[n−1]>=0 且 sum[i]sum[i] 是最小值，那么也一定有 sum[j]-sum[i]>=0sum[j]−sum[i]>=0 ，两个非负项相加一定还是非负的，前后矛盾.

优化之后的方法，只需要求出 sumsum 以及它的最小值下标，时间复杂度 O(n)O(n).


class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n=gas.size(),sum=0,id=0,minsum=INT_MAX;
        for(int i=0;i<n;++i){
            sum+=gas[i]-cost[i];
            if(sum<minsum){  //找出前缀和最小值
                id=i;
                minsum=sum;
            }
        }
        return sum>=0?(id+1)%n:-1;
    }
};


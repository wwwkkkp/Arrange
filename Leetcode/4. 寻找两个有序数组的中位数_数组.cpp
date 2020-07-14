/* 4. 寻找两个有序数组的中位数
给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。

请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

你可以假设 nums1 和 nums2 不会同时为空。

示例 1:

nums1 = [1, 3]
nums2 = [2]

则中位数是 2.0
示例 2:

nums1 = [1, 2]
nums2 = [3, 4]

则中位数是 (2 + 3)/2 = 2.5


*/
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if (m < n) return findMedianSortedArrays(nums2, nums1); //使长的在前面，短的在后面 这里有一个递归
        if (n == 0) return ((double)nums1[(m - 1) / 2] + (double)nums1[m / 2]) / 2.0;//姑且认为是中间的两个数的平均数
        int left = 0, right = n * 2;
        while (left <= right) {
            int mid2 = (left + right) / 2;
            int mid1 = m + n - mid2;//mid1+mid2等于m+n
            double L1 = mid1 == 0 ? INT_MIN : nums1[(mid1 - 1) / 2];//INT_MIN是最小值，int是32位，那INT_MIN就等于-(2^31-1),INT_MAX等于(2^31-1).
            double L2 = mid2 == 0 ? INT_MIN : nums2[(mid2 - 1) / 2];
            double R1 = mid1 == m * 2 ? INT_MAX : nums1[mid1 / 2]; //R是右边 L是左边
            double R2 = mid2 == n * 2 ? INT_MAX : nums2[mid2 / 2];
            if (L1 > R2) left = mid2 + 1;
            else if (L2 > R1) right = mid2 - 1;
            else return (max(L1, L2) + min(R1, R2)) / 2;
        }
        return -1;
    }
};
// https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2471/very-concise-ologminmn-iterative-solution-with-detailed-explanation
//[6 9 13 18]  ->   [# 6 # 9 # 13 # 18 #] 
//中位数的想法是将数组切成两半，得到每一半的边数（称为L和R）的平均值。即，对于大小为N的阵列A，中位数=（A [（N-1）/ 2] + A [N / 2]）/ 2
//当剪切一个数字时，想想它就像每一半占用数字的一半。
//对于大小为N的数组，有2 * N + 1种方式/位置切成两半，对于范围为[0,2 * N]的k，它表示左半部分有多少半数。 L =（k-1）/ 2，R = k / 2;当k = 0时，表示空L，当k = 2 * N时，表示空R.
//当我们将A1和A2分成两半时，每一半的总长度相同，比如位置c1和c2，边数L1，L2，R1，R2。如果左边的所有数字<=右边的所有数字，我们发现中位数=（max（L1，L2）+ min（R1，R2））/ 2.0。每一半应具有（N1 + N2）/ 2个数字，这意味着（N1 + N2）两半，因此c1 + c2 = N1 + N2。
//现在我们可以二进制搜索c1或c2。
// c1的范围是[0,2 * N1]，c2的范围是[0,2 * N2]。
//也是，0 <= c2 = N1 + N2  -  c1 <= N2
// => c1也在[N1  -  N2，N1 + N2]范围内
// => c1范围[max（0，N1  -  N2），min（2 * N1，N1 + N2）]
//如果我们有L1> R2，这意味着A1的左半部分有太多的大数字，那么我们必须向左移动C1（即向右移动C2）;
//如果L2> R1，那么A2的左半部分有太多的大数字，我们必须向左移动C2。
//否则，这次切割是正确的。
//在找到切口后，介质可以计算为（max（L1，L2）+ min（R1，R2））/ 2;


//中位数做法
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m=nums1.size();
        int n=nums2.size();
        priority_queue<int,vector<int>,greater<int>>pq;
        for(auto c:nums1)pq.push(c);
        for(auto c:nums2)pq.push(c);
        if((n+m)%2){//奇数个数的情况
            for(int i=0;i<(n+m)/2;i++)pq.pop();
            return (double)pq.top();
        }else{ //偶数个情况
            for(int i=1;i<(n+m)/2;i++)pq.pop();
            int a=pq.top();
            pq.pop();
            int b=pq.top();
            pq.pop();
            return (double)(a+b)/2;
        }
    }
};
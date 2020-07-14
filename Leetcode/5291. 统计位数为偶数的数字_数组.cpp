/*5291. 统计位数为偶数的数字
给你一个整数数组 nums，请你返回其中位数为 偶数 的数字的个数。

 

示例 1：

输入：nums = [12,345,2,6,7896]
输出：2
解释：
12 是 2 位数字（位数为偶数） 
345 是 3 位数字（位数为奇数）  
2 是 1 位数字（位数为奇数） 
6 是 1 位数字 位数为奇数） 
7896 是 4 位数字（位数为偶数）  
因此只有 12 和 7896 是位数为偶数的数字
示例 2：

输入：nums = [555,901,482,1771]
输出：1 
解释： 
只有 1771 是位数为偶数的数字。
 

提示：

1 <= nums.length <= 500
1 <= nums[i] <= 10^5

*/

//数组 直接除就行了，但是这里有个问题，是一个数除完然后再除第二个数，还是每个数 除一位 然后 再除一位，应该前者要好一些
//下面是后者
class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int n=nums.size();
        vector<int>ve(n,0);
        int k=0;
        int count=0;
        while(1){
            count=0;
            for(int i=0;i<n;i++){
                if(nums[i]!=0){
                    nums[i]=nums[i]/10;
                    ve[i]++;
                    if(nums[i]==0&&ve[i]%2==0)
                        k++;
                }else
                    count++;
            }    
            if(count==n)
                break;
        }
        return k;
    }
};
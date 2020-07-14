/*5293. 子串的最大出现次数

给你一个字符串 s ，请你返回满足以下条件且出现次数最大的 任意 子串的出现次数：

子串中不同字母的数目必须小于等于 maxLetters 。
子串的长度必须大于等于 minSize 且小于等于 maxSize 。
 

示例 1：

输入：s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
输出：2
解释：子串 "aab" 在原字符串中出现了 2 次。
它满足所有的要求：2 个不同的字母，长度为 3 （在 minSize 和 maxSize 范围内）。
示例 2：

输入：s = "aaaa", maxLetters = 1, minSize = 3, maxSize = 3
输出：2
解释：子串 "aaa" 在原字符串中出现了 2 次，且它们有重叠部分。
示例 3：

输入：s = "aabcabcab", maxLetters = 2, minSize = 2, maxSize = 3
输出：3
示例 4：

输入：s = "abcde", maxLetters = 2, minSize = 3, maxSize = 3
输出：0
 

提示：

1 <= s.length <= 10^5
1 <= maxLetters <= 26
1 <= minSize <= maxSize <= min(26, s.length)
s 只包含小写英文字母。

*/

//哈希表
/*
思路：
1、只关注minSize即可，因为如果长度为maxSize的字串出现了N次那么长度为minSize的字串出现次数也会是N,而题目要求返回出现次数最大的任意子串。
2、确定了长度以后就可以维护一个 固定大小的滑动窗口 去统计满足条件（不同字母的数目小于等于maxLetters）的子串的出现次数了，统计次数可以借助map来做。
3、最后取个次数的最大值即可。

*/

class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int n=s.size();
        unordered_map<string,int>ump;
        int nums=0;
		
        for(int i=0;i<=n-minSize;i++){
            string s1=s.substr(i,minSize); //截取子串
            unordered_map<char,int>ump1;
			
            for(int j=0;j<minSize;j++) //计算窗口内的子串 的 不同的字符 的多少
                ump1[s1[j]]++;
			
            if(ump1.size()<=maxLetters) //如果符合要求，添加进哈希表
                ump[s1]++;
        }
        for(unordered_map<string,int>::iterator it=ump.begin();it!=ump.end();it++){ //选出最大的数
            nums=max(nums,it->second);
        }
        return nums;
    }
};
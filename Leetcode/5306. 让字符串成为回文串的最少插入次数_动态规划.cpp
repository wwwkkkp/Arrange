/* 5306. 让字符串成为回文串的最少插入次数
给你一个字符串 s ，每一次操作你都可以在字符串的任意位置插入任意字符。

请你返回让 s 成为回文串的 最少操作次数 。

「回文串」是正读和反读都相同的字符串。

示例 1：

输入：s = "zzazz"
输出：0
解释：字符串 "zzazz" 已经是回文串了，所以不需要做任何插入操作。

示例 2：

输入：s = "mbadm"
输出：2
解释：字符串可变为 "mbdadbm" 或者 "mdbabdm" 。

示例 3：

输入：s = "leetcode"
输出：5
解释：插入 5 个字符后字符串变为 "leetcodocteel" 。

示例 4：

输入：s = "g"
输出：0

示例 5：

输入：s = "no"
输出：1

提示：

	1 <= s.length <= 500
	s 中所有字符都是小写字母。

*/

//动态规划
动态规划解决这道题。
考虑字符串S,长度为len。
S[0],...S[len-1]的字符串，有如下讨论：

1.S[0] == S[len-1]，则判断S[1]-S[len-2]即可。
2.不相等时，则最小的插入长度 = min(S[1]-S[len-1], S[0]-S[len-2]) + 1， 即最后插入的和首尾中的一个对称，考虑剩下的即可。
3.注意边界条件。

class Solution {
public:
    int minsize(string& s,int L,int R,vector<vector<int>>& vec){
        if(L==R) 
            return 0;
        if(vec[L][R]!=-1) return vec[L][R];
        if(R-L==1){
            if(s[L]==s[R])
                return vec[L][R]=0;   
            else
                return vec[L][R]=min(minsize(s,L, R-1,vec),minsize(s,L+1,R,vec))+1;
        }
        else{
            if(s[L]==s[R])
                return vec[L][R]=minsize(s,L+1,R-1,vec);
            else
                return vec[L][R]=min(minsize(s,L+1, R,vec),minsize(s,L,R-1,vec))+1;
        }
    }
    int minInsertions(string s) {
        int n=s.size();
        vector<vector<int>> vec(n,vector<int>(n,-1));  //备忘录
        return minsize(s,0,s.size()-1,vec);
    }
};
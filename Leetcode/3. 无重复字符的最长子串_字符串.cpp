/* 3. 无重复字符的最长子串
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:

输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。


示例 2:

输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。


示例 3:

输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。

*/

//笨办法
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(!s.size()) return 0;
        int n=s.size();
        if(n==1)return 1;
        unordered_map<char,int>up;
        int num=0;
        int count=0;
        for(int j=0;j<n;j++){
            for(int i=j;i<n;i++){ //二维复杂度
                if(up.find(s[i])==up.end()){
                    up[s[i]]=1;
                    count++;
                }      
                else{
                    up.erase(up.begin(),up.end());
                    num=max(num,count);
                    count=0;
                    break;
                }   
            }
        }
        return num;
    }
};


//一维复杂度

//对字符串的遍历，左边不停的遍历，右边删除
//把出现过的字符都放入set中，遇到set中没有的字符就加入set中并更新结果res，如果遇到重复的，则从左边开始删字符，直到删到重复的字符停止
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0, left = 0, i = 0, n = s.size();
        unordered_set<char> t; //无序列的set,这里用set也可以
        while (i < n) {
            if (!t.count(s[i])) {  //如果t中没有这个数
                t.insert(s[i++]);  //t插入这个数然后i++，往下遍历
                res = max(res, (int)t.size());//看是否是最大的长度
            }  else {
                t.erase(s[left++]);//从右往左删除，一直删到，没有t中没有重复的字符为止
            }
        }
        return res;
    }
};
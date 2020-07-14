


9. 回文数
判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

示例 1:

输入: 121
输出: true
示例 2:

输入: -121
输出: false
解释: 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
示例 3:

输入: 10
输出: false
解释: 从右向左读, 为 01 。因此它不是一个回文数。
进阶:

你能不将整数转为字符串来解决这个问题吗？


//数字
class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0)return false;
        vector<int>v;

        while(x){
            v.push_back(x%10);
            x=x/10;
        }
        vector<int>v1=v;
        reverse(v1.begin(),v1.end());
        return v1==v;
    }
};


//把数字转化成string
class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;
        string s1 = to_string(x);
        string s2 = s1;
        reverse(s1.begin(), s1.end());
        return s1 == s2;
    }
};


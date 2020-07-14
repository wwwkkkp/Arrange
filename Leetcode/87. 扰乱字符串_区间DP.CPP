






87. 扰乱字符串
给定一个字符串 s1，我们可以把它递归地分割成两个非空子字符串，从而将其表示为二叉树。

下图是字符串 s1 = "great" 的一种可能的表示形式。

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
在扰乱这个字符串的过程中，我们可以挑选任何一个非叶节点，然后交换它的两个子节点。

例如，如果我们挑选非叶节点 "gr" ，交换它的两个子节点，将会产生扰乱字符串 "rgeat" 。

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
我们将 "rgeat” 称作 "great" 的一个扰乱字符串。

同样地，如果我们继续交换节点 "eat" 和 "at" 的子节点，将会产生另一个新的扰乱字符串 "rgtae" 。

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
我们将 "rgtae” 称作 "great" 的一个扰乱字符串。

给出两个长度相等的字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串。

示例 1:

输入: s1 = "great", s2 = "rgeat"
输出: true
示例 2:

输入: s1 = "abcde", s2 = "caebd"
输出: false




//区间DP
class Solution {
public:
    //bool d[1000][1000][1000];
    map<pair<string,string>,bool>um;
    bool isScramble(string s1, string s2) {
        int n=s1.size();
        return dfs(s1,s2);
    }
    bool dfs(string s1, string s2) {  //s1是不是s2的扰乱字符串
        int n = s1.size();
        int m = s2.size();
        if(s1==s2)return true;			//相等就返回真
        string t1 = s1, t2 = s2;
		sort(t1.begin(), t1.end());
		sort(t2.begin(), t2.end());
		if (t1 != t2)					//剪枝，元素相同，才可能是扰乱字符串
			return false;       
        if(um.find({s1,s2})!=um.end())return um[{s1,s2}];		//剪枝，如果两个字符串比较过，就返回结果
        for (int i = 1; i <= n-1; i++) {
            string s3 = s1.substr(0, i);
            string s4 = s1.substr(i, n-i);		//s1截成两部分
            string s5 = s2.substr(0, i);
            string s6 = s2.substr(i, n-i);		//s2截成两部分，有两种截法，前半部分和s1的前半部分长度相同，后半部分和s1的前半部分长度相同
            string s7 = s2.substr(n-i,i);
            string s8 = s2.substr(0,n-i);
            bool p1=0,p2=0,q1=0,q2=0;
            if(s3.size()==s5.size()) p1 = dfs(s3, s5);			//分别看子串是不是扰乱数组
            um[{s3,s5}]=p1;										//把结果添加进表中
            if(s3.size()==s7.size()) p2= dfs(s3, s7);
            um[{s3,s6}]=p2;
            if(s4.size()==s8.size()) q1 = dfs(s4, s8);
            um[{s4,s5}]=q1;
            if(s4.size()==s6.size()) q2 = dfs(s4, s6);
            um[{s4,s6}]=q2;
            if ((p1&&q2) || (p2&&q1))return true;			//如果是，就返回

        }
        return false;
    }
};
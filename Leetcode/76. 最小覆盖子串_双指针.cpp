



//76. 最小覆盖子串

给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字符的最小子串。

示例：

输入: S = "ADOBECODEBANC", T = "ABC"
输出: "BANC"
说明：

如果 S 中不存这样的子串，则返回空字符串 ""。
如果 S 中存在这样的子串，我们保证它是唯一的答案。



class Solution {
public:
    bool cheak(unordered_map<char,int>&um){ //检查某个子串是否全部包含t中元素
        for(auto c:um){
            if(c.second<=0)
                return false;
        }
        return true;
    }
    string minWindow(string s, string t) {
        unordered_map<char,int>um;
        for(auto c:t)
            if(um.find(c)==um.end())um[c]=0;    
            else um[c]--;//如果t中有两个一样的数，那就在s中必须要出现两次才能算全部包含，这里减一=-1，加上两次才能够大于0，才算是包含
        
        int a=0,b=0;//双指针
        int i=0,j=20000; //记录最小的区间
        while(b<s.size()){
            if(um.find(s[b])!=um.end())um[s[b]]++; //当前数在t中
            b++;  //移动指针
            while(cheak(um)){  //都包含
                if(b-a<j-i)  //区间更小
                    i=a,j=b;
                if(um.find(s[a])!=um.end())um[s[a]]--;   //移动左指针，先要减去这个数
                a++;
            }
        }
        if(!a&&b==s.size())return ""; //没有的情况
        return s.substr(i,j-i); //输出最小区间
    }
};
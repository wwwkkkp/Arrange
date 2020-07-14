



//30. 串联所有单词的子串
给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。

注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。

 

示例 1：

输入：
  s = "barfoothefoobarman",
  words = ["foo","bar"]
输出：[0,9]
解释：
从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
输出的顺序不重要, [9,0] 也是有效答案。
示例 2：

输入：
  s = "wordgoodgoodgoodbestword",
  words = ["word","good","best","word"]
输出：[]




class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(!words.size())return {};
        int n=words[0].size();
        int m=words.size();
        if(s.size()<n)return {};
        unordered_map<string,int>um;
        vector<int>out;
        for(string c:words)um[c]++;
        for(int i=0,j=n*m-1;j<s.size();i++,j++){  //截取固定大小窗口，看这些窗口中是否包含所有的words中的数，
            auto um1=um;
            int m1=m;
            m1++;
            int k=i;
            while(--m1){
                string s1=s.substr(k,n);
                if(um1.find(s1)==um1.end())
                    break;
                um1[s1]--;
                if(um1[s1]<0)
                    break;
                k+=n;
            }
            if(0==m1)out.push_back(i);
        }
        return out;
    }
};


//58. 最后一个单词的长度
给定一个仅包含大小写字母和空格 ' ' 的字符串 s，返回其最后一个单词的长度。如果字符串从左向右滚动显示，那么最后一个单词就是最后出现的单词。

如果不存在最后一个单词，请返回 0 。

说明：一个单词是指仅由字母组成、不包含任何空格字符的 最大子字符串。

 

示例:

输入: "Hello World"
输出: 5


class Solution {
public:
    int lengthOfLastWord(string s) {
        int n=s.size();
        if(!n)return 0;
        reverse(s.begin(),s.end());  //翻转
        while(s[0]==' ')s.erase(s.begin()); //删除开头的空格

        for(int i=0;i<s.size();i++){
            if(s[i]==' ')return i; 
        }
        return s.size();
    }
};

//字符串的分段，
class Solution {
public:
    int lengthOfLastWord(string s) {
        reverse(s.begin(),s.end());
        stringstream ss(s);     //以空格为分界输出各个字符串，这里只需要输出第一个就行，
        string str;
        ss>>str;
        return str.size();
    }
};
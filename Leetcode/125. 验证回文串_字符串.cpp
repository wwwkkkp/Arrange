

//125. 验证回文串
给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

说明：本题中，我们将空字符串定义为有效的回文串。

示例 1:

输入: "A man, a plan, a canal: Panama"
输出: true
示例 2:

输入: "race a car"
输出: false

//这种题不如重新开一个字符串存符合条件的字母和数字
class Solution {
public:
    bool isPalindrome(string s) {
        int n=s.size();
        if(!n)return true;
        
        for(int i=0;i<n;i++){
            if(s[i]>='A'&&s[i]<='Z')s[i]=(s[i]-'A')+'a';
        }
        
        while(s.size()&&(s[0]>'z'||s[0]<'a')&&(s[0]<'0'||s[0]>'9'))s.erase(s.begin());
        for(int i=0;i+1<s.size();){
            if((s[i+1]<'a'||s[i+1]>'z')&&(s[i+1]<'0'||s[i+1]>'9'))s.erase(s.begin()+i+1);
            else i++;
        }
        string s1=s;
        reverse(s1.begin(),s1.end());
        return s1==s;
    }
};




//用内置函数解决
class Solution {
public:
    bool isPalindrome(string s) {
        string tmp;
        for (auto c : s) {
            if (islower(c) || isdigit(c))  tmp += c;
            else if (isupper(c)) tmp += (c + 32);
        }
        int i = 0, j = tmp.size() - 1;
        while (i < j) {
            if (tmp[i] != tmp[j]) return false;
            i++;
            j--;
        }
        return true;
    }
};
记一笔 c++的几个内置函数
	islower(char c) 是否为小写字母
	isuppper(char c) 是否为大写字母
	isdigit(char c) 是否为数字
	isalpha(char c) 是否为字母
	isalnum(char c) 是否为字母或者数字
	toupper(char c) 字母小转大
	tolower(char c) 字母大转小

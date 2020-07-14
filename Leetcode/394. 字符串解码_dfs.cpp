

//394. 字符串解码
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

示例:

s = "3[a]2[bc]", 返回 "aaabcbc".
s = "3[a2[c]]", 返回 "accaccacc".
s = "2[abc]3[cd]ef", 返回 "abcabccdcdcdef".

//递归
class Solution {
public:
    string decodeString(string s) {
        string  s1;
        for(int i=0;i<s.size();i++){
            if(s[i]>='0'&&s[i]<='9'){
                int c=0,j=i;
                while(s[j]>='0'&&s[j]<='9')c=c*10+s[j++]-'0';
                int n=1;
                i=++j;
                while(n){				//当遇到中括号的时候，把中括号中的字符提取出来，然后递归
                    if(s[j]=='[')n++;
                    if(s[j]==']')n--;
                    j++;
                }
                string s2=decodeString(s.substr(i,j-i-1));         
                for(int k=0;k<c;k++)s1+=s2;
                i=--j;
            }else s1+=s[i];
            
        }
        return s1;
    }
};
//17.77. 翻转单词顺序 

/*
输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
为简单起见，标点符号和普通字母一样处理。
例如输入字符串"I am a student."，则输出"student. a am I"。
样例
输入："I am a student."

输出："student. a am I"
*/

//这道题可以使用栈或者是另开一个数组解决，占用的空间是O(n),
//如果这道题要求在原字符串上修改，见下


class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(),s.end());   //先整体翻转
    	for(int i=0;i<s.size();){   //标准定式，一段一段的去循环
    		int j=i;
    		while(j<s.size()&&s[j]!=' ')j++;  //然后每个单词翻转
    		reverse(s.begin()+i,s.begin()+j);
    		i=j+1;
    	}
    	return s;
    }
};
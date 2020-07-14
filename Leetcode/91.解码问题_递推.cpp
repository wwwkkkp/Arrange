/*
一条包含字母 A-Z 的消息通过以下方式进行了编码：

'A' -> 1
'B' -> 2
...
'Z' -> 26
给定一个只包含数字的非空字符串，请计算解码方法的总数。

示例 1:

输入: "12"
输出: 2
解释: 它可以解码为 "AB"（1 2）或者 "L"（12）。
示例 2:

输入: "226"
输出: 3
解释: 它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。
*/


//正确答案：数字递推方法：

class Solution {
public:
    int num = 0;
    int numDecodings(string s) {
        int ssize=s.size();
        int i_1=1;   //上一个数后分隔的方法数量
        int i_2=1;   //上两个数后分隔的方法数量
        int cur=0;
        if(s[0]=='0')
            return 0;
        for(int i=1;i<ssize;i++){
            if(s[i]=='0')
                if(s[i-1]=='1'||s[i-1]=='2')
                    cur=i_2;
                else
                    return 0;
            else if(s[i-1]=='1'){
                cur=i_1+i_2;
            }
            else if(s[i-1]=='2'){
                if(s[i]<='6')
                    cur=i_1+i_2;
                else    
                    cur=i_1;
            }
            else   
                cur=i_1;
            i_2=i_1;
            i_1=cur;
            
        }
        return i_1;
    }
};

//数组递推方法：（虽然正确，但是要考虑i-2=-1的情况，比较麻烦）
class Solution {
public:
    int num = 0;
    int numDecodings(string s) {
        int ssize=s.size();
        int num[ssize];
        num[0]=1;
        if(s[0]=='0')
            return 0;
        for(int i=1;i<ssize;i++){
            if(s[i]=='0'){
                if(s[i-1]=='1'||s[i-1]=='2')
                {   
                    if(i-2<0)
                        num[i]=1;
                    else
                        num[i]=num[i-2];
                    continue;
                }
                else
                    return 0;
            }
            if(s[i-1]=='1')
                if(i-2<0)
                    num[i]=num[i-1]+1;
                else
                    num[i]=num[i-1]+num[i-2];
            else if(s[i-1]=='2'){
                if(s[i]<='6')
                    if(i-2<0)
                        num[i]=num[i-1]+1;
                    else
                        num[i]=num[i-1]+num[i-2];
                else
                    num[i]=num[i-1];
            }
            else{
                num[i]=num[i-1];
            }
        }
        return num[ssize-1];
    }
};

//递归方法：（失败） 失败原因见 心得.cpp
int num = 0;
int numDecodings(string s) {
	int ssize = s.size();
	if (ssize == 0)
		return 1;
	for (int i = 0; i <= 1; i++) { //这里有for循环
		string s1;
		s1.push_back(s[0]);
		if (i == 1)
			if (ssize >= 2)
				s1.push_back(s[1]);
			else
				continue;
		int a = atoi(s1.c_str());
		if (a<=26&&a>=1) {
			string s2;
			for (int j = i + 1; j < ssize; j++) {
				s2.push_back(s[j]);
			}
			int n = numDecodings(s2);
			//return numDecodings(s2);
			if (n == 1)
				num++;
		}	 
	}
	return num; //这个返回值得位置是不对的，最后的结果不准
}


/* //151. 翻转字符串里的单词
给定一个字符串，逐个翻转字符串中的每个单词。

示例 1：

输入: "the sky is blue"
输出: "blue is sky the"
示例 2：

输入: "  hello world!  "
输出: "world! hello"
解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
示例 3：

输入: "a good   example"
输出: "example good a"
解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
 

说明：

无空格字符构成一个单词。
输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

*/

//原地翻转
string reverseWords(string s) {
    reverse(s.begin(), s.end());                        //整体反转
    int start = 0, end = s.size() - 1;
    while (start < s.size() && s[start] == ' ') start++;//首空格
    while (end >= 0 && s[end] == ' ') end--;            //尾空格
    if (start > end) return "";                         //特殊情况

    for (int r = start; r <= end;) {                    //逐单词反转
        while (s[r] == ' '&& r <= end) r++;
        int l = r;
        while (s[l] != ' '&&l <= end) l++;
        reverse(s.begin() + r, s.begin() + l);
        r = l;
    }

    int tail = start;                                   //处理中间冗余空格
    for (int i = start; i <= end; i++) {
        if (s[i] == ' '&&s[i - 1] == ' ') continue;
        s[tail++] = s[i];  //这个删除中间多余空格有点意思
    }
    return s.substr(start, tail - start);
}


//自己写的
class Solution {
public:
    string reverseWords(string s) {
        string dir;
        s+=' ';
        vector<string>vec;
        for(auto c:s){
            if(c==' '){
                if(!dir.size())
                    continue;
                else{
                    vec.push_back(dir);
                    dir="";
                }           
            }
            else
                dir+=c;
        }
        string s1;
        int flag=0;
        for(int i=vec.size()-1;i>=0;i--){
            if(flag==0)
                flag=1;
            else    
                s1+=' ';
            s1=s1+vec[i];
        }
		return s1;        
    }
};

//流
string reverseWords(string s) {
    string ans, str;
    vector<string> tmp;
    stringstream ss(s);
    while (ss >> str) tmp.push_back(str);  //流输入 ，默认以空格为界
    for (int i = tmp.size() - 1; i >= 0; i--) ans += tmp[i] + " "; //倒过来输入
    return ans.size() ? string(ans.begin(), ans.end() - 1) : ""; //删掉最后一个空格，这样可以不用flag标志位 
}


//17.1.591. 国家领导者 

某个国家的宪法规定，领导者是名称中包含最多不同字母的人。 （该国使用从A到Z的大写英文字母。）
例如，GOOGLE有四个不同的字母：E，G，L和O，而APAC CODE JAM有八个不同的字母。 
如果该国仅由这两个人组成，APAC CODE JAM将成为领导者。
如果存在平局，那么名字按字典序排列靠前的人就是领导者。
给定该国公民的名单，你能确定领导者是谁吗？

输入格式
第一行包含整数T，表示共有T组测试数据。
每组数据第一行包含整数N。
接下来N行，每行包含一个公民的名字，该名字最多包含20个字符，且至少包含一个字母。

输出格式
每组数据输出一个结果，每个结果占一行。
结果表示为“Case #x: y”，其中x是组别编号（从1开始），y是领导者的名字。

数据范围
1≤T≤100
1≤N≤100
名字中可包含大写字母或空格，所有名字以字母开头和结尾。
输入样例：
2
3
ADAM
BOB
JOHNSON
2
A AB C
DEF
输出样例：
Case #1: JOHNSON
Case #2: A AB C
样例解释
在样例＃1中，JOHNSON包含5个不同的字母（’H’，’J’，’N’，’O’，’S’），因此他是领导者。
在样例＃2中，DEF包含3个不同的字母，A AB C也包含3个不同的字母。 但是A AB C按字典序更靠前，因此他是领导者。



//注意带空格的string的输入方式

#include<iostream>
#include<unordered_set>
#include<cstring>

using namespace std;

int n,t;

bool work(string s1,string s2){
    unordered_set<char>a,b;
    for(int c:s1)
        if(c!=' ')
            a.insert(c);
    for(int c:s2)
        if(c!=' ')
            b.insert(c);
    
    if(a.size()!=b.size()) return a.size()<b.size();
    else return s1>s2;
}

int main(){
    cin>>t;
    for(int c=1;c<=t;c++){
        cin>>n;
        getchar();   //本题最重要，输入带空格的string，这个是去除n后面的\n，
        string ans;
        while(n--){
            string s;
            getline(cin,s);      //把一行输入赋予s,相当于输入带空格的string
            if(work(ans,s)) ans=s;   //strcpy不能用于string，string 用=
        }
        printf("Case #%d: %s\n",c,ans.c_str());    //输出的string，要加上c_str()，即ans的首地址
    }
    return 0;
}


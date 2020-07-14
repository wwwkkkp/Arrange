

//17.3.561. 大按钮 
你是一个受欢迎的新游戏节目的参赛者，正在为大奖而努力！
有两个大按钮，一个是红色，另一个是黑色，你需要连续N次按动按钮，每次可任选其一按动。
你可以自由的制定你的按动顺序，但是有P个按动顺序序列被称为禁用开头，每个长度不大于N。
如果你的按动顺序在开始时就包含了禁用开头，那么你就不会赢得大奖。 
当然，你的按动顺序序列可以包含一个或多个禁用开头，但是前提是它们不能出现在序列的开头。
如果一个长度为N的按动顺序序列在开头不包含任何禁用开头，那么这个序列就是一个获胜序列。 
请问共有多少个不同的获胜序列？
输入格式
第一行包含整数T，表示共有T组测试数据。
每组数据的第一行包含两个整数N和P。
接下来P行，每行包含一个长度不超过N的字符串，字符串R和B构成，R表示按下红色按钮，B表示按下黑色按钮。
每个字符串代表一个禁用开头，数据保证禁用开头互不相同。
输出格式
每组数据输出一个结果，每个结果占一行。
结果表示为“Case #x: y”，其中x为组别编号（从1开始），y为获胜序列的数量。
数据范围
1≤T≤100
1≤P≤min(2N,100)
1≤N≤50
输入样例：
4
3 2
BBB
RB
5 1
R
4 3
R
B
RBRB
50 5
BRBRBBBRBRRRBBB
BRBRBRRRBRRRBRB
BBBRBBBRBRRRBBB
BRBRBRRRBRRRB
BRBRBBBRBBBRB
输出样例：
Case #1: 5
Case #2: 16
Case #3: 0
Case #4: 1125556309458944
样例解释
在第一种情况下，你必须按动3次按钮。共8种按法，其中3种按法是禁止按法，如下所示：
1、RBB。这是禁止的，因为它以第一个禁用开头（RB）开始。
2、RBR。这是禁止的，因为它以第一个禁用开头（RB）开始。
3、BBB。这是禁止的，因为它以第二个禁用开头（BBB）开始。
因此，只有5个获胜序列。

//因为不能出现指定的开头，所有，只需要把是这些开头的字符串减去就行了，
//例1:3个字符组成的字符串，总组合数是n=1<<3，开头不能有BBB，那就n-=1<<(3-3),开头不能是RB,n-=1<<(3-2)
//这里要注意的就是例三的情况，已经减去开头是R的情况了，不能再减去RBRB的情况，因为他们是包含关系，所以要特判一下

#include<iostream>
#include<algorithm>
#include<cstring>
#include<unordered_map>

using namespace std;
typedef long long ll;

int t,n,p;
void work(unordered_map<string,int>&um,string s){
    for(auto it=um.begin();it!=um.end();it++){
        string s1=it->first;
        int a=strncmp(s1.c_str(),s.c_str(),min( s1.size(),s.size() ));  //判断哈希表中已有的字符串和当前要添加的字符串是不是包含关系，
        if(0==a){  //如果是包含关系
            if(s1.size()>s.size()){  //留下最短的那个 
                um.erase(it);
                um[s]=1;
            }
            return;
        }
    }
    um[s]=1;
    return;
}

int main(){
    cin>>t;
    for(int c=1;c<=t;c++){
        cin>>n>>p;
        unordered_map<string,int>um;
        string s;
        for(int i=0;i<p;i++){
            cin>>s;
            work(um,s);
        }
        ll res=(1ll)<<n;  //注意long long类型的数的位数挪动，(1ll)<<n   1ll:long long类型的1
        for(auto it=um.begin();it!=um.end();it++){
            res-=(1ll)<<(n-it->first.size());
        }
        printf("Case #%d: %lld\n",c,res);
    }
    return 0;
}
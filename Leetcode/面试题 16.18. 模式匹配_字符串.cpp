

面试题 16.18. 模式匹配
你有两个字符串，即pattern和value。 pattern字符串由字母"a"和"b"组成，用于描述字符串中的模式。例如，字符串"catcatgocatgo"匹配模式"aabab"（其中"cat"是"a"，"go"是"b"），该字符串也匹配像"a"、"ab"和"b"这样的模式。但需注意"a"和"b"不能同时表示相同的字符串。编写一个方法判断value字符串是否匹配pattern字符串。

示例 1：

输入： pattern = "abba", value = "dogcatcatdog"
输出： true
示例 2：

输入： pattern = "abba", value = "dogcatcatfish"
输出： false
示例 3：

输入： pattern = "aaaa", value = "dogcatcatdog"
输出： false
示例 4：

输入： pattern = "abba", value = "dogdogdogdog"
输出： true
解释： "a"="dogdog",b=""，反之也符合规则
提示：

0 <= len(pattern) <= 1000
0 <= len(value) <= 1000
你可以假设pattern只包含字母"a"和"b"，value仅包含小写字母。


//暴搜，可以把二维改成一维，但是有很多要注意
class Solution {
public:
    bool patternMatching(string p, string v) {
        int n=p.size();
        int m=v.size();
        if(!n&&!m)return true;
        
        
        int a=0,b=0;
        for(auto c:p){
            if(c=='a') a++;
            else b++;
        }
        
        for(int i=0;i<=m;i++){
		
            int j=0;
            if(a*i>m)break;  //这个不能放到for判断语句中去，因为可能a=0，这样就会进入死循环
            if(b){
                if((m-a*i)%b)continue;
                j=(m-a*i)/b;
            }
			
            set<string>se1,se2;
            if(a*i+b*j!=m)continue;
            int k=0;
            for(auto c:p){
                if(c=='a'){
                    string s1=v.substr(k,i);
                    k+=i;
                    se1.insert(s1);
                    if(se1.size()!=1)break;
                }else{
                    string s1=v.substr(k,j);
                    k+=j;
                    se2.insert(s1);
                    if(se2.size()!=1)break;
                }
            }
            if((b==0&&se1.size()==1)||(a==0&&se2.size()==1)||(se1.size()==1&&se2.size()==1&&(*se1.begin()!=*se2.begin()))){return true;}
            }
        return false;
    }
};
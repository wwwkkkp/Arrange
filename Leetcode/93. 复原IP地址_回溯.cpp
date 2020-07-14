/*93. 复原IP地址

给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。

示例:

输入: "25525511135"
输出: ["255.255.11.135", "255.255.111.35"]

*/

//回溯
class Solution {
public:
    vector<string>vec;
    void DFS(string &s,int n,int st,string a ,int count){
        if(count==4&&st!=n-1) return;
        if(count==4&&st==n-1){
            a.erase(a.size()-1);
            vec.push_back(a);
            return;
        }
        for(int i=st+1;i<st+4&&i<n;i++){
            string str=s.substr(st+1,i-st);
            int num=0,ju=0;
            for(int j=0;j<str.size();j++){//变整数
                num=num*10+(str[j]-'0');
                if(j>0&&num<10){
                    ju=1;
                    break;
                }     
            }
            if(ju)
                break;
            if(num<=255&&num>=0)//在0-255中间
                DFS(s,n,i,a+str+'.',count+1);
        }
    }
    vector<string> restoreIpAddresses(string s) {
        DFS(s,s.size(),-1,"",0);
        return vec;
    }
};
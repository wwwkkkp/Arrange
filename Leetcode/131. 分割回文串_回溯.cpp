
//131. 分割回文串
给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。

返回 s 所有可能的分割方案。

示例:

输入: "aab"
输出:
[
  ["aa","b"],
  ["a","a","b"]
]

//回溯
class Solution {
public:
    vector<vector<string>>v;
    vector<string>v1;
    vector<vector<string>> partition(string s) {
        int n=s.size();
        if(!n)return {{}};
        dfs(s,0,n);
        return v;
    }
    void dfs(string &s,int a,int b){
        if(a==b){
            v.push_back(v1);
            return;
        }
        for(int i=a;i<b;i++){
            string s1=s.substr(a,i-a+1);
            if(ish(s1)){
                v1.push_back(s1);
                dfs(s,i+1,b);
                v1.pop_back();
            }
        }
    }
    bool ish(string& s){
        int n=s.size();
        int i=0,j=n-1;
        while(i<j){
            if(s[i]==s[j])i++,j--;
            else return false;
        }
        return true;;      
    }
};




//126. 单词接龙 II
给定两个单词（beginWord 和 endWord）和一个字典 wordList，找出所有从 beginWord 到 endWord 的最短转换序列。转换需遵循如下规则：

每次转换只能改变一个字母。
转换过程中的中间单词必须是字典中的单词。
说明:

如果不存在这样的转换序列，返回一个空列表。
所有单词具有相同的长度。
所有单词只由小写字母组成。
字典中不存在重复的单词。
你可以假设 beginWord 和 endWord 是非空的，且二者不相同。
示例 1:

输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

输出:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]
示例 2:

输入:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

输出: []

解释: endWord "cog" 不在字典中，所以不存在符合要求的转换序列。



class Solution {
public:
    
    vector<vector<string>>v;
    vector<string>v1;
    unordered_map<string,int>um;
    unordered_map<string ,int>um1;
	
    vector<vector<string>> findLadders(string b, string e, vector<string>& w) {
        int n=w.size();
        int m=b.size();
        if(!n)return {};
        

        for(int i=0;i<n;i++){
            um[w[i]]=1;
            um1[w[i]]=0;
        }
        if(um.find(e)==um.end())return {};
        
        queue<pair<string,int>>q;
        q.push({b,1});
        
        int k=0;
        while(q.size()){
            auto a=q.front();q.pop();
            
            string s=a.first;
            if(s==e){k=a.second;break;}
            for(int i=0;i<m;i++){
                char c=s[i];
                for(int j=0;j<26;j++){
                    if('a'+j!=c)s[i]='a'+j;
                    if(um.find(s)!=um.end()&&um1[s]==0){
                        q.push({s,a.second+1});
                        um1[s]=1;
                    }
                }
                s[i]=c;
            }
        }
        for (int i = 0; i < n; i++) { 
            um1[w[i]] = 0; 
            if (w[i] == b)um1[w[i]] = 1;
        }
        v1.push_back(b);
        dfs(b,e,k-1);
        return v;
    } 
    
    void dfs(string s,string &s1,int k){
        int m=s.size();
        if(k==0){
            if(s==s1)v.push_back(v1);
            return;
        }
        for(int i=0;i<m;i++){
            char c=s[i];
            for(int j=0;j<26;j++){
                s[i]='a'+j;
                if(um.find(s)!=um.end()&&um1[s]==0){
                    
                    v1.push_back(s);
                    um1[s]=1;
                    dfs(s,s1,k-1);
                    um1[s]=0;
                    v1.pop_back();
                }
            }
            s[i]=c;
        }      
    }  
};
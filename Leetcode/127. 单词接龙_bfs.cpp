

//127. 单词接龙
给定两个单词（beginWord 和 endWord）和一个字典，找到从 beginWord 到 endWord 的最短转换序列的长度。转换需遵循如下规则：

每次转换只能改变一个字母。
转换过程中的中间单词必须是字典中的单词。
说明:

如果不存在这样的转换序列，返回 0。
所有单词具有相同的长度。
所有单词只由小写字母组成。
字典中不存在重复的单词。
你可以假设 beginWord 和 endWord 是非空的，且二者不相同。
示例 1:

输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

输出: 5

解释: 一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog",
     返回它的长度 5。
示例 2:

输入:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

输出: 0

解释: endWord "cog" 不在字典中，所以无法进行转换。


class Solution {
public:
    int ladderLength(string b, string e, vector<string>& w) {
        int n=w.size();
        int m=b.size();
        if(!n)return 0;
        
        unordered_map<string,int>um;
        unordered_map<string ,int>um1;
        for(int i=0;i<n;i++){
            um[w[i]]=1;
            um[w[i]]=0;
        }
        if(um.find(e)==um.end())return 0;
        
        queue<pair<string,int>>q;
        q.push({b,1});
        
        while(q.size()){
            auto a=q.front();q.pop();
            
            string s=a.first;
            if(s==e)return a.second;
            for(int i=0;i<m;i++){
                char c=s[i];
                for(int j=0;j<26;j++){
                    if('a'+j!=c)s[i]='a'+j;
                    if(um.find(s)!=um.end()&&um[s]==0){
                        q.push({s,a.second+1});
                        um[s]=1;
                    }
                }
                s[i]=c;
            }
        }
        return 0;
    } 
};
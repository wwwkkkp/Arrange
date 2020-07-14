

//140. 单词拆分 II
给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，在字符串中增加空格来构建一个句子，使得句子中所有的单词都在词典中。返回所有这些可能的句子。

说明：

分隔时可以重复使用字典中的单词。
你可以假设字典中没有重复的单词。
示例 1：

输入:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
输出:
[
  "cats and dog",
  "cat sand dog"
]
示例 2：

输入:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
输出:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
解释: 注意你可以重复使用字典中的单词。
示例 3：

输入:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
输出:
[]




//先判断能不能（139题），再用回溯算法
class Solution {
public:
    int n;
    vector<vector<string>>v;
    vector<string>v1;
    vector<string> wordBreak(string s, vector<string>& w) {
        int n1=s.size();
        n=n1;
        if(!n)return {};
        
        bool f[1000];
        memset(f,0,sizeof f);
        for(int i=0;i<n;i++){
            if(i==0||f[i-1]==true){
                for(auto c:w){
                    int m=c.size();
                    string s1=s.substr(i,m);
                    if(s1==c)f[i+m-1]=1;
                    
                }
            }
        }
        
		
		//上面的部分和139题一样，
        if(f[n-1]){
            dfs(s,0,n,w);
			
            v1.clear();
            for(auto c:v){
                string s2;
                for(auto p:c){
                    s2+=p;
                    s2+=' ';
                }
                s2.erase(s2.end()-1);
                v1.push_back(s2);
            }
            return v1;
        }
        return {};
    }
    void dfs(string &s,int a,int b,vector<string>&w){
        if(a==b){
            v.push_back(v1);
            return ;
        }
        int m1=b-a;

        for(auto c:w){
            int m=c.size();
            if(m>m1)continue;
            string s1=s.substr(a,m);
            if(s1==c){
                v1.push_back(s1);
                dfs(s,a+m,b,w);
                v1.pop_back();
            }
        }        
    }

};
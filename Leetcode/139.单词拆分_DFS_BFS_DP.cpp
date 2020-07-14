/*
给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

说明：

拆分时可以重复使用字典中的单词。
你可以假设字典中没有重复的单词。
示例 1：

输入: s = "leetcode", wordDict = ["leet", "code"]
输出: true
解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。
示例 2：

输入: s = "applepenapple", wordDict = ["apple", "pen"]
输出: true
解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
     注意你可以重复使用字典中的单词。
示例 3：

输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
输出: false


*/
//这个解的思想是按照单词查找的顺序来比较的，
//dp[]储存的是[i - ws，i]这个长度的单词是否在wordDict中
bool wordBreak(string s, vector<string>& wordDict) {
	vector<int> dp(s.size() + 1, 0);
	dp[0] = 1;
	for (int i = 0; i <= s.size(); ++i) { //这里的i指的是第几个单词，其实是可以从 1 出发的
		for (auto word : wordDict) {
			int ws = word.size();  //wordDict中每一个string的长度，减小搜索范围
			if (i - ws >= 0) {
				int cur = s.compare(i - ws, ws, word);  //比较个word一样长度的节段中有没有和word一样的数字
				if (cur == 0 && dp[i - ws] == 1) {
					dp[i] = 1;
				}
			}
		}
	}
	return dp[s.size()];
}

//6.5版本
class Solution {
public:
    bool wordBreak(string s, vector<string>& v) {
        int n=s.size();
        if(!n)return false;
        
        bool f[1000];
        memset(f,0,sizeof f);
        for(int i=0;i<n;i++){
            if(i==0||f[i-1]==true){
                for(auto c:v){
                    int m=c.size();
                    string s1=s.substr(i,m);
                    if(s1==c)f[i+m-1]=1;
                    
                }
            }
        }
        return f[n-1];
    }
};


//BFS方法
//BFS方法
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int size=s.size();
        int wsize=wordDict.size();
        queue<int>q;
        map<string,int>m;  //把wordDict改成map形式，可以使用find函数，方便搜索
        for (auto word : wordDict) {
            m[word] = 1;  //注意map的赋值
        }
        int visited[size];  //队列中访问过的点就不用再访问了
        for(int i=0;i<size;i++)
            visited[i]=0;
        q.push(0);
        while(!q.empty()){
            int a=q.front();
            q.pop();
            if (visited[a] == 0) {
                for(int i=a+1;i<=size;i++){
                    map<string, int>::iterator it;  //注意map find的使用方法，find返回的是指针，注意指针的定义 固定格式
                    it = m.find(s.substr(a, i - a));
                    if (it!=m.end()) {
                        q.push(i);
                        if (i == size)
                            return true;
                    }
                }
                visited[a]=1;
            }
        }
        return false;
    }
};



//递归
class Solution {
public:
    bool mem[200][2]; //前面记录的是真假，后面记录的是是否被访问
    map<string, int>m;//把vector改做map，方便find
    bool func(string s, map<string, int> m, int start) {  //s从start开始到最后是否满足单词拆分的要求
														  //这个函数的意思是字符串s的第start位到最后是否满足拆分要求
        if (start == s.size()) //start和s.size()相等,边界条件
            return true;
        if (mem[start][1] ==1) //如果这个点已经被标记了，直接返回结果，不用计算，这就是动态规划和递归的区别
            return mem[start][0];
        for (int i = start + 1; i <= s.size(); i++) {//把[start,s.size()]拆分成两部分，，这里i<=s.size(),要满足边界条件
            map<string, int>::iterator it;
            it = m.find(s.substr(start, i - start));
            if (it != m.end()&&func(s, m, i))) { //如果当前的段[start,i]在map里，func的意思是字符串s的第start位到最后是否满足拆分要求，
												 //如果满足拆分要求，
                    mem[start][0] = 1;           //那从start开始就满足拆分要求
                    mem[start][1] = 1;            //标记这个点，已经访问过了   
            }
			/*
			if (it != m.end()) {
                if (func(s, m, i)) {
                    mem[start][0] = 1;
                    mem[start][1] = 1;
                }else{
					mem[start][0] = 0; //不能这么写，start位置不满足条件是遍历完所有的情况以后得出的结论，不是一种情况不满就不满足了。
					mem[start][1] = 1;
				}

            }
			*/
        }
        mem[start][1] = 1;
        return mem[start][0];  //都拆分完以后，返回结果，如果有一个满足if条件的，这里就是真，没有满足的就是假。，这里很重要，当for里面的所有条件都不满足的时候，才是false
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        for (int i = 0; i < 100; i++) {
            //mem[i] = NULL;
        }
        for (int i = 0; i < wordDict.size(); i++) {
            m[wordDict[i]] = 1;
        }
        bool a = func(s, m, 0);
        return a;
    }
};


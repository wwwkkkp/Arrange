

面试题 17.13. 恢复空格
哦，不！你不小心把一个长篇文章中的空格、标点都删掉了，并且大写也弄成了小写。像句子"I reset the computer. It still didn’t boot!"已经变成了"iresetthecomputeritstilldidntboot"。在处理标点符号和大小写之前，你得先把它断成词语。当然了，你有一本厚厚的词典dictionary，不过，有些词没在词典里。假设文章用sentence表示，设计一个算法，把文章断开，要求未识别的字符最少，返回未识别的字符数。

注意：本题相对原题稍作改动，只需返回未识别的字符数

 

示例：

输入：
dictionary = ["looked","just","like","her","brother"]
sentence = "jesslookedjustliketimherbrother"
输出： 7
解释： 断句后为"jess looked just like tim her brother"，共7个未识别字符。
提示：

0 <= len(sentence) <= 1000
dictionary中总字符数不超过 150000。
你可以认为dictionary和sentence中只包含小写字母。

class Solution {
public:
    int respace(vector<string>& d, string s) {
        int n=s.size();
        if(!n)return 0;
        
        unordered_set<string_view>us;    //string_view 可以提高实际速度
        set<int>se;
        for(const string &c:d){
            us.insert(c);
            se.insert(c.size());
        }
        vector<int>v(se.begin(),se.end());
        
        int f[1010];
        memset(f,0x3f3f3f,sizeof f);
        f[0]=0;
        s='0'+s;

        string_view sv(s);					
        for(int i=1;i<=n;i++){
            for(auto j:v){
                if(j>i)break;
                string_view s1=sv.substr(i-j+1,j);
                if(us.find(s1)!=us.end()){
                    f[i]=min(f[i],f[i-j]);
                }
            }
            f[i]=min(f[i],f[i-1]+1);
        }
        return f[n];
    }
};

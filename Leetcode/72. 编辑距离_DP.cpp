/* 72. 编辑距离
给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符
示例 1:

输入: word1 = "horse", word2 = "ros"
输出: 3
解释: 
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
示例 2:

输入: word1 = "intention", word2 = "execution"
输出: 5
解释: 
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')


*/

//动态规划
/*
回到这道题，当我们在比较 str1(m) 和 str2(n) 的时候也会有两种结果，即 相等 或 不相等，如果说是 相等，那其实我们就不需要考虑这两个字符，问题就直接变成了子问题 str1(0…m-1) 通过多少 cost 变成 str2(0…n-1)，如果说 不相等，那我们就可以执行题目给定的三种变换策略:

将问题中的 str1 末尾字符 str1(m) 删除，因此只需要考虑子问题 str1(0…m-1)，str2(0…n)
将问题中的 str1 末尾字符 str1(m) 替换 成 str2(n)，这里我们就只需要考虑子问题 str1(0…m-1)，str2(0…n-1)
将问题中的 str1 末尾 添加 一个字符 str2(n)，添加后 str1(m+1) 必定等于 str2(n)，所以，我们就只需要考虑子问题 str1(0…m)，str2(0…n-1)

如果你还不是特别清楚问题之间的关系，那就画图表吧，这里我就略过。

状态定义

dp[i][j] 表示的是子问题 str1(0…i)，str2(0…j) 的答案，和常规的字符匹配类动态规划题目一样，没什么特别

递推方程
问题拆解那里其实说的比较清楚了，这里需要把之前的描述写成表达式的形式：
str1(i) == str2(j):
dp[i][j] = dp[i - 1][j - 1]
tip: 这里不需要考虑 dp[i - 1][j] 以及 dp[i][j - 1]，因为
   dp[i - 1][j - 1] <= dp[i - 1][j] +1 && dp[i - 1][j - 1] <= dp[i][j - 1] + 1

str1(i) != str2(j):
dp[i][j] = Math.min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][i - 1]) + 1

你可以看到字符之间比较的结果永远是递推的前提
实现
这里有一个初始化，就是当一个字符串是空串的时候，转化只能通过添加元素或是删除元素来达成，那这里状态数组中存的值其实是和非空字符串的字符数量保持一致。
*/
class Solution {
public:
    int minDistance(string word1, string word2) {
        int s1=word1.size();
        int s2=word2.size();
        if (s1 > s2) {
            swap(s1, s2);
            swap(word1, word2);
        }
        vector<vector<int>> dp(s1+1,vector<int>(s2+1,0));
        for(int i=1;i<s2+1;i++)
            dp[0][i]=i;
        for(int i=1;i<s1+1;i++)
            dp[i][0]=i;
        for(int i=1;i<s1+1;i++){
            for(int j=1;j<s2+1;j++){
                if(word1[i-1]==word2[j-1])
                    dp[i][j]=dp[i-1][j-1];
                else{
                    dp[i][j]=min(dp[i-1][j],min(dp[i-1][j-1],dp[i][j-1]))+1;
                }

            }
        }
       return dp[s1][s2];     
    }
};

//错误演示
class Solution {
public:
    int minDistance(string word1, string word2) {
        int s1=word1.size();
        int s2=word2.size();
        if (s1 > s2) {
            swap(s1, s2);
            swap(word1, word2);
        }
        vector<vector<int>> dp(s1+1,vector<int>(s2+1,0));
        for(int i=1;i<s2+1;i++)
            dp[0][i]=i;
        for(int i=1;i<s1+1;i++)
            dp[i][0]=i;
        for(int i=1;i<s1+1;i++){
            int k=0;
            for(int j=1;j<s2+1;j++){
                if(k==0){
                    
                    if(word1[i-1]!=word2[j-1]&&i>=2&&word1[i-2]==word2[j-1])
                        dp[i][j]=min(dp[i-1][j]+1,dp[i][j-1]);
                    else if(word1[i-1]!=word2[j-1])
                        dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                    else{
                        dp[i][j]=dp[i-1][j-1];  
                        k=1;            
                    }     
                }
                else{
                    if(word1[i-1]!=word2[j-1]&&i>=2&&word1[i-2]==word2[j-1])
                        dp[i][j]=min(dp[i-1][j]+1,dp[i][j-1]+1);
                    else if(word1[i-1]!=word2[j-1])
                        dp[i][j]=min(dp[i-1][j],dp[i][j-1]+1);
                    else
                        dp[i][j]=dp[i-1][j-1];  
                }

                
            }
        }
       return dp[s1][s2];     
    }
};
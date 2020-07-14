
//14. 最长公共前缀
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

示例 1:

输入: ["flower","flow","flight"]
输出: "fl"
示例 2:

输入: ["dog","racecar","car"]
输出: ""
解释: 输入不存在公共前缀。
说明:

所有输入只包含小写字母 a-z 。 



//前缀树，固定模板
class Solution {
public:
    struct com{
        int val;
        com* v[27];
        com(){
            val=1;
            for(int i=0;i<27;i++)
                v[i]=NULL;
        }
    };
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        if(!n)return "";
        
        com* r=new com();
        
        for(int i=0;i<n;i++){
            com* p=r;
            for(auto c:strs[i]){
                if(p->v[c-'a']==NULL){
                    p->v[c-'a']=new com();  //如果这个字符对应的位置不存在，就添加
                }else{
                    p->v[c-'a']->val++;  //如果存在，就在原来的基础上+1，证明有val个字符通过了这个点
                }
                p=p->v[c-'a'];
            }
        }
        int res=0;
        com* q=r;
        while(1){
            int i=0;
            for(;i<27;i++){
                if(q->v[i]&&q->v[i]->val==n){  //最后统计值为n的结点，即有n个字符串通过了这个点
                    q=q->v[i];
                    res++;
                    break;
                }
            }
            if(i==27)break;
        }
        return strs[0].substr(0,res);
    }
};
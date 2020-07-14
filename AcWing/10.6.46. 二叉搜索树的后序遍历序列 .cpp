
//10.6.46. 二叉搜索树的后序遍历序列 

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
如果是则返回true，否则返回false。
假设输入的数组的任意两个数字都互不相同。
样例
输入：[4, 8, 6, 12, 16, 14, 10]

输出：true


class Solution {
public:
    vector<int>s;
    bool verifySequenceOfBST(vector<int> se) {
        s=se;
        return dfs(0,se.size()-1);
    }
    bool dfs(int le,int ri){
        if(le>=ri)return true;
        int i=le;
        for(;i<ri;i++)if(s[ri]<s[i])break;//左边要小于中间数
        for(int j=i;j<ri;j++)if(s[ri]>s[j])return false;//右边要大于中间数
        return dfs(le,i-1)&&dfs(i,ri-1);//递归看左边和右边
    }
    
};
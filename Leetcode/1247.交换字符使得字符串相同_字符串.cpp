/*
5247. 交换字符使得字符串相同 显示英文描述 

有两个长度相同的字符串 s1 和 s2，且它们其中 只含有 字符 "x" 和 "y"，你需要通过「交换字符」的方式使这两个字符串相同。

每次「交换字符」的时候，你都可以在两个字符串中各选一个字符进行交换。

交换只能发生在两个不同的字符串之间，绝对不能发生在同一个字符串内部。也就是说，我们可以交换 s1[i] 和 s2[j]，但不能交换 s1[i] 和 s1[j]。

最后，请你返回使 s1 和 s2 相同的最小交换次数，如果没有方法能够使得这两个字符串相同，则返回 -1 。

 

示例 1：

输入：s1 = "xx", s2 = "yy"
输出：1
解释：
交换 s1[0] 和 s2[1]，得到 s1 = "yx"，s2 = "yx"。
示例 2：

输入：s1 = "xy", s2 = "yx"
输出：2
解释：
交换 s1[0] 和 s2[0]，得到 s1 = "yy"，s2 = "xx" 。
交换 s1[0] 和 s2[1]，得到 s1 = "xy"，s2 = "xy" 。
注意，你不能交换 s1[0] 和 s1[1] 使得 s1 变成 "yx"，因为我们只能交换属于两个不同字符串的字符。
示例 3：

输入：s1 = "xx", s2 = "xy"
输出：-1
示例 4：

输入：s1 = "xxyyxyxyxx", s2 = "xyyxyxxxyx"
输出：4
 

提示：

1 <= s1.length, s2.length <= 1000
s1, s2 只包含 'x' 或 'y'。
*/
//这道题主要是看 x-y 的个数，一个x-y无解，xx-yy 移动一下就可以  xy-yx要移动两下
class Solution {
public:
    int minimumSwap(string s1, string s2) {
        int a=s1.size();
        int b=s2.size();
        int bad=-1;
        if(a!=b)
            return bad;
        int num=0;
        int x1=0,y1=0;
        for(int i=0;i<a;i++){
            if(s1[i]!=s2[i]){
                if(s1[i]=='x'){
                    x1++;
                }
                else{
                    y1++;
                }
            }
        }
        int m1=x1%2;
        int m2=x1/2;
        int n1=y1%2;
        int n2=y1/2;
        num=m2+n2;
        int ju=m1+n1;
        if(ju==1)
            return bad;
        else if(ju==2){
            num+=2;
            return num;
        }
        return num;
    }
};
/*67. 二进制求和

给定两个二进制字符串，返回他们的和（用二进制表示）。

输入为非空字符串且只包含数字 1 和 0。

示例 1:

输入: a = "11", b = "1"
输出: "100"
示例 2:

输入: a = "1010", b = "1011"
输出: "10101"

*/

class Solution {
public:
    string addBinary(string a, string b) {
        int sizea = a.size();
        int sizeb = b.size();
        if(!sizea) return b;
        if(!sizeb) return a;
        int n = max(sizea, sizeb) + 1;
        string s(n, '0');
        int n1 = n;
        int i, j;
        for (i = sizea - 1, j = sizeb - 1; i >= 0 || j >= 0; i--, j--) {
            n--;
            char c = s[n];
            if (i >= 0 && j >= 0) {
                s[n] = ((s[n] - '0') + (a[i] - '0') + (b[j] - '0')) % 2 + '0';
                s[n - 1] = ((c - '0') + (a[i] - '0') + (b[j] - '0')) / 2 + '0';
            }
            else if (i >= 0) {
                s[n] = ((s[n] - '0') + (a[i] - '0')) % 2 + '0';
                s[n - 1] = ((c - '0') + (a[i] - '0')) / 2 + '0';
            }
            else if (j >= 0) {
                s[n] = ((s[n] - '0') + (b[j] - '0')) % 2 + '0';
                s[n - 1] = ((c - '0') + (b[j] - '0')) / 2 + '0';
            }
        }
        string s1;
        if (s[0] == '0') {
			s.erase(0,1);
        }
        return s;
    }
};


//6.23版本
class Solution {
public:
    string addBinary(string a, string b) {
        while(a.size()&&a[0]=='0')a.erase(0,1);
        while(b.size()&&b[0]=='0')b.erase(0,1);
        
        int n=a.size();
        int m=b.size();
        if(!n&&!m)return "0";
        
        int k=n-m;
        if(k>0)work(b,k);
        else if(k<0)work(a,-1*k);   //补齐
        
        int w=max(n,m);
        string s(w,'0');
        int j=0;
        for(int i=s.size()-1;i>=0;i--){
            s[i]=(a[i]-'0'+b[i]-'0'+j)%2+'0';
            j=(a[i]-'0'+b[i]-'0'+j)/2;  //是否进位
        }
        if(j==1)s='1'+s;
        return s;
    }
     void work(string &b,int k){
         while(k--){
             b='0'+b;
         }
     }
};
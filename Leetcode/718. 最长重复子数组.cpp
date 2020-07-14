
718. 最长重复子数组
给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。

 

示例：

输入：
A: [1,2,3,2,1]
B: [3,2,1,4,7]
输出：3
解释：
长度最长的公共子数组是 [3, 2, 1] 。
 

提示：

1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100


//二分+哈希
class Solution {
public:
    
    int findLength(vector<int>& A, vector<int>& B) {
        int n=A.size();
        int m=B.size();
        if(!n||!m)return 0;
                
        int l=0,r=n;
        while(l<r){
            int mid=(l+r+1)>>1;     //长度为mid的子串，A和B中有没有重复的，如果有，就增长长度，反之减少长度
            if(work(A,B,mid))l=mid;
            else r=mid-1;
        }
        return l;
    }
    bool work(vector<int>&v,vector<int>&v1,int n){
        set<vector<int>>us;
        for(int i=0;i+n<=v1.size();i++){				//先把B的长度为n的子串都列举出来
            us.insert({v1.begin()+i,v1.begin()+i+n});
        }
        for(int i=0;i+n<=v.size();i++){					//然后用A的子串一个一个找
            vector<int>p(v.begin()+i,v.begin()+i+n);
            if(us.find(p)!=us.end()){
                return true;
            }
        }
        return false;
    }
};


//动态规划

class Solution {
public:
    
    int findLength(vector<int>& A, vector<int>& B) {
        A.insert(A.begin(),-1);
        B.insert(B.begin(),-2);
        
        int f[1100][1100];  //第i个数结尾的A，和第j个数结尾的B的最长重复子串
        memset(f,0,sizeof f);
        
        int res=0;
        for(int i=1;i<A.size();i++){
            for(int j=1;j<B.size();j++){
                if(A[i]==B[j]){					//如果当前相等，把那就要在前面的基础上+1;
                    f[i][j]=f[i-1][j-1]+1;
                    res=res<f[i][j]?f[i][j]:res;
                }
            }
        }     
        return res;
    }

};
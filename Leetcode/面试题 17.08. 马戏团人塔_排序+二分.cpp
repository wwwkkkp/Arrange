


//面试题 17.08. 马戏团人塔
有个马戏团正在设计叠罗汉的表演节目，一个人要站在另一人的肩膀上。出于实际和美观的考虑，在上面的人要比下面的人矮一点且轻一点。已知马戏团每个人的身高和体重，请编写代码计算叠罗汉最多能叠几个人。

示例：

输入：height = [65,70,56,75,60,68] weight = [100,150,90,190,95,110]
输出：6
解释：从上往下数，叠罗汉最多能叠 6 层：(56,90), (60,95), (65,100), (68,110), (70,150), (75,190)
提示：

height.length == weight.length <= 10000


//排序+二分
class Solution {
public:
    static  bool com(const vector<int>&p,const vector<int>&q){
        if(p[0]!=q[0])return p[0]<q[0];
        else return p[1]>q[1];
    }
    
    int bestSeqAtIndex(vector<int>& h, vector<int>& w) {
        int n=h.size();
        if(!n)return  0;
        
        vector<vector<int>>v(n,vector<int>(2,0));
        for(int i=0;i<n;i++){
            v[i][0]=h[i];
            v[i][1]=w[i];
        }
        
        sort(v.begin(),v.end(),[](const vector<int>&p,const vector<int>&q){  //二维数组的排序，lambda表达式
            if(p[0]!=q[0])return p[0]<q[0];
            else return p[1]>q[1];            
        });   //注意这里的排序是先按h的大小从小到大排序，当h相同的时候，按w的大小从大到小排序，，如果都是从小到大排序，注意反例:[2,2]  [2,3]
		
        //sort(v.begin(),v.end(),com);  //第二种排序方法是调用外部的函数，时间上差不多
        
        vector<int>v1;
        v1.push_back(v[0][1]);//下面的步骤和LeetCode 300题是一样的
        for(int i=1;i<n;i++){
            if(v1.back()<v[i][1])v1.push_back(v[i][1]);
            else {
                int l=0,r=v1.size()-1;
                while(l<r){
                    int mid=l+r>>1;
                    if(v1[mid]>=v[i][1])r=mid;
                    else l=mid+1;
                }
                v1[r]=min(v1[r],v[i][1]);
            }
        }
        return v1.size();
    }
};
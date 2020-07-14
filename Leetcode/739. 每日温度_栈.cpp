

739. 每日温度
根据每日 气温 列表，请重新生成一个列表，对应位置的输出是需要再等待多久温度才会升高超过该日的天数。如果之后都不会升高，请在该位置用 0 来代替。

例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。

提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。



const int N=30010;
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int n=T.size();
        if(!n)return {};
        
        T.insert(T.begin(),0);
        T.push_back(0);
        n+=2;
        int tt=0,q[N];
        vector<int>v;
        q[0]=n-1;
        for(int i=n-2;i>0;i--){
            while(tt>=1&&T[q[tt]]<=T[i])tt--;
            if(tt==0) v.push_back(0);     //根据题意，当栈里面什么都没有的时候，就是0，
            else v.push_back(q[tt]-i);
            q[++tt]=i;
        }
        //vector<int>v1(v.begin()+1,v.end()-1);
        reverse(v.begin(),v.end());
        return v;
        
    }
};
/*数组中只出现一次的数字
题目描述
一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。
*/


//哈希	
class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        unordered_map<int,int>um;
        int n=data.size();
        unordered_map<int,int>::iterator it;
        int num[2],j=0;
        for(int i=0;i<n;i++){
            it=um.find(data[i]);
            if(it==um.end())
                um[data[i]]=1;
            else
                um[data[i]]++;
        }
        for(it=um.begin();it!=um.end();it++){
            if(it->second==1 && j<=1)
                num[j++]=it->first;
        }
        *num1 = num[0];
        *num2 = num[1];
    }
};


//605. 种花问题
假设你有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花卉不能种植在相邻的地块上，它们会争夺水源，两者都会死去。

给定一个花坛（表示为一个数组包含0和1，其中0表示没种植花，1表示种植了花），和一个数 n 。能否在不打破种植规则的情况下种入 n 朵花？能则返回True，不能则返回False。

示例 1:

输入: flowerbed = [1,0,0,0,1], n = 1
输出: True
示例 2:

输入: flowerbed = [1,0,0,0,1], n = 2
输出: False
注意:

数组内已种好的花不会违反种植规则。
输入的数组长度范围为 [1, 20000]。
n 是非负整数，且不会超过输入数组的大小。



//递推
class Solution {
public:
    bool canPlaceFlowers(vector<int>& v, int n) {
        int m=v.size();
        if(!m&&n)return false;
        if(!m&&!n)return true;
        
        v.insert(v.begin(),0);
        int f[20010];			//前i颗点最多能种多少颗树
        for(int i=1;i<=m;i++){
            if(v[i]==1){
                if(i-2>=0)f[i]=f[i-2];
                else f[i]=0;
            }else{
                if(v[i-1]==1)f[i]=f[i-1];
                else {
                    if(i-2>=0)f[i]=max(f[i-2]+1,f[i-1]);
                    else f[i]=1;
                }
            }
        }
        return f[m]>=n;
    }
};


//贪心，如果出现三个连续的0，种一颗树
class Solution {
public:
    bool canPlaceFlowers(vector<int>& v, int n) {
        int m=v.size();
        if(!m&&n)return false;
        if(!m&&!n)return true;
        
        int k=0;
        v.insert(v.begin(),0);
        v.push_back(0);
        for(int i=1;i<=m;i++){
            if(v[i]==0&&v[i-1]==0&&v[i+1]==0){
                k++;
                v[i]=1;
            }
        }
        return k>=n;
    }
};
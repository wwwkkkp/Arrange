


//1054. 距离相等的条形码
在一个仓库里，有一排条形码，其中第 i 个条形码为 barcodes[i]。

请你重新排列这些条形码，使其中两个相邻的条形码 不能 相等。 你可以返回任何满足该要求的答案，此题保证存在答案。

 

示例 1：

输入：[1,1,1,2,2,2]
输出：[2,1,2,1,2,1]
示例 2：

输入：[1,1,1,1,2,2,3,3]
输出：[1,3,1,3,2,1,2,1]
 

提示：

1 <= barcodes.length <= 10000
1 <= barcodes[i] <= 10000



//堆，这道题的思路是：先统计每个数有多少，然后建一个大顶堆，判断标准是个数，每次拿出最多的数和第二多的数，放在vector中，如果有剩余，继续放在堆里面
class Solution {
public:
    struct com{
        bool operator()(pair<int,int>&a,pair<int,int>&b){  //重载运算符()
            return a.second<b.second;
        }
    };
    vector<int> rearrangeBarcodes(vector<int>& b) {
        unordered_map<int,int>um;
        for(auto c:b)um[c]++;
        
        priority_queue<pair<int,int>,vector<pair<int,int>>,com>q; //重点：关于组合的大顶堆的设计，判断标准必须是一个结构体，然后去重载()
        for(auto c:um)q.push(c);
        
        vector<int>v;
        
        while(q.size()){
            auto p=q.top();q.pop();
            if(q.size()==0) {v.push_back(p.first);break;}//取出一个数以后没有数了，就退出了
            auto w=q.top();q.pop();
            v.push_back(p.first);
            v.push_back(w.first);
            p.second--;w.second--;
            if(p.second)q.push(p);//如果有剩余，继续放在堆里面
            if(w.second)q.push(w);
        }
        return v;
    }
};


//16.7.53. 最小的k个数 

输入n个整数，找出其中最小的k个数。
注意：
数据保证k一定小于等于输入数组的长度;
输出数组内元素请按从小到大顺序排序;
样例
输入：[1,2,3,4,5,6,7,8] , k=4

输出：[1,2,3,4]


//基本题
class Solution {
public:
    vector<int> getLeastNumbers_Solution(vector<int> &input, int k) {
        priority_queue<int,vector<int>,greater<int>>pq;
        for(int i=0;i<input.size();i++){
            pq.push(input[i]);
        }
        vector<int>v;
        while(k--){
            v.push_back(pq.top());
            pq.pop();
        }
        return v;
    }
};
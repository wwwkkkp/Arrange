//3.1452. 寻找矩阵的极小值
/* 
给定一个 n×n的矩阵，矩阵中包含 n×n个 互不相同 的整数。
定义极小值：如果一个数的值比与它相邻的所有数字的值都小，则这个数值就被称为极小值。
一个数的相邻数字是指其上下左右四个方向相邻的四个数字，另外注意，处于边界或角落的数的相邻数字可能少于四个。
要求在O(nlogn)的时间复杂度之内找出任意一个极小值的位置，并输出它在第几行第几列。
本题中矩阵是隐藏的，你可以通过我们预设的 函数 query来获得矩阵中某个位置的数值是多少。
例如，
query(a,b)即可获得矩阵中第 a行第b列的位置的数值。
注意： 
矩阵的行和列均从0开始编号。
query()函数的调用次数不能超过(n+2)×⌈log2n⌉+n。
答案不唯一，输出任意一个极小值的位置即可。
数据范围1≤n≤300，矩阵中的整数在int范围内。
输入样例：
[[1, 2, 3], [4, 5, 6], [7, 8, 9]]
输出样例：
[0, 0]
*/
//这道题用二分法，当时间或者空间复杂度要求出现logn的时候，首先应该想到二分

// Forward declaration of queryAPI.
// int query(int x, int y);
// return int means matrix[x][y].

class Solution {
public:
    vector<int> getminlimumValue(int n) {
         
        int left=0;
		int right =n-1;
		while(left<right){
			int mid=(left+right)/2;
			int minl=INT_MAX;
			int x=0;
			for(int i=0;i<n;i++){
				int t=query(i,mid);
				if(minl>t){
					minl=t;
					x=i;
				}
			}
			int leftval=mid>0?query(x,mid-1):INT_MAX;
			int rightval=mid<n-1?query(x,mid+1):INT_MAX;
			
			if(minl<leftval&&minl<rightval)return {x,mid};
			else if(min>leftval) right=mid-1;
			else left=mid+1;
		}
		
		int x=0;
		int min=INT_MAX;
		for(int i=0;i<n;i++){
			int t=query(i,left);
			if(min>t){
				min=t;
				x=i;
			}
		}
		return {x,left};
    }
};



//这种方法是二分法，先在中间那一列找出最小值，看这个最小值，如果这个最小值左右两边的数都比最小值大，那就找到了返回，否则，如果有一边小一些，那那一边就一定有解，这样就把搜索范围减少了一半，以此类推

//注意，先按列分再按列中最小值所在行分，直到结果，这样解法上是可以的，但是时间复杂度比nlogn大，因为每次分不一定是二分，有可能只分了一点，导致时间复杂度上升
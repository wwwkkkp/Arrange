/*  456. 132模式
给定一个整数序列：a1, a2, ..., an，一个132模式的子序列 ai, aj, ak 被定义为：当 i < j < k 时，ai < ak < aj。设计一个算法，当给定有 n 个数字的序列时，验证这个序列中是否含有132模式的子序列。

注意：n 的值小于15000。

示例1:

输入: [1, 2, 3, 4]

输出: False

解释: 序列中不存在132模式的子序列。
示例 2:

输入: [3, 1, 4, 2]

输出: True

解释: 序列中有 1 个132模式的子序列： [1, 4, 2].
示例 3:

输入: [-1, 3, 2, 0]

输出: True

*/


bool find132pattern(vector<int>& nums) {
	if (nums.size() < 3) return false;
	stack<int> max;
	int n = nums.size();
	int third = INT_MIN;//初始化不能为0，因为要进行比较，初始化为0会出错。
	for (int i = n - 1; i >= 0; i--)  //从后往前遍历，third是第三个数，堆栈中的数永远是位置在third前面，但是值比third的数，如果新的数比third小的话，那就符合条件
	{
		if (nums[i] < third) return true;
		while (!max.empty() && nums[i] > max.top())//若找到比栈中还大的元素，则更新
		{
			third = max.top();
			max.pop();
		}
		max.push(nums[i]);
	}
	return false;
}
//重要举例：721.账户合并：当两个数组寻找共同元素，如果有就合并的时候，用并查集+哈希表
/*
给定一个列表 accounts，每个元素 accounts[i] 是一个字符串列表，其中第一个元素 accounts[i][0] 是 名称 (name)，其余元素是 emails 表示该帐户的邮箱地址。

现在，我们想合并这些帐户。如果两个帐户都有一些共同的邮件地址，则两个帐户必定属于同一个人。
请注意，即使两个帐户具有相同的名称，它们也可能属于不同的人，因为人们可能具有相同的名称。一个人最初可以拥有任意数量的帐户，但其所有帐户都具有相同的名称。

合并帐户后，按以下格式返回帐户：每个帐户的第一个元素是名称，其余元素是按顺序排列的邮箱地址。accounts 本身可以以任意顺序返回。

例子 1:

Input: 
accounts = 
[["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]

Output: 
[["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]

Explanation: 
  第一个和第三个 John 是同一个人，因为他们有共同的电子邮件 "johnsmith@mail.com"。 
  第二个 John 和 Mary 是不同的人，因为他们的电子邮件地址没有被其他帐户使用。
  我们可以以任何顺序返回这些列表，例如答案[['Mary'，'mary@mail.com']，['John'，'johnnybravo@mail.com']，
  ['John'，'john00@mail.com'，'john_newyork@mail.com'，'johnsmith@mail.com']]仍然会被接受。

*/


int find(vector<int>& P, int x) {  // vector中没有find，所以要新建一下 ，，并查集的精髓之一
	return P[x] == x ? x : P[x] = find(P, P[x]); //含数据压缩，递归查找，直到找到头
}

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
	unordered_map<string, vector<int>> hash;
	vector<int> P(accounts.size(), 0);
	//将邮箱添加到hash中，当出现相同的邮箱的时候，添加后缀  如：  {"johnsmith@mail.com",[0,2]}
	for (int i = 0; i < accounts.size(); ++i) {
		P[i] = i;
		for (int j = 1; j < accounts[i].size(); ++j) {
			hash[ string(accounts[i][j]) ].push_back(i);  //unordered_map或者map在用这种方式添加的时候，一定要加上数据类型
		}
	}
	//查账户
	unordered_map<string, vector<int>>::iterator it;
	for (it = hash.begin(); it != hash.end(); ++it) {  //对哈希表的遍历，也可以用到vector，map等
		vector<int>& v = it->second;
		for (int j = 0; j < v.size(); ++j) {
			int jp = find(P, v[j]);   //在P中寻找v[j]，
			int ip = find(P, v[0]);
			if (jp != ip) {
				P[jp] = ip;   // 当 ip=0 , jp=2 是，就把P[2]=0:根结点赋予
			}
		}
	}
	
	//根据 P 合并账户
	vector<vector<string>> ans(accounts.size());  //这里必须加数量，因为后面要用索引号
	for (it = hash.begin(); it != hash.end(); ++it) {
		vector<int>& v = it->second;  //每个邮箱出现的索引号
		int r = find(P, v[0]);        //沿索引号查找
		if (ans[r].empty()) {
			ans[r].push_back(accounts[r][0]);  //添加表头
		}
		ans[r].push_back(it->first);    //把索引号的一样的邮箱添加到一起
	}
	
	int p = 0;
	vector<vector<string>> ans1;
	for (int i = 0; i < ans.size(); ++i) {
		if (ans[i].size()) {
			sort(ans[i].begin(), ans[i].end());	//排序
			ans1.push_back(ans[i]);  //重新添加，主要是去除没有数的行
		}
	}
	return ans1;
}
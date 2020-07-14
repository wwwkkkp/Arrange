/*  49. 字母异位词分组

给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

示例:

输入: ["eat", "tea", "tan", "ate", "nat", "bat"],
输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
说明：

所有输入均为小写字母。
不考虑答案输出的顺序。

*/

//unordered_map
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<int>> um;
        vector<vector<string>> sv;
        vector<string> st=strs;
        int s=strs.size();
        vector<int> Vec(s);
        for(int i=0;i<s;i++)
            Vec[i]=i;
        for(int i=0;i<s;i++){
            sort(strs[i].begin(),strs[i].end());
            um[strs[i]].push_back(Vec[i]);
        }
        unordered_map<string,vector<int>>::iterator it=um.begin();
        for(;it!=um.end();it++){
            vector<int> v=it->second;
            vector<string> str;
            for(int j=0;j<v.size();j++)
                str.push_back(st[v[j]]);
            sv.push_back(str);
        }
        return sv;
    }
};


//附一个简单写法；
vector<vector<string>> groupAnagrams(vector<string>& strs) {
	map<string,vector<string> > ma;
	vector<vector<string>> res;
	for(auto str:strs){  //遍历vector
		string tmp = str;
		sort(tmp.begin(),tmp.end());
		ma[tmp].push_back(str);
	}
	for(const auto& m:ma)  //遍历map
		res.push_back(m.second);
	return res;
}

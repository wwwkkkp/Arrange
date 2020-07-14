/*  5273. 搜索推荐系统
给你一个产品数组 products 和一个字符串 searchWord ，products  数组中每个产品都是一个字符串。

请你设计一个推荐系统，在依次输入单词 searchWord 的每一个字母后，推荐 products 数组中前缀与 searchWord 相同的最多三个产品。如果前缀相同的可推荐产品超过三个，请按字典序返回最小的三个。

请你以二维列表的形式，返回在输入 searchWord 每个字母后相应的推荐产品的列表。

 

示例 1：

输入：products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
输出：[
["mobile","moneypot","monitor"],
["mobile","moneypot","monitor"],
["mouse","mousepad"],
["mouse","mousepad"],
["mouse","mousepad"]
]
解释：按字典序排序后的产品列表是 ["mobile","moneypot","monitor","mouse","mousepad"]
输入 m 和 mo，由于所有产品的前缀都相同，所以系统返回字典序最小的三个产品 ["mobile","moneypot","monitor"]
输入 mou， mous 和 mouse 后系统都返回 ["mouse","mousepad"]
示例 2：

输入：products = ["havana"], searchWord = "havana"
输出：[["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
示例 3：

输入：products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
输出：[["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
示例 4：

输入：products = ["havana"], searchWord = "tatiana"
输出：[[],[],[],[],[],[],[]]
 

提示：

1 <= products.length <= 1000
1 <= Σ products[i].length <= 2 * 10^4
products[i] 中所有的字符都是小写英文字母。
1 <= searchWord.length <= 1000
searchWord 中所有字符都是小写英文字母。

*/

//暴力方法
class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        sort(products.begin(),products.end());
        int prosize=products.size();
        int size=searchWord.size();
        vector<vector<string>>out1(size,vector<string>());
        string s;
        for(int i=0;i<size;i++){
            s.push_back(searchWord[i]); 
            
            for(int j=0;j<prosize;j++){
                string s1;
                if(s.size()<=products[j].size())
                    s1=products[j].substr(0,s.size());
                else
                    continue;
                
                if(s==s1){
                    if(out1[i].size()<3)
                        out1[i].push_back(products[j]);
                    else
                        break;
                }
            }
            if(out1[i].size()==0)
                break;   
        }
        return out1;
    }
};


//前缀树
#include<iostream>
#include<vector>

using namespace std;

class Trie
{
private:
	Trie *next[26] = { nullptr };
	vector<string> words;
public:
	Trie() {}

	void insert(const string& word)                   //插入单词
	{
		Trie *root = this;  //this:常值指针，指向的是调用该函数的指针，也就是suggestedProducts中的root
		for (const auto& w : word) {  //迭代完以后返回的是完整的数
			if (root->next[w - 'a'] == nullptr)root->next[w - 'a'] = new Trie();
			root = root->next[w - 'a'];
			root->words.push_back(word);
		}
	}

	vector<string> startsWith(string prefix)          //查找前缀
	{
		Trie* root = this;
		for (const auto& p : prefix) {
			if (root->next[p - 'a'] == nullptr)return {};
			root = root->next[p - 'a'];//每一个字母是否相等
		}
		if (root->words.size() <= 3)return vector<string>(root->words.begin(), root->words.end());
		else return vector<string>(root->words.begin(), root->words.begin() + 3);
	}
};


vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
	sort(products.begin(), products.end());
	Trie *root = new Trie();
	
	for (const auto& product : products)
		root->insert(product);  //建立前缀树
	
	vector<vector<string>> result;
	
	for (int i = 0; i < searchWord.size(); ++i)
	{
		result.push_back(root->startsWith(searchWord.substr(0, i + 1)));  //搜索前缀树
	}
	return result;
}


int main() {
	vector<string> products = { "mobile","mouse","moneypot","monitor","mousepad" };
	suggestedProducts(products, "mouse");
}
/*5298. 口算难题
给你一个方程，左边用 words 表示，右边用 result 表示。

你需要根据以下规则检查方程是否可解：

每个字符都会被解码成一位数字（0 - 9）。
每对不同的字符必须映射到不同的数字。
每个 words[i] 和 result 都会被解码成一个没有前导零的数字。
左侧数字之和（words）等于右侧数字（result）。 
如果方程可解，返回 True，否则返回 False。

 

示例 1：

输入：words = ["SEND","MORE"], result = "MONEY"
输出：true
解释：映射 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
所以 "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652
示例 2：

输入：words = ["SIX","SEVEN","SEVEN"], result = "TWENTY"
输出：true
解释：映射 'S'-> 6, 'I'->5, 'X'->0, 'E'->8, 'V'->7, 'N'->2, 'T'->1, 'W'->'3', 'Y'->4
所以 "SIX" + "SEVEN" + "SEVEN" = "TWENTY" ,  650 + 68782 + 68782 = 138214
示例 3：

输入：words = ["THIS","IS","TOO"], result = "FUNNY"
输出：true
示例 4：

输入：words = ["LEET","CODE"], result = "POINT"
输出：false
 

提示：

2 <= words.length <= 5
1 <= words[i].length, results.length <= 7
words[i], result 只含有大写英文字母
表达式中使用的不同字符数最大为 10

*/

//JAVA 暴力搜索
// 判断当前映射组合能否让方程可解。sum(word[i]) = result
    private boolean isMatch(int[] map) {
        int sum = 0;
        for (String word: words) {
            int tmp = 0;
            for (char c : word.toCharArray()) {
                tmp *= 10;
                tmp += map[c - 'A'];
            }
            sum += tmp;
        }

        int resultValue = 0;
        for (char c : result.toCharArray()) {
            resultValue *= 10;
            resultValue += map[c - 'A'];
        }

        return sum == resultValue;
    }

    private boolean backTrack(int from, boolean[] visited, int[] map) {
        if (from == charSize) {
            return isMatch(map);
        }

        char curChar = charList.get(from);
        for (int i = 0; i <= 9; i++) {
            if (i == 0 && nonZero[curChar - 'A'] || visited[i]) {
                continue;
            }

            visited[i] = true;
            map[curChar - 'A'] = i;
            boolean isMatch = backTrack(from + 1, visited, map);
            if (isMatch) {
                return true;
            }
            visited[i] = false;
        }

        return false;
    }

    public boolean isSolvable(String[] words, String result) {
        this.words = words;
        this.result = result;
        int resLen = result.length();
        Set<Character> set = new HashSet<>();
        nonZero = new boolean[26];
        for (String word: words) {
            if (word.length() > resLen) {
                return false;
            }

            nonZero[word.charAt(0) - 'A'] = true;
            for (char c : word.toCharArray()) {
                set.add(c);
            }
        }

        nonZero[result.charAt(0) - 'A'] = true;
        for (char c : result.toCharArray()) {
            set.add(c);
        }

        charList = new ArrayList<>(set);
        charSize = charList.size();

        int[] map = new int[26];
        Arrays.fill(map, -1);
        return backTrack(0, new boolean[10], map);
    }

}


//C++ 合并同类项
bool isSolable(vector<string>& words, string result) {
	vector<char> h;
	vector<int> base;
	vector<int> coe(26, 0);
	vector<bool> not_zero(26, false);

	words.push_back(result);
	base.push_back(1);
	for (int i = 1; i <= 8; i++) base.push_back(base.back() * 10);

	for (int j = 0; j < words.size(); j++) {
		string x = words[j];
		for (int i = 0; i < x.size(); i++) {
			if (i == 0) not_zero[x[i] - 'A'] = true;
			h.push_back(x[i]);
			int flag = j == words.size() - 1 ? -1 : 1;
			coe[x[i] - 'A'] += flag * base[x.size() - 1 - i];
		}
	}
	sort(h.begin(), h.end());
	h.erase(unique(h.begin(), h.end()), h.end());

	function<bool(int, int, int)> dfs = [&](int pos, int used, int sum) {
		if (pos == h.size()) return sum == 0;
		for (int i = 0; i < 10; i++) {
			if (used >> i & 1) continue;
			if (i == 0 && not_zero[h[pos] - 'A']) continue;
			if (dfs(pos + 1, used | 1 << i, sum + i * coe[h[pos] - 'A'])) return true;
		}
		return false;
	};
	return dfs(0, 0, 0);
}




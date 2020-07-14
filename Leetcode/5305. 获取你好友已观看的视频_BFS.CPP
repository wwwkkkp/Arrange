/* 5305. 获取你好友已观看的视频
有 n 个人，每个人都有一个  0 到 n-1 的唯一 id 。

给你数组 watchedVideos  和 friends ，其中 watchedVideos[i]  和 friends[i] 分别表示 id = i 的人观看过的视频列表和他的好友列表。

Level 1 的视频包含所有你好友观看过的视频，level 2 的视频包含所有你好友的好友观看过的视频，以此类推。一般的，Level 为 k 的视频包含所有从你出发，最短距离为 k 的好友观看过的视频。

给定你的 id  和一个 level 值，请你找出所有指定 level 的视频，并将它们按观看频率升序返回。如果有频率相同的视频，请将它们按名字字典序从小到大排列。

示例 1：

输入：watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
输出：["B","C"] 
解释：
你的 id 为 0 ，你的朋友包括：
id 为 1 -> watchedVideos = ["C"] 
id 为 2 -> watchedVideos = ["B","C"] 
你朋友观看过视频的频率为：
B -> 1 
C -> 2

示例 2：

输入：watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
输出：["D"]
解释：
你的 id 为 0 ，你朋友的朋友只有一个人，他的 id 为 3 。

提示：

	n == watchedVideos.length == friends.length
	2 <= n <= 100
	1 <= watchedVideos[i].length <= 100
	1 <= watchedVideos[i][j].length <= 8
	0 <= friends[i].length < n
	0 <= friends[i][j] < n
	0 <= id < n
	1 <= level < n
	如果 friends[i] 包含 j ，那么 friends[j] 包含 i

*/
//BFS+层级计数

class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& w, vector<vector<int>>& f, int id, int le) {
        queue<int>q;
        q.push(id);
        int n=f.size();
        vector<int> visit(n,0);
        int last=id;
        unordered_map<string,int>up;
        vector<string>out;
        while(!q.empty()){
            int a=q.front();
            q.pop();
            int mid;
            visit[a]=1;
            for(int i=0;i<f[a].size();i++){         
                if(visit[f[a][i]]==0){
                    q.push(f[a][i]); 
                    visit[f[a][i]]=1;
                    mid=f[a][i];
                }
            }
            if(a==last){ //层级计数
                le--;
                last=mid;
            }
            if(le==0){
                while(!q.empty()){
                    int b=q.front();
                    q.pop();
                    for(int i=0;i<w[b].size();i++){ //计数
                    for(int i=0;i<w[b].size();i++){ //计数
                        if(up.find(w[b][i])==up.end())
                            up[w[b][i]]=1;
                        else
                            up[w[b][i]]++;
                    }
                }
                int maxnum=0;
                for(unordered_map<string,int>::iterator it=up.begin();it!=up.end();it++)
                    maxnum=max(maxnum,it->second); //寻找个数最多那个节目
					
                vector<vector<string>>vec(maxnum+1);
				
                for(unordered_map<string,int>::iterator it1=up.begin();it1!=up.end();it1++){ //挨个插入节目进vec中
                    vec[it1->second].push_back(it1->first);
                }
                
                for(int i=0;i<maxnum+1;i++)  //合并
                    if(vec[i].size()){
                        sort(vec[i].begin(),vec[i].end());
                        out.insert(out.end(),vec[i].begin(),vec[i].end());
                    }
            }
        }
        return out;
    }

};
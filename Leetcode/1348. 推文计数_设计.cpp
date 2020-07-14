


//1348. 推文计数
请你实现一个能够支持以下两种方法的推文计数类 TweetCounts：

1. recordTweet(string tweetName, int time)

记录推文发布情况：用户 tweetName 在 time（以 秒 为单位）时刻发布了一条推文。
2. getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime)

返回从开始时间 startTime（以 秒 为单位）到结束时间 endTime（以 秒 为单位）内，每 分 minute，时 hour 或者 日 day （取决于 freq）内指定用户 tweetName 发布的推文总数。
freq 的值始终为 分 minute，时 hour 或者 日 day 之一，表示获取指定用户 tweetName 发布推文次数的时间间隔。
第一个时间间隔始终从 startTime 开始，因此时间间隔为 [startTime, startTime + delta*1>,  [startTime + delta*1, startTime + delta*2>, [startTime + delta*2, startTime + delta*3>, ... , [startTime + delta*i, min(startTime + delta*(i+1), endTime + 1)>，其中 i 和 delta（取决于 freq）都是非负整数。
 

示例：

输入：
["TweetCounts","recordTweet","recordTweet","recordTweet","getTweetCountsPerFrequency","getTweetCountsPerFrequency","recordTweet","getTweetCountsPerFrequency"]
[[],["tweet3",0],["tweet3",60],["tweet3",10],["minute","tweet3",0,59],["minute","tweet3",0,60],["tweet3",120],["hour","tweet3",0,210]]

输出：
[null,null,null,null,[2],[2,1],null,[4]]

解释：
TweetCounts tweetCounts = new TweetCounts();
tweetCounts.recordTweet("tweet3", 0);
tweetCounts.recordTweet("tweet3", 60);
tweetCounts.recordTweet("tweet3", 10);                             // "tweet3" 发布推文的时间分别是 0, 10 和 60 。
tweetCounts.getTweetCountsPerFrequency("minute", "tweet3", 0, 59); // 返回 [2]。统计频率是每分钟（60 秒），因此只有一个有效时间间隔 [0,60> - > 2 条推文。
tweetCounts.getTweetCountsPerFrequency("minute", "tweet3", 0, 60); // 返回 [2,1]。统计频率是每分钟（60 秒），因此有两个有效时间间隔 1) [0,60> - > 2 条推文，和 2) [60,61> - > 1 条推文。 
tweetCounts.recordTweet("tweet3", 120);                            // "tweet3" 发布推文的时间分别是 0, 10, 60 和 120 。
tweetCounts.getTweetCountsPerFrequency("hour", "tweet3", 0, 210);  // 返回 [4]。统计频率是每小时（3600 秒），因此只有一个有效时间间隔 [0,211> - > 4 条推文。
 

提示：

同时考虑 recordTweet 和 getTweetCountsPerFrequency，最多有 10000 次操作。
0 <= time, startTime, endTime <= 10^9
0 <= endTime - startTime <= 10^4




class TweetCounts {
public:
    unordered_map<string,vector<int>>um;
    TweetCounts() {
        
    }
    
    void recordTweet(string s, int time) {
        um[s].push_back(time);
        
        //vector<int >v=um[s];
        int i=0;
        for(;i<um[s].size();i++){
            if(um[s][i]<time)continue;
            else break;
        }
        um[s].insert(um[s].begin()+i,time); //这里时间复杂度应该是线性的
    }
    
    vector<int> getTweetCountsPerFrequency(string f, string s, int b, int e) {
        vector<int>v=um[s];
        
        int ju=0;
        if(f=="minute")ju=60;
        else if(f=="hour")ju=3600;
        else ju=3600*24;
        
        int k=(e-b+1)/ju+((e-b+1)%ju==0?0:1);
        vector<int>v1(k,0);
        int res=0;
        int j=0,i=0;
        while(j<v.size()&&v[j]<b)j++;
        for(;j<v.size()&&v[j]<e+1;j++){    
            if(v[j]>=b+i && v[j]<min(b+i+ju,e+1)){res++;continue;}
            
            v1[i/ju]=res;
            i+=ju;
            res=0;
            j--;
        }
        v1[i/ju]=res;
        return v1;
        return {};
    }
};

/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 = obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */
 
 
 //查询好方法lower_bound
 class TweetCounts {
	unordered_map<string,set<int>> m;  //注意容器是set，自动排序
public:
    TweetCounts() {
        
    }
    
    void recordTweet(string tweetName, int time) {
        m[tweetName].insert(time);
    }
    
    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
        int gap;
        if(freq == "minute")
        	gap = 60;
        else if(freq == "hour")
        	gap = 3600;
        else//"day"
        	gap = 3600*24;
        if(!m.count(tweetName))
        	return {};
        vector<int> ans;
        int count, end_t;
        while(startTime <= endTime)
        {
        	count = 0;
        	end_t = min(endTime, startTime + gap-1);
        	auto beg = m[tweetName].lower_bound(startTime); //返回比startTime大的最小的那个数的地址
        	auto end = m[tweetName].upper_bound(end_t);     //返回比end_t大的最小的那个数的地址
        	for(auto it = beg; it != end; it++)
        	{
        		count++;
        	}
        	ans.push_back(count);
        	startTime += gap;
        }
        return ans;
    }
};
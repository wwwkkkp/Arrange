

//8.《C++海量数据处理（一）： 查重 与 top K问题的分析与实现》

//布隆过滤器:
/*布隆过滤器是一种采用hash法进行查重的工具。*/它将每一条数据进行n次独立的hash处理，每次处理得到一个整数，总共得到n个整数。使用一个很长的数组表示不同的整数，每一次插入操作把这n个整数对应的位置的0设置为1（如果已经被设置为1则不变）

例如：在100w个数中找出重复出现的数
设置n=2,3,5,7,11,13,17;新建一个17位的二进制位m，让这100w个数分类求余n中的数，，得到的结果可能是 1,2,3,6,9,10,16,那将m的第 1,2,3,6,9,10,16 全部置1，如果这些位已经全部是1了，那说明这个数已经出现过了,

/布隆过滤器是允许错误的，但是可以大大地节省空间和提高效率/，布隆过滤器还有一个缺点，不能删除数据，因为删除一个数会影响其他数

//BitMap　
比如有2.5亿个整数中找出不重复的整数的个数，内存空间不足以容纳这2.5亿个整数。
一个数字的状态只有三种，分别为不存在，只有一个，有重复。因此，我们只需要2 bits就可以对一个数字的状态进行存储了，假设我们设定一个数字不存在为00，存在一次01，存在两次及其以上为11。那我们大概需要存储空间几十兆左右。接下来的任务就是遍历一次这2.5亿个数字。

如果对应的状态位为00，则将其变为01；
如果对应的状态位为01，则将其变为11；
如果为11，对应的状态位保持不变。

最后，我们将状态位为01的进行统计，就得到了不重复的数字个数，时间复杂度为O(n)。

分治法hash分组:
如果有两份50G的数据，要查重，内存4G，怎么查？
想法是先将50G的数据分别做hash%1000，分成1000个文件，理论上hash做得好那么这1000个文件的大小是差不多接近的。
如果有重复，那么A和B的重复数据一定在相对同一个文件内，因为hash结果是一样的。将1000个文件分别加载进来，一一比对是否有hash重复。这种想法是先把所有数据按照相关性进行分组，相关的数据会处于同样或者接近的位置中，再将小文件进行对比。


//top K问题分析与实现
在几千亿个数据中如何获取10个最大的数？这其实就是一个Top k问题，如何从亿万级的数据中得到前K个最大或者最小的数字;
/一个复杂度比较低的算法就是利用最小堆算法，

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;
int main()
{
	vector<int> vec;
	for (int i = 0; i < 100000; ++i)
	{
		vec.push_back(rand() + i);
	}

	/* 定义小根堆，注意默认为大根堆，若我们求top K小的数
	** 则需要大根堆，定义则可省去堆结构的模板类型参数：
	** priority_queue<int, vector<int>> minHeap;
	*/ 
	priority_queue<int, vector<int>, greater<int>> minHeap; //注意用的是最小堆，
	
	int k = 0;
	for (; k < 10; ++k) // 加入 10 个元素(根据所需top K的K而定)
	{
		minHeap.push(vec[k]);
	}

	/*
	**	遍历剩下的元素依次和堆顶元素进行比较，如果比堆顶元素大，
	**	那么删除堆顶元素，把当前元素添加到小根堆中，元素遍历完成，
	**	堆中剩下的10个元素，就是值最大的10个元素
	*/
	for (; k < vec.size(); ++k)
	{
		if (vec[k] > minHeap.top())
		{
			minHeap.pop();
			minHeap.push(vec[k]);
		}
	}
	
	// 打印结果
	while (!minHeap.empty())
	{
		cout << minHeap.top() << " ";
		minHeap.pop();
	}
	cout << endl;

	return 0;
}

//查重+topK 综合应用
在千万级的数目的数字中 ，找出重复次数最多的前10个

	// 假定数据存储在vec中
	unordered_map<int, int> numMap;
	for (int val : vec)
	{
		numMap[val]++;
	}

	// 封装一个类类型：数字，重复次数
	struct Node
	{
		Node(int v, int c) :val(v), count(c) {}
		
		// 重载 大于运算符，小根堆进行比较时需要用药
		bool operator>(const Node &src)const
		{
			return count > src.count;
		}
		int val;
		int count;
	};

	// 先定义一个小根堆
	priority_queue<Node, vector<Node>, greater<Node>> minheap;

	// 先往堆放k个数据
	int k = 0;
	auto it = numMap.begin();

	// 先从map表中读10个数据到小根堆中，建立top 10的小根堆，最小的元素在堆顶
	for (; it != numMap.end() && k < 10; ++it, ++k)
	{
		minheap.push(Node(it->first, it->second));
	}

	// 把K+1到末尾的元素进行遍历，和堆顶元素比较
	for (; it != numMap.end(); ++it)
	{
		// 如果map表中当前元素重复次数大于，堆顶元素的重复次数，则替换
		if (it->second > minheap.top().count)
		{
			minheap.pop();
			minheap.push(Node(it->first, it->second));
		}
	}
	// 堆中剩下的就是重复次数最大的前k个
	while (!minheap.empty())
	{
		Node node = minheap.top();
		cout << node.val << " : " << node.count << endl;
		minheap.pop();
	}


//重要例子：分治+查重+top k
有一个包含100亿个整数的data.txt二进制文件，全部存储整数，每个整数占4个字节，内存限制400M，求出文件中整数重复出现次数最大的前20个数字，并打印出来，请设计并输出代码。
/*
	100 亿个int数据 ---》 40G大小， 40 * 10 ^ 8 = 4 * 10 ^ 10

	400M -》 400 * 10^6  内存大小是4 * 10 ^ 8

	大约100个文件，将100亿个文件分成100份，然后对每一份进行处理：先将数据装进哈希表中，然后做最小堆处理，完了再处理下一份数据
	如果不分组，
*/
#include <iostream>
#include <cassert>
#include <functional>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

struct MyNode // 将数据和重复次数合并为类类型
{
	MyNode(int data, int count) :mdata(data), mcount(count) {};
	bool operator>(const MyNode& rhs)const // 重载 大于运算符，小根堆进行比较时需要用药
	{
		return this->mcount > rhs.mcount;
	}
	int mdata;
	int mcount;
};

int main()
{
	//FILE* p = fopen("data.txt", "wb");
	//for (long long i = 0; i < 200000; i++)
	//{
	//	int data = rand();
	//	fwrite(&data, 4, 1, p);  // 将数据存入data.txt中
	//}
	//fclose(p);

	p = fopen("data.txt", "rb");
	assert(p != nullptr);

	const int fileNum = 101; // 分割100个文件
	FILE * pfile[fileNum] = { nullptr };
	for (int i = 0; i < fileNum; i++)
	{
		char fileName[20];
		sprintf(fileName, "data%d.txt", i + 1);
		pfile[i] = fopen(fileName, "wb+");
	}

	int data;
	while (fread(&data, 4, 1, p) > 0)
	{
		int index = data % fileNum; // 进行hash映射，将数据映射到相应的小文件中
		fwrite(&data, 4, 1, pfile[index]);
	}

	unordered_map<int, int> Map; // 存储数字和次数的无序map
	priority_queue<MyNode, vector<MyNode>, greater<MyNode>> minHeap; // 小根堆存储

	for (int i = 0; i < fileNum; i++)
	{
		fseek(pfile[i], 0, SEEK_SET); // 将文件指针置为起始位置
		while (fread(&data, 4, 1, pfile[i]) > 0) // 将数据全部存入map表中
		{
			Map[data]++;
		}

		int j = 0;
		auto it = Map.begin();

		if (minHeap.empty())  // 初始先将map中的前20个数据存入小根堆
		{
			for (; it != Map.end() && j < 20; it++, j++)
			{
				minHeap.push(MyNode(it->first, it->second));
			}
		}

		for (; it != Map.end(); it++) // 将当前文件下的剩余数据逐一与堆顶元素比较
		{
			if (it->second > minHeap.top().mcount) // 当前map中数据的重复次数大于堆顶元素的重复次数
			{
				minHeap.pop();
				minHeap.push(MyNode(it->first, it->second));
			}
		}
		Map.clear(); // 清空map表，读取下个文件
	}

	while (!minHeap.empty())
	{
		MyNode cur = minHeap.top();
		cout << cur.mdata << " : " << cur.mcount << endl;
		minHeap.pop();
	}
}


//3.对象池
对象池
对象池可以显著提高性能,/如果一个对象的创建非常耗时或非常昂贵，频繁去创建的话会非常低效。对象池通过对象复用的方式来避免重复创建对象，它会事先创建一定数量的对象放到池中，当用户需要创建对象的时候，直接从对象池中获取即可，用完对象之后再放回到对象池中，以便复用。/
这种方式避免了重复创建耗时或耗资源的大对象，大幅提高了程序性能。

对象池模型适用的场景

需要使用大量对象
这些对象的实例化开销比较大且生存期比较短


效果

节省了创建类实例的开销
节省了创建类实例的时间
存储空间随着对象的增多而增大

/*
** Implementation of Object Pool Automatic Recycling Technology
** AUTHOR：ZYZMZM
** DATE: 31/3/2019
*/

#include<iostream>
using namespace std;

// 对象池的初始个数
const int MEM_NODE_SIZE = 1;

template<typename T>
class CLink
{
public:
	/* 使用Node类型的new运算符重载函数 */
	CLink() { mphead = new Node(); }

	/* 析构函数 */
	~CLink()
	{
		Node* pCur = mphead;
		while (pCur != nullptr)
		{ 
			Node* pNext = pCur->mpnext;
			delete pCur;
			pCur = pNext;
		}
		delete pCur;
		pCur = nullptr;
	}
	
	/* 尾插 */
	void insertTail(const T& val)
	{
		Node* pGet = new Node(val);
		Node* pCur = mphead;
		while (pCur->mpnext != nullptr)
		{
			pCur = pCur->mpnext;
		}
		pCur->mpnext = pGet;
	}
	
	/* 头删 */
	void removeHead()
	{
		Node* pDel = mphead->mpnext;
		if (pDel == nullptr)
		{
			return;
		}
		mphead->mpnext = pDel->mpnext;
		delete pDel;
	}
	
	void show()
	{
		Node* pCur = mphead->mpnext;
		while (pCur != nullptr)
		{
			cout << pCur->mdata << " ";
			pCur = pCur->mpnext;
		}
		cout << endl;
	}
private:
	/* 对象池的简单实现 */
	struct Node
	{
		Node(T data = T()) :mdata(data), mpnext(nullptr) {}
		/*
			给Node类型提供new和delete运算符的重载，
			自定义Node对象的内存管理方式，实现Node对象池功能
		*/
		void* operator new(size_t size)
		{
			cout << "operator new()" << endl;
			Node* pcur = mpObjectPool;
			
			/* 对象池不存在 或 对象池已满 重新开辟新内存 */
			if (mpObjectPool == nullptr)   
			{
				/* 开辟新内存的大小为对象池的个数乘size，即Node的大小 */
				int allocsize = MEM_NODE_SIZE * sizeof(Node);
				
				/* 使用new运算符开辟新内存 */
				mpObjectPool = (Node *)new char[allocsize];
				
				/* 构建对象池，是一段连续的空间 */
				for (pcur = mpObjectPool; 
					pcur < mpObjectPool + MEM_NODE_SIZE - 1; ++pcur)
				{
					pcur->mpnext = pcur + 1;	// 内存连续
				}
				/* 将对象池的末尾结点next指针域置空 */
				pcur->mpnext = NULL;
			}

			/* 若对象池已经存在，那么直接拿到空闲块 */
			pcur = mpObjectPool;
			
			/* 更改对象池空闲块为新的起始地址 */
			mpObjectPool = mpObjectPool->mpnext;
			
			return pcur;
		}

		void operator delete(void* ptr)
		{
			cout << "operator delete()" << endl;
			if (ptr == nullptr)
				return;
				
			/* 进行类型的强制转换 */
			Node* pcur = (Node*)ptr;  
			
			/* 当前对象池起始地址链到归还节点的后边 */
			pcur->mpnext = mpObjectPool;
				
			/* 将归还节点设为对象池新的起始*/
			mpObjectPool = pcur;	
		}
		T mdata;
		Node* mpnext;

		/* 添加一个指向对象池的起始地址的指针 */
		static Node* mpObjectPool;
	};
	Node* mphead;
};

template<typename T>
typename CLink<T>::Node* CLink<T>::Node::mpObjectPool = nullptr;

int main()
{
	CLink<int>link;
	for (int i = 0; i < 10; i++)
	{
		link.insertTail(i);
	}
	link.show();
	link.removeHead();
	link.show();
	link.removeHead();
	link.show();
	link.removeHead();
	link.show();
	link.removeHead();
	link.show();
	return 0;
}

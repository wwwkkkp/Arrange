
//6.利用CAS实现无锁数据结构（栈、队列和链表）

//=============CAS无锁栈================
#include <iostream>
#include <cstring>
using namespace std;

class CStack
{
public:
	CStack(int size);
	~CStack();
	void push(int& val);
	void pop();
	void show();
	bool empty()const;
	bool full()const;
private:
	int* mdata;
	int mtop;   //mtop指向头结点
	int msize;
};
CStack::CStack(int size = 10)
{
	msize = size;
	mtop = 0;
	mdata = new int[msize];
}

CStack::~CStack()
{
	delete[]mdata;
}



/*
*	思路：如果多个线程进行push，我们就要使用CAS操作
*	来保证我们对变量的互斥访问，首先在我们记录下mdata的地址
*	用于扩容前的CAS比较，然后我们进入push操作，在循环中
*	不断更新mtop的值，因为每个线程push都会改变mtop的值
*	请注意扩容操作中的if (mtop == msize)语句，是必不可少的
*	假如某线程正在执行扩容操作的mdata = pChange语句，还没有
*	执行msize *= 2，但此时有一个新线程进入了push函数，如果在
*	扩容前没有if (mtop == msize)语句，那么新线程又会再次扩容。
*/
void CStack::push(int& val)
{
	int* ptmp = mdata; /* ptmp 暂存 mdata*/
	while (1)
	{
		while (mtop >= msize) // 多线程自旋
		{
			if (ptmp != nullptr)
			{
				if (mtop == msize) // 最后两条语句被其他进入push的线程打断，防止多次扩容
				{
					if (__sync_bool_compare_and_swap(&mdata, ptmp, nullptr)) // CAS
					{
						int* pChange = new int[msize * 2];
						for (int i = 0; i < mtop; ++i)
						{
							pChange[i] = ptmp[i];
						}
						delete ptmp;
						mdata = pChange;
						msize *= 2;
					}
				}

			}
		}
		do
		{
			int tmp = mtop; // 循环拿到最新的栈顶元素
			if (mtop >= msize) // 多线程同时进行push，某个线程push后栈满
			{
				break;
			}
			if (__sync_bool_compare_and_swap(&mtop, tmp, tmp + 1)) // CAS
			{
				mdata[tmp] = val;
				return; // push over
			}

		} while (1); // 自旋
	}

	/*==========普通的push操作=========
		if (full())
		{
			int* ptmp = new int[msize * 2];
			for (int i = 0; i < msize; ++i)
			{
				ptmp[i] = mdata[i];
			}
			delete[]mdata;
			mdata = ptmp;
			msize *= 2;
		}
		mdata[mtop++] = val;
	*/
}

/*
*	思路：CAS实现pop操作较push容易一些，我们只需要在自旋循环中
*	不断更新mtop的值，然后进行CAS操作将mtop值减一即可，需要注意
*	的是多个线程pop时，有可能将栈中元素pop空，此时我们直接返回即可。
*/
void CStack::pop()
{
	if (empty())
	{
		return;
	}

	do
	{
		int tmp = mtop;
		if (tmp == 0)
		{
			break;
		}
		if (__sync_bool_compare_and_swap(&mtop, tmp, tmp - 1))// CAS ,满足条件将mtop更新为tmp - 1
		{
			return;
		}
	} while (1);


	// mtop--;
}

bool CStack::empty()const
{
	return mtop == 0;
}

bool CStack::full()const
{
	return mtop == msize;
}

void CStack::show()
{
	for (int i = 0; i < mtop; ++i)
	{
		cout << mdata[i] << " ";
	}
	cout << endl;
}



//=============CAS无锁队列================
#include <iostream>
#include <pthread.h>

using namespace std;

struct Node
{
	Node(int data = 0) :mdata(data), mpnext(nullptr) {}
	int mdata;
	Node* mpnext;
};

class CQueue
{
public:
	CQueue();
	~CQueue();
	void push(int val);
	void pop();
	void show();
private:
	Node* mfront;//mfront指向头结点
	Node* mrear; //mrear等于尾结点
};

//构造函数
CQueue::CQueue()
{
	mfront = new Node();
	mrear = mfront;
}

//析构函数
CQueue::~CQueue()
{
	while (mfront != nullptr)
	{
		Node* pDel = mfront;
		mfront = mfront->mpnext;
		delete pDel;
	}
}

/*
*    思路：push操作我们在自旋体中首先不断更新mrear的值，然后进行CAS操作，
*    CAS操作将尾节点的next指针域置为新节点，然后我们将队列尾节点置为新节点。
*    这里要注意更新尾节点的写法：不能写为newNode，若此刻其它线程进入push，
*    程序将会造成错误。
*/
//插入元素
void CQueue::push(int val)
{
	Node* newNode = new Node(val);
	do
	{
		Node* ptmp = mrear;
		if (__sync_bool_compare_and_swap(&mrear->mpnext, nullptr, newNode))
		{
			mrear = mrear->mpnext; // 这里不能写为newNode，若此刻其它线程进入push，就会造成错误
			return;
		}
	} while (1); // 自旋

	/*Node *newNode = new Node(val);
	mrear->mpnext = newNode;
	mrear = newNode;*/
}


/*
*    思路：pop操作我们首先要判断队列是否为空，若为空，我们直接返回即可。
	 不为空我们开始进行头删，那么同样的，在自旋体中我们不断更新pDel的值，
	 然后判空，再进行CAS操作删除结点，那么我们还需要注意一下若队列中只有
	 一个结点了，我们需要把mrear指向mfront。
*/
//删除一个元素
void CQueue::pop()
{
	Node* pDel = mfront->mpnext;
	if (pDel == nullptr)
	{
		return;
	}

	do
	{
		pDel = mfront->mpnext;

		if (pDel == nullptr)
		{
			return;
		}
		if (__sync_bool_compare_and_swap(&mfront->mpnext, pDel, pDel->mpnext))
		{
			if (pDel->mpnext == nullptr) // 队列中只剩一个结点
			{
				mfront = mrear;
			}
			delete pDel;
			return;
		}
	} while (1);

	/*Node *pDel = mfront->mpnext;
	if (pDel == nullptr)
	{
		return;
	}
	mfront->mpnext = pDel->mpnext;
	delete pDel;*/
}

//打印函数
void CQueue::show()
{
	Node* pCur = mfront->mpnext;
	while (pCur != nullptr)
	{
		cout << pCur->mdata << " ";
		pCur = pCur->mpnext;
	}
	cout << endl;
}




//=============CAS无锁链表================
#include <iostream>
using namespace std;

struct Node
{
	Node(int data = 0)
		:mdata(data), mpnext(nullptr) {};
	int mdata;
	Node* mpnext;
};

class CLink
{
public:
	CLink();
	~CLink();

	void insertHead(int val);
	void insertTail(int val);

	void removeNode(int val);
	void show();

	CLink(const CLink& link) = delete;
	CLink& operator=(const CLink& link) = delete;
private:
	Node* mpHead;
};

CLink::CLink()
{
	mpHead = new Node();
}

CLink::~CLink()
{
	Node* pCur = mpHead;
	while (pCur != nullptr)
	{
		mpHead = mpHead->mpnext;
		delete pCur;
		pCur = mpHead;
	}
}

void CLink::insertHead(int val) //在头部添加，
{
	Node* newNode = new Node(val);
	do
	{
		Node* ptmp = newNode;
		if (__sync_bool_compare_and_swap(&newNode->mpnext, ptmp->mpnext, mpHead->mpnext))  //mHead指向头结点
		{
			mpHead->mpnext = ptmp;
			return;
		}
	} while (1);
}

void CLink::insertTail(int val)
{
	Node* newNode = new Node(val);
	Node* pCur = mpHead;  //注意，是从头结点开始往后遍历的，链表中没有尾结点
	do
	{
		Node* ptmp = newNode;
		Node* ptmpCur = pCur;
		if (__sync_bool_compare_and_swap(&pCur, ptmpCur, ptmpCur))
		{
			while (pCur->mpnext != nullptr) //从头结点一直遍历到尾部，
			{
				Node* ptmploop = pCur;
				if (__sync_bool_compare_and_swap(&pCur, ptmploop, pCur->mpnext));
			}
			if (__sync_bool_compare_and_swap(&pCur, ptmpCur, ptmpCur))
			{
				pCur->mpnext = ptmp;//在尾部添加
				return;
			}

		}
	} while (1);
}

void CLink::removeNode(int val) // 删除值为val的所有节点
{
	Node* pCur = mpHead->mpnext;
	Node* pPri = mpHead;

	do
	{
		Node* ptmp = pCur;
		if (__sync_bool_compare_and_swap(&pCur, ptmp, ptmp))
		{
			while (pCur != nullptr)
			{
				ptmp = pCur;
				Node* ptmpPri = pPri;
				if (pCur->mdata == val && pCur->mpnext != nullptr)
				{
					if (__sync_bool_compare_and_swap(&pCur->mdata, ptmp->mdata, pCur->mpnext->mdata))
					{
					}
					if (__sync_bool_compare_and_swap(&pCur->mpnext, ptmp->mpnext, pCur->mpnext->mpnext))
					{
						ptmp = pCur;
					}
					continue;
				}
				else if (pCur->mdata == val && pCur->mpnext == nullptr)
				{
					if (__sync_bool_compare_and_swap(&pPri->mpnext, ptmpPri->mpnext, nullptr))
					{
					}
					return;
				}
				Node* ptmploop = pCur;
				if (__sync_bool_compare_and_swap(&pCur, ptmploop, pCur->mpnext));

				Node* pPriloop = pPri;
				if (__sync_bool_compare_and_swap(&pPri, pPriloop, pPri->mpnext));

			}
		}
	} while (1);

}

void CLink::show()
{
	Node* pCur = mpHead->mpnext;
	while (pCur != nullptr)
	{
		cout << pCur->mdata << " ";
		pCur = pCur->mpnext;
	}
	cout << endl;
}

int main()
{
	CLink link;
	for (int i = 0; i < 10; i++)
	{
		int data = rand() % 101;
		link.insertHead(data);
	}

	for (int i = 0; i < 5; i++)
	{
		int data = rand() % 101;
		link.insertTail(data);
	}

	link.insertTail(100);
	link.insertTail(9);
	link.insertTail(8);
	link.insertHead(100);
	link.insertHead(100);
	link.insertTail(100);
	link.show();

	link.removeNode(100);
	link.show();
}

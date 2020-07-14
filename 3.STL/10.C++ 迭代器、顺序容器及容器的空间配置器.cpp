
//10.C++ | 迭代器、顺序容器及容器的空间配置器

//实现不带空间配置器的vector,着重看iterator和resize
template<typename T>
class Vector
{
public:
	// 按指定size进行构造，size个空间，没有元素
	Vector(int size = 0):mCur(0),mSize(size)
	{
		if (size == 0)
		{
			mpVec = nullptr;
		}
		else
		{
			mpVec = new T[mSize];
		}
	}
	// 按指定size进行构造,添加size个元素，元素值是val
	Vector(int size, const T &val = T()):mCur(size)
	{
		mpVec = new T[size];
		mSize = size;
		for (int i = 0; i < size; ++i)
		{
			mpVec[i] = val;
			
		}
	}
	// 按[first, last)区间的元素来构造Vector
	Vector(T *first, T *last)
	{
		int size = last - first;
		mSize = size;
		mpVec = new T[mSize];
		for (mCur = 0; mCur < size; first++)
		{
			mpVec[mCur++] = *first;
		}
	}
	// 从末尾添加元素
	void push_back(const T &val)
	{
		if (full())
		{
			resize();
		}
		mpVec[mCur++] = val;
	}
	// 从末尾删除元素
	void pop_back()
	{
		if (empty())
		{
			return;
		}
		--mCur;
	}
	bool full()const
	{
		return mCur == mSize;
	}
	bool empty()const
	{
		return mSize == 0;
	}
	// 返回容器元素的个数
	int size()const
	{
		return mCur;
	}
	// Vector的迭代器
	class iterator
	{
	public:
		iterator(T *argv = nullptr):_mpVec(argv) {}
		void operator++()
		{
			_mpVec++;
		}
		bool operator!=(const iterator &rhs)
		{
			return _mpVec != rhs._mpVec;
		}
		T& operator*()
		{
			return *_mpVec;
		}
	private:
		T *_mpVec;
	};
	iterator begin()
	{
		return iterator(mpVec);
	}
	iterator end()
	{
		return iterator(mpVec + size());
	}
	
private:
	T *mpVec;
	int mCur;
	int mSize;
	// 容器内存2倍扩容
	void resize()
	{
		if (empty())
		{
			mpVec = new T[1];
			mSize = 1;
			mCur = 0;
		}
		else
		{
			T *tmp = new T[mSize * 2];
			for (int i = 0; i < mSize; i++)
			{
				tmp[i] = mpVec[i];
			}
			delete []mpVec;
			mpVec = tmp;
			mSize *= 2;
		}
	}
};
int main()
{
	Vector<int> vec1; // 底层不开辟空间
	//vec1.push_back(10); // 0 - 1 - 2 - 4 - 8 - 16 - 32 - 64 - 128
	//vec1.push_back(20);
	for (int i = 0; i < 20; ++i)
	{
		vec1.push_back(rand() % 100 + 1);
	}
	cout << vec1.size() << endl;
	
	// 用通用的迭代器遍历方式，遍历vec1，并打印容器中所有的元素值
	Vector<int>::iterator it = vec1.begin();
	for (; it != vec1.end() ; ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	Vector<int> vec2(10, 20);

	Vector<int>::iterator it1 = vec2.begin();
	for (; it1 != vec2.end() ; ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	int arr[] = { 12,4,56,7,89 };
	Vector<int> vec3(arr, arr + sizeof(arr) / sizeof(arr[0]));

	Vector<int>::iterator it2 = vec3.begin();
	for (; it2 != vec3.end() ; ++it2)
	{
		cout << *it2 << " ";
	}
	cout << endl;
	return 0;
}


//容器的空间配置器
一般来说，我们习惯的C++内存配置和释放操作是这样的：
class A {};
A* pa = new A;
//...执行其他操作
delete pa;
1234
这里面隐含几个操作，对于new，我们都是先配置内存，然后调用对应的构造函数；而delete则是先调用对应的析构函数，然后释放内存;

/但是我们只需要开辟一定大小内存，并不想去构造对象，删除是只进行对象析构，但不释放这块内存，以后继续留用;/

/使用容器的空间配置器的目的：把对象的内存开辟和对象的构造分开；把对象的析构和内存释放分开。/


// 实现容器的空间配置器
template<typename T>
class Allocator
{
public:
	T* allocate(size_t size) // 开辟内存
	{
		return (T*)malloc(size);
	}
	void deallocate(void *ptr) // 释放内存
	{
		free(ptr);
	}
	void construct(T *ptr, const T &val) // 构造
	{
		new (ptr) T(val);
	}
	void destroy(T *ptr) // 析构
	{
		ptr->~T();
	}
};


// 实现容器的空间配置器
template<typename T>
class Allocator
{
public:
	T* allocate(size_t size) // 开辟内存
	{
		return (T*)malloc(size);
	}
	void deallocate(void *ptr) // 释放内存
	{
		free(ptr);
	}
	void construct(T *ptr, const T &val) // 构造
	{
		new (ptr) T(val);
	}
	void destroy(T *ptr) // 析构
	{
		ptr->~T();
	}
};


//实现带空间配置器Vector
template<typename T, 
		typename allocator = Allocator<T>>
class Vector
{
public:
	// 按指定size进行构造，size个空间，没有元素
	Vector(int size = 0)
		:mCur(0), mSize(size)
	{
		if (size == 0)
		{
			mpVec = nullptr;
		}	
		else
		{
			//mpVec = new T[mSize];
			mpVec = mAllocator.allocate(mSize * sizeof(T));
		}
	}
	
	// 按指定size进行构造,添加size个元素，元素值是val
	Vector(int size, const T &val)
		:mCur(size), mSize(size)
	{
		mpVec = new T[mSize];
		for (int i = 0; i < mSize; ++i)
		{
			mpVec[i] = val;
		}
	}
	
	// 按[first, last)区间的元素来构造Vector
	Vector(T *first, T *last)
	{
		int size = last - first;
		mSize = size;
		mpVec = new T[mSize];
		for (mCur=0; first < last; ++first)
		{
			mpVec[mCur++] = *first;
		}
	}
	
	~Vector() 
	{ 
		//delete[]mpVec; 
		// 析构有效的对象
		for (int i = 0; i < mCur; ++i)
		{
			mAllocator.destroy(mpVec+i);
		}
		// 释放内存
		mAllocator.deallocate(mpVec);
	}
	
	// 从末尾添加元素
	void push_back(const T &val)
	{
		if (full())
			resize();
		//mpVec[mCur++] = val;
		mAllocator.construct(mpVec+mCur, val);
		mCur++;
	}
	
	// 从末尾删除元素
	void pop_back()
	{
		if (empty())
			return;
		--mCur;
		mAllocator.destroy(mpVec+mCur);
	}
	
	bool full()const { return mCur == mSize; }
	bool empty()const { return mCur == 0; }
	
	// 返回容器元素的个数
	int size()const { return mCur; }
	
	// Vector的迭代器
	class iterator
	{
	public:
		iterator(T *p = nullptr) :_ptr(p) {}
		bool operator!=(const iterator &it)
		{
			return _ptr != it._ptr;
		}
		void operator++() { _ptr++; }
		T& operator*() { return *_ptr; }
	private:
		T *_ptr;
	};
	iterator begin() { return iterator(mpVec); }
	iterator end() { return iterator(mpVec + size()); }
	
private:
	T *mpVec;
	int mCur;
	int mSize;
	allocator mAllocator;  // 存储容器的空间配置器

	// 容器内存2倍扩容
	void resize()
	{
		if (0 == mSize)
		{
			mCur = 0;
			mSize = 1;
			mpVec = mAllocator.allocate(mSize * sizeof(T));
		}
		else
		{
			T *ptmp = mAllocator.allocate(2 * mSize * sizeof(T));
			for (int i = 0; i < mSize; ++i)
			{
				mAllocator.construct(ptmp + i, mpVec[i]);	
			}
			for (int i = 0; i < mSize; ++i)
			{
				mAllocator.destroy(mpVec + i);	
			}
			mAllocator.destroy(mpVec);
			mpVec = ptmp;
			mSize *= 2;
		}
	}
};

class A
{
public:
	A() :p(new int[2]) { cout << "A()" << endl; }
	A(const A &src) { cout << "A(const A&)" << endl; }
	~A() { cout << "~A()" << endl; }
private:
	int *p;
};
int main()
{
	A a1, a2, a3;
	cout << "------------" << endl;

	// 这里只需要空间，不需要构造对象  malloc
	Vector<A> vec(100);
	vec.push_back(a1);
	vec.push_back(a2);
	vec.pop_back();
	vec.push_back(a3);
}

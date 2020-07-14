//14.C++ STL顺序容器 —— vector的底层原理解析及实现

vector采用简单的线性连续空间。以两个迭代器start和end分别指向头尾，并以迭代器end_of_storage指向容量尾端。容量可能比(尾-头)还大，多余即备用空间。

template <class T, class Alloc = alloc>  // 预设使用 alloc 为配置器
class vector {
···
protected:
  iterator start; // 表示目前使用空间的头
  iterator finish; // 表示目前 使用空间 的尾
  iterator end_of_storage; // 表示目前 可用空间 的尾

为了降低空间配置时的速度成本，vector实际配置的大小可能比客户端需求量更大一些，已备将来可能的扩充，这便是容量capacity的观念;
/一个vector的容量永远大于等于其大小，一旦容量等于大小，便是满载，下次再有新增元素，整个vector就需要进行扩容。

	iterator begin() { return start; } //开始
	iterator end() { return finish; }	//使用空间的地址
	size_type size() const { return size_type(end() - begin()); }
	size_type max_size() const { return size_type(-1) / sizeof(T); }
	size_type capacity() const { return size_type(end_of_storage - begin()); }  //容量，可用空间的大小
	bool empty() const { return begin() == end(); }
	reference operator[](size_type n) { return *(begin() + n); }

	// 取出第一个元素内容
	reference front() { return *begin(); } 

	// 取出最后一个元素内容
	reference back() { return *(end() - 1); }


//vector的构造与析构
	vector() : start(0), finish(0), end_of_storage(0) {}

	// 以下建构式，允许指定大小 n 和初值 value
	vector(size_type n, const T& value) { fill_initialize(n, value); }
	vector(int n, const T& value) { fill_initialize(n, value); }
	vector(long n, const T& value) { fill_initialize(n, value); }
	explicit vector(size_type n) { fill_initialize(n, T()); }

	// 使用已有vector构造新vector
	vector(const vector<T, Alloc>& x) {
	  start = allocate_and_copy(x.end() - x.begin(), x.begin(), x.end());
	  finish = start + (x.end() - x.begin());
	  end_of_storage = finish;
	}

	// 传入迭代器构造新vector
	template <class InputIterator>
	vector(InputIterator first, InputIterator last) :
	  start(0), finish(0), end_of_storage(0)
	{
	  range_initialize(first, last, iterator_category(first));
	}

vector的析构函数很简单，就是先销毁所有已存在的元素，然后释放所有内存
	~vector() { 
	  destroy(start, finish);  // 销毁容器内的所有元素
	  deallocate();   // 释放容器内存空间
	}
	
//vector的插入与删除
vector的插入删除共有四种方法：
O(1)时间插入：push_back()
O(1)时间删除：pop_back()
O(n)时间插入：insert()
O(n)时间删除：earse()

	// 在容器尾部增加一个元素
	void push_back(const T& x) {
	  if (finish != end_of_storage) {  // 还有备用空间
		construct(finish, x);   // 直接在备用空间中建构元素
		++finish;     // 调整尾部位置
	  }
	  else      // 已无备用空间
		insert_aux(end(), x);	// 扩容操作		
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::insert_aux(iterator position, const T& x) {
	  if (finish != end_of_storage) {  // 还有备用空间
		// 在备用空间起始处建构一个元素，并以vector 最后一个元素值为其初值。    
		construct(finish, *(finish - 1));
		++finish; // 调整尾部位置
	   
		T x_copy = x;
		copy_backward(position, finish - 2, finish - 1);
		*position = x_copy;
	  }
	  else {		// 已无备用空间
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2 * old_size : 1;
		// 以上配置原则：如果原大小为0，则配置 1（个元素大小）；
		// 如果原大小不为0，则配置原大小的两倍，
		// 前半段用来放置原数据，后半段准备用来放置新数据。

		iterator new_start = data_allocator::allocate(len); // 实际配置
		iterator new_finish = new_start;
		__STL_TRY {
		  // 将原vector 的内容拷贝到新 vector。
		  new_finish = uninitialized_copy(start, position, new_start);
		  // 为新元素设定初值x
		  construct(new_finish, x);
		  // 调整水位。
		  ++new_finish;
		  // 将原vector 的备用空间中的内容也忠实拷贝过来（啥用途？）
		  new_finish = uninitialized_copy(position, finish, new_finish);
		}
		
		// 析构并释放原 vector
		destroy(begin(), end());
		deallocate();

		// 调整迭代器，指向新vector
		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	  }
	}
当我们以push_back()将新元素插入vector尾端时，该函数首先检查是否有备用空间，如果有，那么直接在备用空间上构造元素，并调整迭代器finish，使vector变大;/如果没有备用空间了，就扩充空间（重新配置、移动数据、释放原空间）。一旦扩充空间，原来的迭代器失效/

	// 删除容器尾部的元素
	void pop_back() {
	  --finish;
	  destroy(finish);
	}
	// 在position位置插入x
	iterator insert(iterator position, const T& x) {
	  size_type n = position - begin();
	  if (finish != end_of_storage && position == end()) {
		construct(finish, x);
		++finish;
	  }
	  else
		insert_aux(position, x);
	  return begin() + n;
	}

	// 在position位置插入从first到last区间的元素
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last){
	  range_insert(position, first, last, iterator_category(first));
	}

	// 在position位置插入n个x
	void insert (iterator pos, int n, const T& x) {
	  insert(pos, (size_type) n, x);
	}
	// 将迭代器 position 所指的元素移除
	iterator erase(iterator position) {
	  if (position + 1 != end()) // 如果 p 不是指向最后一个元素
		// 将 p 之后的元素一一向前递移
		copy(position + 1, finish, position); 

	  --finish;  // 调整水位
	  destroy(finish);
	  return position;
	}

	// 移除[first,last)区间的元素
	iterator erase(iterator first, iterator last) {
	  iterator i = copy(last, finish, first);
	  destroy(i, finish);
	  finish = finish - (last - first);
	  return first;
	}

//vector的其他操作
	/*
		调整容器的长度大小，使其能容纳n个元素。
		如果n小于容器的当前的size，则删除多出来的元素。
		否则，添加采用值初始化的元素。
	*/
	void resize(size_type new_size, const T& x) {
	  if (new_size < size()) 
		erase(begin() + new_size, end());
	  else
		insert(end(), new_size - size(), x);
	}

	void resize(size_type new_size) { resize(new_size, T()); }
	12345678910111213
	// 清除全部元素。注意，并未释放空间，以备可能未来还会新加入元素。
	void clear() { erase(begin(), end()); }
	12
	/*
		预分配n个元素的存储空间。但在空间内不真正创建元素对象，
		所以在没有添加新的对象之前，不能引用容器内的元素。
	*/
	void reserve(size_type n) {
	  if (capacity() < n) {
		const size_type old_size = size();
		iterator tmp = allocate_and_copy(n, start, finish);
		destroy(start, finish);
		deallocate();
		start = tmp;
		finish = tmp + old_size;
		end_of_storage = start + n;
	  }
	}

reserve()与resize()的区别

1,resize()函数和容器的size息息相关。调用resize(n)后，容器的size即为n。至于是否影响capacity，取决于调整后的容器的size是否大于capacity。
2,reserve()函数和容器的capacity息息相关。调用reserve(n)后，若容器的capacity小于n，则重新分配内存空间，从而使得capacity等于n。如果capacity大于等于n，则capacity无变化。
3,容器调用resize()函数后，所有的空间都已经初始化了，所以可以直接访问。
4,reserve()函数预分配出的空间没有被初始化，所以不可访问。



//vector的简单实现
template<typename T>
class Allocator
{
public:
	T* allocate(size_t size) // 开辟内存
	{
		return (T*)malloc(sizeof(T) * size);
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

template<typename T, 
		typename allocator = Allocator<T>>
class Vector
{
public:
	/* 默认构造 */
	Vector(int size = 0)
	{
		if (size == 0)
		{
			_first._ptr = _last._ptr = _end._ptr = nullptr;
		}
		else
		{
			_first._ptr = mAllocator.allocate(size);
			_last._ptr = _first._ptr;
			_end._ptr = _first._ptr + size;
		}
	}

	/* 在vector中构造size个值为value的元素 */
	Vector(int size, const T &val)
	{
		_first._ptr = mAllocator.allocate(size);
		for (int i = 0; i < size; i++)
		{
			mAllocator.construct(_first.ptr + i, val);
		}
		_last._ptr = _end._ptr = _first._ptr + size; 
	}
	
	/* 使用[first,last)区间的元素构造vector */
	Vector(T *first, T *last)
	{
		int length = last - first;
		_first._ptr = mAllocator.allocate(length);
		for (int i = 0; i < length; i++)
		{
			mAllocator.construct(_first._ptr + i, first[i]);
		}
		_last._ptr = _end._ptr = _first._ptr + length; 
	}

	~Vector()
	{
		int length = _last._ptr - _first._ptr;
		for (int i = 0; i < length; i++)
		{
			mAllocator.destroy(_first._ptr + i);
		}
		mAllocator.deallocate(_first._ptr);
	}
	
	/* 尾插 */
	void push_back(const T &val)
	{
		if (full())
		{
			resize();
		}
		mAllocator.construct(_last._ptr++, val);
	}
	
	/* 尾删 */
	void pop_back()
	{
		if (empty())
		{
			return;
		}
		mAllocator.destroy(--_last._ptr);
	}

	/* 判满 */
	bool full()const
	{
		// 谨记，太坑了···
		return _last._ptr == _end._ptr; ·
	}

	/* 判空 */
	bool empty()const
	{
		return _first._ptr == _last._ptr;
	}
	
	int size()const
	{
		return _last._ptr - _first._ptr;
	}

	/* vector的迭代器实现 */
	class iterator
	{
	public:

		friend class Vector<T>;

		iterator(T *p = nullptr):_ptr(p) {}
		bool operator!=(const iterator &it)
		{
			return _ptr != it._ptr;
		}
		void operator++()
		{
			_ptr++;
		}
		T &operator*()
		{
			return *_ptr;
		}

	private:
		T *_ptr;
	};
	/* begin方法 */
	iterator begin()
	{
		return iterator(_first._ptr);
	}

	/* end方法 */
	iterator end()
	{
		return iterator(_first._ptr + size());
	}

	/* insert方法 */
	iterator insert(iterator it, const T &val)
	{
		// 需要判满，若已经满了，需要进行扩容
		if (full())
		{
			int offset = _end._ptr - _first._ptr;
			resize();
			it._ptr = _first._ptr + offset;
		}
		
		// 注意 条件  tmp >= it._ptr
		for (T *tmp = _last._ptr - 1; tmp >= it._ptr ; --tmp) 
		{
			mAllocator.construct(tmp + 1, *tmp);
			mAllocator.destroy(tmp);
		}
		++_last._ptr;
		mAllocator.construct(it._ptr, val);
		return it;
	}

	/* erase方法 */
	iterator erase(iterator it)
	{
		for (T * tmp = it._ptr; tmp < _last._ptr; ++tmp)
		{
			mAllocator.destroy(tmp);
			mAllocator.construct(tmp, *(tmp + 1));
		}
		_last._ptr--;
		return it;
	}

private:
	iterator _first; // 指向起始位置
	iterator _last; // 最后一个元素的下一个位置
	iterator _end; // 指向末尾的下一个位置
	allocator mAllocator;  // 容器的空间配置器

	/* resize方法，扩容 */
	void resize()
	{
		if (empty())
		{
			_first._ptr = mAllocator.allocate(sizeof(T));
			_last._ptr = _first._ptr; // 没有元素 ，last=first
			_end._ptr = _first._ptr + 1;
		}
		else
		{
			int size = _last._ptr - _first._ptr;
			T *tmp = mAllocator.allocate(sizeof(T) * size * 2);
			for (int i = 0; i < size; i++)
			{
				mAllocator.construct(tmp + i, _first._ptr[i]);
			}

			for (int i = 0; i < size; i++)
			{
				mAllocator.destroy(_first._ptr + i);
			}
			mAllocator.deallocate(_first._ptr);

			_first._ptr = tmp;
			_last._ptr = _first._ptr + size;
			_end._ptr = _first._ptr + 2 * size;
		}
	}
};

int main()
{
	Vector<int> vec;
	for (int i = 0; i < 10; i++)
	{
		vec.push_back(rand() % 101);
	}
	cout << vec.size() << endl;

	Vector<int>::iterator it = vec.begin();
	for (;it != vec.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	vec.pop_back();
	vec.pop_back();
	vec.pop_back();

	cout << vec.size() << endl;

	Vector<int>::iterator it1 = vec.begin();
	for (;it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	Vector<int>::iterator it2 = vec.begin();
	vec.insert(it2, 12345);

	Vector<int>::iterator it3 = vec.end();
	vec.insert(it3, 54321);
	it3 = vec.end();
	vec.insert(it3, 123455);

	Vector<int>::iterator it4 = vec.begin();
	for (;it4 != vec.end(); ++it4)
	{
		cout << *it4 << " ";
	}
	cout << endl;
}



//13.SGI STL空间配置器(allocator)设计原理与源码剖析(二)
	/*
	** <stl_alloc.h>部分源码剖析
	** AUTHOR：ZYZMZM
	** DATE: 15/4/2019
	*/

	// 需注意，无模板类型参数
	template <int __inst>
	class __malloc_alloc_template {

	private:

	  /* 以下三个函数处理malloc 或realloc分配内存失败的情况 */
	  static void* _S_oom_malloc(size_t);
	  static void* _S_oom_realloc(void*, size_t);

	#ifndef __STL_STATIC_TEMPLATE_MEMBER_BUG
	  static void (* __malloc_alloc_oom_handler)();
	#endif

	public:

	  /* 一级空间配置器直接使用malloc()开辟内存  */
	  static void* allocate(size_t __n)
	  {
		void* __result = malloc(__n);
		/* 内存不足，改用 _S_oom_malloc() */
		if (0 == __result) __result = _S_oom_malloc(__n);
		return __result;
	  }

	  /* 一级空间配置器直接使用free()释放内存  */
	  static void deallocate(void* __p, size_t /* __n */)
	  {
		free(__p);
	  }

	  /* 一级空间配置器直接使用realloc()追加内存  */
	  static void* reallocate(void* __p, size_t /* old_sz */, size_t __new_sz)
	  {
		void* __result = realloc(__p, __new_sz);
		/* 内存不足，改用 _S_oom_realloc() */
		if (0 == __result) __result = _S_oom_realloc(__p, __new_sz);
		return __result;
	  }

	  /* 
	  ** 设置__set_malloc_handler指向的函数为内存分配操作失败时调用的处理函数 
	  ** 最内部的__f是一个函数指针，其参数为void，返回值为void。
	  ** 首先__set_malloc_handle是一个函数，其参数为形如__f的函数指针，
	  ** 其返回值又是个指针，这个指针的类型是void(*)(),用法应该如下形式：
	  ** void (*foo)();
	  ** void (*bar)();
	  ** foo = __set_malloc_handler(bar);
	  */
	  static void (* __set_malloc_handler(void (*__f)()))()
	  {
		void (* __old)() = __malloc_alloc_oom_handler;
		__malloc_alloc_oom_handler = __f;
		return(__old);
	  }

	};

	// malloc_alloc out-of-memory handling

	#ifndef __STL_STATIC_TEMPLATE_MEMBER_BUG
	/* 初值为0，有待客端设定 */
	template <int __inst>
	void (* __malloc_alloc_template<__inst>::__malloc_alloc_oom_handler)() = 0;
	#endif

	template <int __inst>
	void*
	__malloc_alloc_template<__inst>::_S_oom_malloc(size_t __n)
	{
		void (* __my_malloc_handler)();
		void* __result;

		/* 不断尝试释放、配置、再释放、再配置··· */
		for (;;) { 
			__my_malloc_handler = __malloc_alloc_oom_handler;
			if (0 == __my_malloc_handler) { __THROW_BAD_ALLOC; }
			(*__my_malloc_handler)(); // 调用处理例程，尝试释放内存
			__result = malloc(__n); // 再次尝试配置内存
			if (__result) return(__result);
		}
	}

	template <int __inst>
	void* __malloc_alloc_template<__inst>::_S_oom_realloc(void* __p, size_t __n)
	{
		void (* __my_malloc_handler)();
		void* __result;

		/* 不断尝试释放、配置、再释放、再配置··· */
		for (;;) {
			__my_malloc_handler = __malloc_alloc_oom_handler;
			if (0 == __my_malloc_handler) { __THROW_BAD_ALLOC; }
			(*__my_malloc_handler)(); // 调用处理例程，尝试释放内存
			__result = realloc(__p, __n); // 再次尝试配置内存
			if (__result) return(__result);
		}
	}

	// 注意，以下直接将参数inst指定为0
	typedef __malloc_alloc_template<0> malloc_alloc;

/第一级配置器以 malloc()、free()、realloc() 等 C 函数执行实际的内存配置、释放、重配置操作/,
C++ new-handler 机制是，可以要求系统在配置需求无法被满足时，调用你所指定的函数。但是这里使用的是malloc，而不是new，所以要封装一个类似new-handler的函数

SGI 第一级配置器 allocate() 和 realloc() 都是/*在调用 malloc() 和 realloc() 不成功后，改调用 oom_malloc() 和 oom_realloc()。后两者都有内循环，不断调用 “内存不足处理例程” ，期望在某次调用的时候，能够得到充足的内存分配而完成任务*/

//二级空间配置器
第二级配置器使用的是memory pool，即内存池,/需要防止申请小额区块过多而造成内存碎片。

步骤如下：//具体看https://zhaoyang.blog.csdn.net/article/details/89321130，这里说个大概
对于小于128k的内存申请，用内存池的方法：
1,配置器维护了一个链表，free-list，这个链表分别放大小为 8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128,这16种大小的内存地址，如free-list[3]表示的是大小为32的内存空间的首地址，注意，大小为32的内存空间可能不止一次，由free-list分支串起来，最多放20个，

2,当需要大小为32的内存时，就去free-list[3]找，有就取一块，如果没有，就去内存池中找20块大小为32的内存来，其中1块返回，剩下的19块给free-list管理

3,如果内存池中不足，也有可能返回不足20个，如果内存池空了，那就需要malloc开辟空间，开辟20+n个大小为32的内存，其中1个返回，19个放free-list，n个放内存池，n可以自拟

4,如果最终内存里面的堆区没有内存了，无法为内存池注入新的内存，malloc() 行动失败，_S_chunk_alloc（）就在free-list里寻找有没有 “尚未应用区块，且区块足够大”，找到就挖出一块并交出，找不到就调用第一级配置器，执行仿new-handler函数，再不行就抛出bad_alloc（）异常。


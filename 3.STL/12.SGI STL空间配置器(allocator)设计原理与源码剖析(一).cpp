//12.SGI STL空间配置器(allocator)设计原理与源码剖析(一)

//allocator设计初衷
一般而言，我们所习惯的C++内存配置操作和释放操作是这样的：
  class Foo{...};
  Foo pf=new Foo;       //配置内存，然后构造对象
  delete pf;           //将对象析构，然后释放内存
  
其中，new有两步操作：
1,调用::operator new配置内存
2,调用该对象的构造函数构造对象内容

delete有两步操作
1,调用该对象的析构函数将对象析构
2,调用::operator delete释放内存

为了精密分工，STL allocator将上述两阶段操作区分开来。
1,内存配置由alloc::allocator()负责
2,内存释放操作由alloc::deallocator()负责
3,对象构造由::constructor()负责
4,对象析构由::destroy()负责

头文件：
#include<stl_alloc.h>       //负责内存空间的配置和释放
#include<stl_construct.h>   //负责对象内容的构造与析构


//构造和析构基本工具：construct() 和 destroy()
/*
** <stl_construct.h>部分源码剖析
** AUTHOR：ZYZMZM
** DATE: 15/4/2019
*/


#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#define __SGI_STL_INTERNAL_CONSTRUCT_H

#include <new.h> // 使用定位new，要包含此头文件

/*
** 使用定位new，将初值设定到指针所指的空间上
*/
template <class _T1, class _T2>
inline void _Construct(_T1* __p, const _T2& __value) {
  new ((void*) __p) _T1(__value);
}

/*
** 普通new，调用T1::T1()，即T1的默认构造函数
*/
template <class _T1>
inline void _Construct(_T1* __p) {
  new ((void*) __p) _T1();
}

/*
** _Destroy版本一：接收一个指针，将该指针所指析构
**                 直接调用该对象的析构函数
*/
template <class _Tp>
inline void _Destroy(_Tp* __pointer) {
  __pointer->~_Tp();
}

/*
** _Destroy版本二：接收两个迭代器，准备将[__first,__last)
** 范围内的所有对象析构掉，首先利用__VALUE_TYPE()获得迭代器
** 所指对象的型别，再利用_type_traits<_Tp>判断该型别的析构
** 函数是否无关痛痒(trival destructor)，若是(__true_type),
** 则什么也不做就结束；若否(__false_type)，就以循环方式寻访
** 整个范围，并在循环中每经历一个对象，就调用版本二的_Destroy
** 具体见下面几个函数
*/
template <class _ForwardIterator>
inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last) {
  __destroy(__first, __last, __VALUE_TYPE(__first));
}

/*
** 判断元素的数值型别(value type)，是否有trival destructor
*/
template <class _ForwardIterator, class _Tp>
inline void 
__destroy(_ForwardIterator __first, _ForwardIterator __last, _Tp*)
{
  typedef typename __type_traits<_Tp>::has_trivial_destructor  
          _Trivial_destructor;   //判断该类型的析构函数是否无关痛痒，如果是，就什么操作也不做，如果不是，就依次析构，
  __destroy_aux(__first, __last, _Trivial_destructor());
}

/*
** 若否(__false_type)，即元素的数值型别为no-trival destructor
** 就以循环方式寻访整个范围，并在循环中每经历一个对象，就调用版
** 本二的_Destroy
*/
template <class _ForwardIterator>
void
__destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type)
{
  for ( ; __first != __last; ++__first)
    destroy(&*__first);
}

/*
** 若是(__true_type)，即元素的数值型别为trival destructor，
** 那么就则什么也不做就结束
*/
template <class _ForwardIterator> 
inline void __destroy_aux(_ForwardIterator, _ForwardIterator, __true_type) {}


/*
** 以下是_Destroy版本二针对迭代器为
** char\int\long\float\double\wchar_td 特化版本
*/
inline void _Destroy(char*, char*) {}
inline void _Destroy(int*, int*) {}
inline void _Destroy(long*, long*) {}
inline void _Destroy(float*, float*) {}
inline void _Destroy(double*, double*) {}
#ifdef __STL_HAS_WCHAR_T
inline void _Destroy(wchar_t*, wchar_t*) {}
#endif /* __STL_HAS_WCHAR_T */

// --------------------------------------------------
,
/上述的constructor()的一个版本接受一个指针p和一个初值value，该函数的用途是将初值设定到指针所指的空间上，也就是定位new(placement new)运算子的作用。

而_Destroy的接受范围的版本需要特别注意，当范围非常大时，不断调用析构函数可能会导致效率的极具降低，
所以此时我们需要判断析构函数是否是trival destructor是非常有必要的。 
具体的执行顺序:
	1,_Destroy(first,last)，函数要求析构first到last范围中的对象，
	2,__destroy(__first, __last, __VALUE_TYPE(__first))，查看该对象的析构函数是否无关痛痒，通过第三步查，__VALUE_TYPE是获取迭代器所指向对象的类别
	3,__type_traits<&__VALUE_TYPE(__first)>::has_trivial_destructor  ，就是通过这个方法判断的析构函数是否无关痛痒，结论放在_Trivial_destructor中
	4,	if( _Trivial_destructor ==__false_type)
			挨个执行析构函数；
		else
			什么操作也不做；


//空间的配置与释放

C++的内存配置的基本操作时 ::operator new() 和 ::operator delete()。这两个全局函数相当于C中的 malloc() 和 free() 函数，正是如此SGI STL正是以malloc() 和 free() 完成内存的配置与释放。

考虑到小型区块所可能造成的内存碎片问题,/SGI 设计了双层配置器，第一级配置器直接使用malloc() 和 free()，第二级配置器按照不同情况采用不同策略：
	当配置区块超过128bytes时，视之为"足够大"，调用第一级配置器。
	当配置区块小于128bytes时，视之为"过小"，为了降低额外负担，便采用复杂的memory pool整理方式(内存池)，而不再求助于第一级配置器;;

/整个设计究竟只开放第一级配置器，或者是同时开放第二级配置器，取决于 __USE_MALLOC是否被定义。/
	typedef __malloc_alloc_template<0> malloc_alloc;

	# ifdef __USE_MALLOC
	typedef malloc_alloc alloc; /* 令 alloc 为第二级配置器 */
	# else
	···
	/* 令 alloc 为第二级配置器 */
	typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> alloc;
	#endif /* ! __USE_MALLOC */

无论 alloc 被定义成第一级还是第二级配置器,/ SGI 都将 alloc 进行了上层封装，类似于一个转接器/，使其配置器的接口符合 STL 规范：
	template<class _Tp, class _Alloc>
	class simple_alloc {

	public:
		static _Tp* allocate(size_t __n)
		  { return 0 == __n ? 0 : (_Tp*) _Alloc::allocate(__n * sizeof (_Tp)); }
		static _Tp* allocate(void)
		  { return (_Tp*) _Alloc::allocate(sizeof (_Tp)); }
		static void deallocate(_Tp* __p, size_t __n)
		  { if (0 != __n) _Alloc::deallocate(__p, __n * sizeof (_Tp)); }
		static void deallocate(_Tp* __p)
		  { _Alloc::deallocate(__p, sizeof (_Tp)); }
	};
内部的四个成员函数只是单纯的转调用，调用传递给配置器的成员函数，可能是第一级也有可能是第二级，SGI STL 的所有容器全部用该接口，比如我们常用的vector的定义：
	//默认缺省alloc为空间配置器
	template<class T, class Alloc = alloc> 
	class vector
	{
	protected:
		// 使用了simple_alloc，每次配置一个元素大小
		typedef simple_alloc<value_type, Alloc> data_allocator;
		void deallocate()
		{
			if(...)
				data_allocator::deallocate(start, end_of_storage - start);
		}
		//...
	};


//一、二级空间配置器简述
一级空间适配器是对malloc的简单包装,就是简单的申请空间，调用malloc()和realloc()，如果调用失败，再调用oom_malloc() 和oom_realloc() 清理内存,重复多次后，如果还不成功便调用_THROW_BAD_ALLOC,丢出bad_alloc异常信息。

二级空间配置器对内存的管理减少了小区块造成的内存碎片，
如果所要申请的空间大于128字节，则直接交至一级空间配置器处理，
如果小于128字节，则使用二级空间配置器，它是用一个16个元素的自由链表来管理的，每个位置下挂载着大小（分别为8、16、24、32、48、56、64、72、80、88、96、104、112、120、128字节

关于一、二级空间配置器的具体分析，见下一个cpp

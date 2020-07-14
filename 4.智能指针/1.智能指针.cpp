
//1.智能指针

智能指针的由来：
1,当我们用new申请一块空间之后，必须要用delete去释放这块区域，不然会泄露；
2,同一个区域释放两次，导致释放野指针，程序崩溃，
3,程序异常退出，导致delete语句没有执行;

/由于C++没有自动回收内存机制。为了保证每次申请的空间都能delete，引入了智能指针的机制


智能指针不是一个指针，而是一个栈对象，或者说是一个类，这个类释放空间是通过析构函数完成，当类生命期结束的时候，就调用析构函数管理空间。

C++11为我们提供了 带引用计数的智能指针 和 不带引用计数的智能指针，
包括
auto_ptr，scoped_ptr，unique_ptr:不带计数的智能指针
shared_ptr，weak_ptr:带计数的智能指针;

/引用计数这种计数是为了 防止内存泄露 而产生的。/
基本想法:对于动态分配的对象，进行引用计数，每当增加一次对同一个对象的引用，那么引用对象的引用计数就会增加一次，每删除一次引用，引用计数就会减一，
		 当一个对象的引用计数减为零时，就自动删除指向的堆内存。

RALL资源获取即初始化技术:对于一个对象而言，我们在构造函数的时候申请空间，而在析构函数（在离开作用域时调用）的时候释放空间。

智能指针计数原理：	智能指针类将一个计数器与类指向的对象相关联，引用计数跟踪该类有多少个对象的指针指向同一对象。
					每次创建类的新对象时，初始化指针就将引用计数置为1,/当对象作为另一对象的副本而创建时，拷贝构造函数拷贝指针并增加与之相应的引用计数;
					/对一个对象进行赋值时，赋值操作符减少左操作数所指对象的引用计数（如果引用计数为减至0，则删除对象），并增加右操作数所指对象的引用计数；
					调用析构函数时，析构函数减少引用计数（如果引用计数减至0，则删除基础对象）;

//智能指针的简单实现：

/自定义智能指针，但是这个还不是真正的智能指针类
template<typename T>
class CSmartPtr
{
public:
	// 构造函数
	CSmartPtr(T *ptr = nullptr)
		:mptr(ptr) {}
	~CSmartPtr()  { delete mptr; }

private:
	T *mptr;
};
int main()
{
	CSmartPtr<int> ptr(new int);//注意定义的方法，Ptr就是一个智能指针对象，无论发生什么情况，都会自动执行析构函数，
	return 0;
}

如果上例中的定义方式写成 CSmartPtr<int> *ptr = new CSmartPtr<int>(new int); 那ptr还是一个裸指针，不是智能指针;

/对于下例
CSmartPtr<int> ptr(new int);  //ptr是一个智能指针对象
CSmartPtr<int> ptr1(ptr);     //因为执行的是默认拷贝构造函数，所以是浅复制，ptr1和ptr指向的都是同一个位置，释放的时候肯定会出现二次释放的问题，导致程序错误。

//解决二次释放问题：
C++提供了3个模板：auto_ptr,scoped_ptr,unique_ptr


1,auto_ptr:
auto_ptr通过转移使用权限来来防止值拷贝所带来问题;/所谓权限转移就是说 开辟的动态内存 任何时刻只能由 一个指针指向。/
		源码见：https://zhaoyang.blog.csdn.net/article/details/88921280
auto_ptr在拷贝构造和赋值运算符重载时做了特殊的处理,/都调用了release方法，而release方法的操作是对所有权进行了完全转移,/,
/在拷贝和赋值时，剥夺原对象对指针的拥有权，赋予当前对象对指针的拥有权，/
当前对象获得auto_ptr的指针,/并使原对象的指针置空/，那么只有最后一个auto_ptr智能指针持有资源，原来的auto_ptr都被赋为nullptr了，即原来的auto_ptr全部失效。

	// 拷贝构造函数，调用release方法
	auto_ptr(_Myt& _Right) _THROW0()
		: _Myptr(_Right.release())
		{	// construct by assuming pointer from _Right auto_ptr
		}
	
	// 赋值运算符函数，调用release方法
	template<class _Other>
		_Myt& operator=(auto_ptr<_Other>& _Right) _THROW0()
		{	// assign compatible _Right (assume pointer)
		reset(_Right.release());
		return (*this);
		}
,
/auto_ptr的问题：
1),当转移使用权之后，再访问原来的对象就会产生错误，
	int main()
	{
		auto_ptr<int> ptr(new int);
		auto_ptr<int> ptr1 = ptr;
		*ptr = 10; // error，ptr的资源所有权已被释放，ptr被赋值为 nullptr
		return 0;
	}
2),/如下例，当ptr作值传递时，中间会拷贝构造一个临时的ptr对象p,同时ptr的使用权也转移给了p,ptr成空指针,当函数执行完时，p析构，再调用ptr会发生错误。
	void func(auto_ptr<int> p)
	{
		cout << *p<< endl;
	}

	auto_ptr<int> ptr(new int(1));
	func(ptr);
	cout << *ptr<< endl;	//error，函数调用结束后，ptr的资源所有权已被释放


2,scoped_ptr:
/scoped_ptr从根本上就不允许拷贝和赋值(防赋值、防拷贝)，即禁止使用拷贝构造和赋值运算符的重载。
具体方法:
	//将拷贝构造函数和赋值运算符声明为私有，不允许在类外使用，这样就限制了其所有权的转让
	private:
		scoped_ptr(scoped_ptr const &);
		scoped_ptr & operator=(scoped_ptr const &);

3,unique_ptr

1),unique_ptr 与 auto_ptr 同样都可以改变资源所有权，通过release函数实现,/也就是说，最后还是只有一个智能指针拥有资源。
2),unique_ptr 与 scoped_ptr 同样都是,/禁止了拷贝构造和赋值操作，防止了浅拷贝的发生;
,
/unique_ptr可以通过右值引用的方式进行拷贝复制和赋值，具体实现方式是转移语义；
	// 提供了右值引用的拷贝构造函数
	unique_ptr(unique_ptr && _Right) _NOEXCEPT
		: _Mybase(_Right.release(),
			_STD forward<_Dx>(_Right.get_deleter()))
		{	// construct by moving _Right
		}

	// 提供了右值引用的赋值运算符重函数
	_Myt& operator=(_Myt && _Right) _NOEXCEPT
		{	// assign by moving _Right
		if (this != &_Right)
			{	// different, do the move
			reset(_Right.release());
			this->get_deleter() = _STD forward<_Dx>(_Right.get_deleter());
			}
		return (*this);
		}
	
关于右值引用和转移语义，下章详细说，这里简单说下：转移语义是靠右值引用的方式实现的
int a=1;
int&& b=a;//右值引用，
当右值引用作为函数参数的时候，参数参数是通过引用传递的方式传递的，这时候的函数参数是一个临时对象，是深拷贝的对象，然后临时对象直接赋值给main栈中的对象，转移语义的意思就是令这个临时对象直接变成main()栈中的对象，这样省去了对函数参数对象析构的麻烦，同时省去了返回值临时对象的构建析构	

//带引用计数的智能指针
1,share_ptr:
/shared_ptr允许拷贝和赋值，允许多个智能指针共享同一块堆分配对象的内存 ，其底层实现是以"引用计数"为基础的，通过引用计数来控制空间的释放，
share_ptr指针的计数器是在内存的堆上，

2,weak_ptr:
/weak_ptr是为配合shared_ptr而引入的一种智能指针来协助shared_ptr工作，它可以从一个shared_ptr或另一个weak_ptr对象构造/，
它的构造和析构不会引起引用计数的增加或减少。没有重载 * 和 -> ，但可以使用lock获得一个可用的shared_ptr对象。

weak_ptr的使用更为复杂一点,/它可以指向shared_ptr指针指向的对象内存，却并不拥有该内存，/,/而使用weak_ptr成员lock，则可返回其指向内存的一个share_ptr对象，且在所指对象内存已经无效时，返回指针空值nullptr。
注意：

weak_ptr并不拥有资源的所有权，所以不能直接使用资源。
可以从一个weak_ptr构造一个shared_ptr以取得共享资源的所有权;

/shared_ptr一般被称作强智能指针，weak_ptr被称作弱智能指针.


//带引用计数的智能指针的循环(交叉)引用

class B; 
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	shared_ptr<B> _ptrb; // 指向B对象的智能指针
};
class B
{
public:
	B() { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
	shared_ptr<A> _ptra; // 指向A对象的智能指针
};
int main()
{
	shared_ptr<A> ptra(new A());// ptra指向A对象，A的引用计数为1
	shared_ptr<B> ptrb(new B());// ptrb指向B对象，B的引用计数为1
	
	ptra->_ptrb = ptrb;// A对象的成员变量_ptrb也指向B对象，B的引用计数为2
	ptrb->_ptra = ptra;// B对象的成员变量_ptra也指向A对象，A的引用计数为2

	cout << ptra.use_count() << endl; // 2
	cout << ptrb.use_count() << endl; // 2

	return 0;
}
输出：
A()
B()
ptra.use_count() 2
ptrB.use_count() 2

注意：上式中没有对智能指针对象实行ptra,ptrb进行析构，原因是两者互相指向对方，使得两者的计数都是1，导致泄露



class B;
class A
{
public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
	weak_ptr<B> _ptrb; // 指向B对象的弱智能指针。引用对象时，用弱智能指针
};
class B
{
public:
	B() { cout << "B()" << endl; }
	~B() { cout << "~B()" << endl; }
	weak_ptr<A> _ptra; // 指向A对象的弱智能指针。引用对象时，用弱智能指针
};
int main()
{···}

输出：
A()
B()
ptra.use_count() 1
ptrB.use_count() 1
~B()
~A()

,/将原来在类中的强智能指针修改为弱智能指针，因为我们只是引用对象，那么弱智能指针不会引起引用计数的改变，则上述程序将成功运行。

weak_ptr不会改变资源的引用计数，只是一个观察者的角色。
weak_ptr持有的引用计数，不是资源的引用计数，而是同一个资源的观察者的计数

weak_ptr无法访问对象，需要先通过lock方法提升为shared_ptr强智能指针，才能访问资源；
class B;
class A
{
public:
	A(){cout << "A()" << endl;}
	~A() {cout << "~A()" << endl;}
	weak_ptr<B> _ptrb;
};

class B
{
public:
	B(){cout << "B()" << endl;}
	~B() {cout << "~B()" << endl;}
	weak_ptr<A> _ptra;

	void func()
	{
		// promote -> 提升 弱 -》强（引用计数不为0才能成功）
		shared_ptr<A> sp = _ptra.lock();
		if (sp != nullptr)
		{
			cout << sp->_ptrb.use_count() << endl;
		}
		else
		{
			cout << "sourse not exist!" << endl;
		}
	}
};

/**
总结：
定义对象时，使用强智能指针
引用对象时，使用弱智能指针
*/

//多线程访问共享对象,自定义删除器deleter
/除了堆内存资源，智能指针还可以管理其它资源，比如打开的文件，此时对于文件指针的关闭，就不能用delete了，这时我们需要自定义智能指针释放资源的方式。

unique_ptr智能指针的析构函数源码如下：
	~unique_ptr() noexcept
	{	// destroy the object
		if (get() != pointer())
		{
			this->get_deleter()(get()); // 这里获取底层的删除器，进行函数对象的调用
		}
	}

从unique_ptr的析构函数可以看到，如果要实现一个自定义的删除器，实际上就是定义一个函数对象而已，示例代码如下：
	class FileDeleter
	{
	public:
		// 删除器负责删除资源的函数
		void operator()(FILE *pf)//某个类重载了(),就可以作为函数对象了，也就是函数参数，
		{
			fclose(pf);
			pf = nullptr;
		}
	};
	int main()
	{
		// 由于用智能指针管理文件资源，因此传入自定义的删除器类型FileDeleter
		unique_ptr<FILE, FileDeleter> filePtr(fopen("data.txt", "w"));  //注意：上面的get()，在这里就是FileDeleter，
		return 0;
	}



//2.详解C++11 右值引用、转移语义和完美转发

//右值引用
1,左值和右值
可以取地址的，有名字的，非临时的就是左值；如int a;a是可以取地址的
不能取地址的，没有名字的，临时的就是右值。如数字1，常数是不能取地址的;

/立即数（常数），函数返回的值等都是右值；而非匿名对象(包括变量)，函数返回的引用，const对象等都是左值。

2,右值引用

表达方式：
int &&b=1; //右值引用绑定对象可以是常数，左值引用就不行

右值引用和常引用的区别:
/右值引用是可读可写的；常引用是只读的；

右值引用的目的:
/右值引用的存在并不是为了取代左值引用，而是充分利用右值(特别是临时对象)的构造来减少对象构造和析构操作以达到提高效率的目的，
主要体现方式：
	// 带右值引用参数的拷贝构造函数
	Stack(Stack &&src)
		:msize(src.msize), mtop(src.mtop)
	{
		cout << "Stack(Stack&&)" << endl;
		/*此处没有重新开辟内存拷贝数据，把src的资源直接给当前对象，再把src置空*/
		mpstack = src.mpstack;  
		src.mpstack = nullptr;
	}

	// 带右值引用参数的赋值运算符重载函数
	Stack& operator=(Stack &&src)     
	{
		cout << "operator=(Stack&&)" << endl;
		if(this == &src)
			return *this;
			
		delete[]mpstack;

		msize = src.msize;
		mtop = src.mtop;
		/*此处没有重新开辟内存拷贝数据，把src的资源直接给当前对象，再把src置空*/
		mpstack = src.mpstack;
		src.mpstack = nullptr;
		return *this;
	}

临时量都会自动匹配右值引用版本的成员方法，旨在提高内存资源使用效率，
在上例中，src就是临时量，函数通过值传递，生成了参数src,也就是临时量，然后通过右值引用直接赋给了当前对象,
/对于函数的右值引用，无论是放在函数参数中，还是放在被绑定对象中，都是一样的，实现了深拷贝，实现了转移语义，如
		// 带右值引用参数的拷贝构造函数
	Stack(Stack &&src)
		:msize(src.msize), mtop(src.mtop)
	{
		cout << "Stack(Stack&&)" << endl;
		/*此处没有重新开辟内存拷贝数据，把src的资源直接给当前对象，再把src置空*/
		mpstack = src.mpstack;
		src.mpstack = nullptr;
	}

	// 带右值引用参数的赋值运算符重载函数
	Stack& operator=(Stack &&src)
	{
		cout << "operator=(Stack&&)" << endl;
		if (this == &src)
			return *this;

		delete[]mpstack;

		msize = src.msize;
		mtop = src.mtop;
		/*此处没有重新开辟内存拷贝数据，把src的资源直接给当前对象，再把src置空*/
		mpstack = src.mpstack;
		src.mpstack = nullptr;
		return *this;
	}
	Stack GetStack(Stack &stack)  //左值引用
	{
		Stack tmp(stack.getSize()); //2,普通构造函数
		return tmp;//3,函数的返回值是右值，他会拷贝构造一个临时对象，这时候的tmp是右值，执行带右值引用的拷贝构造函数，然后完成转移语义。
	}

	int main()
	{
		Stack s;  //1,默认构造函数
		s = GetStack(s);//4,返回值是右值，调用带右值引用参数的赋值运算符重载函数
		return 0;
	}
	输出：
	Stack(int)  //生成s;
	Stack(int)  //生成tmp
	Stack(Stack&&)    //执行带右值的拷贝构造函数，生成临时对象
	~Stack()          //析构tmp
	operator=(Stack&&)   //执行带右值引用的赋值运算符
	~Stack()            //析构临时对象,如果上式中的是 stack s=GetStack(s); 就不用析构临时对象，直接把临时对象赋给s,
	~Stack()			//析构s

/对于常数的右值引用，
int a=1;
int &&b=a;//b和a指向的是同一个地址，和常引用(const int&)不同的是，a,b都可以修改这个地址上的值，常引用不行，

int a=1;
int &&b=1;//a,b指向的地址也是一样的，
	
//右值引用的绑定规则

1,非const左值引用只能绑定到非const左值；
2,const左值引用可绑定到const左值、非const左值、const右值、非const右值；
3,非const右值引用只能绑定到非const右值；
4,const右值引用可绑定到const右值和非const右值，不能绑定到左值。

	struct A { A(){} };
	A lvalue;                             // 非const左值对象
	const A const_lvalue;                 // const左值对象
	A rvalue() {return A();}              // 返回一个非const右值对象
	const A const_rvalue() {return A();}  // 返回一个const右值对象
	 
	// 规则一：非const左值引用只能绑定到非const左值
	A &lvalue_reference1 = lvalue;         // ok
	A &lvalue_reference2 = const_lvalue;   // error
	A &lvalue_reference3 = rvalue();       // error
	A &lvalue_reference4 = const_rvalue(); // error
	 
	// 规则二：const左值引用可绑定到const左值、非const左值、const右值、非const右值
	const A &const_lvalue_reference1 = lvalue;         // ok
	const A &const_lvalue_reference2 = const_lvalue;   // ok
	const A &const_lvalue_reference3 = rvalue();       // ok
	const A &const_lvalue_reference4 = const_rvalue(); // ok
	 
	// 规则三：非const右值引用只能绑定到非const右值
	A &&rvalue_reference1 = lvalue;         // error
	A &&rvalue_reference2 = const_lvalue;   // error
	A &&rvalue_reference3 = rvalue();       // ok
	A &&rvalue_reference4 = const_rvalue(); // error
	 
	// 规则四：const右值引用可绑定到const右值和非const右值，不能绑定到左值
	const A &&const_rvalue_reference1 = lvalue;         // error
	const A &&const_rvalue_reference2 = const_lvalue;   // error
	const A &&const_rvalue_reference3 = rvalue();       // ok
	const A &&const_rvalue_reference4 = const_rvalue(); // ok
	 
	// 规则五：函数类型例外
	void fun() {}
	typedef decltype(fun) FUN;  // typedef void FUN();
	FUN       &  lvalue_reference_to_fun       = fun; // ok
	const FUN &  const_lvalue_reference_to_fun = fun; // ok
	FUN       && rvalue_reference_to_fun       = fun; // ok
	const FUN && const_rvalue_reference_to_fun = fun; // ok

	归纳：const左绑定到所有，const右只能绑定右，非const左右只能绑定自己，
	
	
//转移语义
右值引用是用来支持转移语义的。转移语义可以将资源 ( 堆，系统对象等 ) 从一个对象转移到另一个对象，这样能够减少不必要的临时对象的创建、拷贝以及销毁，能够大幅度提高 C++ 应用程序的性能。

//实现转移构造函数和转移赋值函数
	class Stack
	{
	public:
		// 拷贝构造
		Stack(const Stack &src)
			:msize(src.msize), mtop(src.mtop)
		{
			cout << "Stack(const Stack&)" << endl;
			mpstack = new int[src.msize];
			for (int i = 0; i < mtop; ++i)
			{
				mpstack[i] = src.mpstack[i];
			}
		}
		
		// 转移构造函数
		Stack(Stack &&src)   //如果传递的参数是左值(变量)，就调用拷贝构造函数，反之，就调用转移构造函数(常数)。
			:msize(src.msize), mtop(src.mtop)
		{
			mpstack = src.mpstack;  
			src.mpstack = nullptr;
		}

		// 转移赋值函数
		Stack& operator=(Stack &&src)
		{
			if(this == &src)
				return *this;
				
			delete[]mpstack;
		
			msize = src.msize;
			mtop = src.mtop;
			
			mpstack = src.mpstack;
			src.mpstack = nullptr;
			return *this;
		}
	private:
		int *mpstack;
		int mtop;
		int msize;
	};


//标准库函数 std::move
/将左值引用转换为右值引用

 void ProcessValue(int& i) 
 { 
  	std::cout << "左值引用，i = " << i << std::endl; 
 } 

 void ProcessValue(int&& i) 
 { 
  	std::cout << "右值引用，i = " << i << std::endl; 
 } 

 int main() 
 { 
	  int a = 0; 
	  ProcessValue(a); //执行第一个函数
	  ProcessValue(std::move(a));  //执行第二个
 }
	
,/swap函数：通过 std::move，一个简单的 swap 函数就避免了 3 次不必要的拷贝操作。
template <class T> swap(T& a, T& b) 
{ 
    T tmp(std::move(a)); // move a to tmp 
    a = std::move(b);    // move b to a 
    b = std::move(tmp);  // move tmp to b 
 }



//完美转发
需要将一组参数原封不动的传递给另一个函数。 
如下例：
	void func(const int);
	void func(int);
	void func(int&&);
如果func功能一样，只是参数类型是否是常变量，是否是右值引用；需要使用模板：
	template<typename T>
	void cover(T para)
	{
	  ...
	  func(para);
	  ...
	}
模板的问题是，当参数很大的时候，效率会很低，为解决这个问题
	template<typename T>
	void cover(T&& para)
	{
	  ...
	  func(static_cast<T &&>(para));  //static_cast强制转换符，将para强制转换成T&&类型
	  ...
	}

如果传入的是左值引用，转发函数将被实例化为:
	void func(T& && para)
	{
	  func(static_cast<T& &&>(para));
	}

应用引用折叠,就为:
	void func(T& para)
	{
	  func(static_cast<T&>(para));
	}

如果传入的是右值引用，转发函数将被实例化为:
	void func(T&& &&para)
	{
	   func(static_cast<T&& &&>(para));
	}

应用引用折叠,就是:
	void func(T&& para)
	{
	  func(static_cast<T&&>(para));
	}

,/对于以上的static_cast<T&&>，实际上只在para被推导为右值引用的时候才发挥作用，由于para是左值(右值引用是左值)，因此需要将它转为右值后再传入func内。

所以最终版本为
	template<typename T> 
	void cover(T&& para)
	{
	  func(forward(forward<T>(para)));//因为func中的参数要求可能是左值，也可能是右值，所以保持实参的原有的引用类型（左引用或者右引用类型）。
	}

//标准库函数std::forward
T para;
forward(para) ;
若T为左值引用，para将被转换为T类型的左值，否则para将被转换为T类型右值。

static_cast<T>(a):强制转换,把a强制转换成T类型，


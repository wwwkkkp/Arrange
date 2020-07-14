
//7.深入理解C++静态联编、动态联编与虚函数底层原理、RTTI 机制


在函数调用时，调用哪一个函数(当有继承，隐藏，覆盖等情况是)，C++有两种确定机制，静态联编和动态联编

//静态联编和动态联编

静态联编：在编译过程中进行联编被称为静态联编（static binding），又称为静态绑定、早期联编
动态联编：编译器必须能够在程序运行时选择正确的虚函数的代码，这被称为动态联编（dynamic binding），又称为动态绑定、晚期联编。

class Base
{
public:
	Base(int a = 0) :ma(a) {}

	/* 基类的虚函数function */
	virtual void function()
	{
		cout << "Base's function" << endl;
	}

	static int mb;
private:
	int ma;
};

class Derive : public Base
{
public:
	Derive(int data = 0) :Base(data), mc(data) {}

	void function()
	{
		cout << "Derive's function" << endl;
	}

private:
	int mc;
};

void fr(Base& rb) // 引用类型
{
	rb.function();
}

void fp(Base* pb) // 指针类型
{
	pb->function();
}

void fv(Base b) // 值传递
{
	b.function();
}

int main()
{
	Base base;
	Derive derive;            //运行结果
	fr(base);          //Base's function   //函数参数是引用，根据参数类型确定执行哪一个函数，下面有详解
	fr(derive);		   //Derive's function
	fp(&base);         //Base's function   //指针和引用效果一样
	fp(&derive);	   //Derive's function
	fv(base);		   //Base's function  
	fv(derive);		   //Base's function   //因为是值传递，所以当派生类传递给基类的时候，只传递了派生类中基类的部分，其他部分没有传递，所以执行的的基类的函数

	return 0;
}

//虚函数和动态联编
,/虚函数用的都是动态联编，根据指针指向的实际类型执行函数，普通的用的都是静态联编，根据指针的类型执行函数/，
动态联编的特点就是: /程序将使用为对象类型定义的方法，而不使用为引用或指针类型定义的方法。/

静态联编和动态联编的区别:
1,静态联编是在编译的时候就确认的调用链接，效率高，灵活性差，C++默认方式，C++的原则是效率优先
2,动态联编是在执行的时候确定调用链接，效率低，灵活性好


//虚函数的工作原理
如果一个类定义了虚函数,/那么在编译时期，会生成该类型的一张虚函数表vftable，存储的是虚函数的地址。这个虚函数表是存在.rotate段中，只读/,
						虚函数表是一个类共有的,和static一样,
/这个类的生成的对象，那会额外生成一个 虚函数指针vfptr，该指针指向这个类的虚函数表，虚函数指针占4个字节，地址在该对象的头部RTTI指针之后/

具体运行见图，这里简单说一下;
/当派生类继承了基类，也会继承虚函数表，如果重新定义了虚函数，就会更新对应虚函数的地址，/
当调用时,如果这个类包含虚基类，那就会去查 实际类对象 的虚函数表，然后执行对应的函数

总之,/使用虚函数时,在内存和执行速度方面有一定的成本/，包括：
1,每个对象都将增大，增大量为存储地址(vfptr)的空间
2,对于每个类，编译器都创建一个虚函数地址表（数组）
3,对于每个函数调用，都需要执行一项额外的操作，即到表中查找地址。


//有关虚基类注意对象
1,构造函数不能是虚函数
2,析构函数应当是虚函数．除非类不用做基类。
	如：
	class Base
	{
	public:
		Base(int a) :ma(a) { cout << "Base()" << endl; }
		~Base() { cout << "~Base()" << endl; }
		
	private:
		int ma;
	};
	class Derive : public Base
	{
	public:
		Derive(int data = 0) :Base(data), mb(data)
		{
			cout << "Derive()" << endl;
		}
		~Derive() {  cout << "~Derive()" << endl; }

	private:
		int mb;
	};

	int main()
	{
		Base* p = new Derive(); 
		delete p; 
		return 0;
	}
	//运行结果：
	Base()
	Derive()
	~Base()  //因为是静态联绑，所以只会执行基类的析构函数
	//如果将程序改成
	class Base
	{
	public:
		Base(int a) :ma(a) { cout << "Base()" << endl; }
		virtual ~Base() { cout << "~Base()" << endl; }
		
	private:
		int ma;
	};
	class Derive : public Base
	{
	public:
		Derive(int data = 0) :Base(data), mb(data)
		{
			cout << "Derive()" << endl;
		}
		~Derive() {  cout << "~Derive()" << endl; }

	private:
		int mb;
	};

	int main()
	{
		Base* p = new Derive(); 
		delete p; 
		return 0;
	}	
	//运行结果：
	Base()
	Derive()
	~Derive()  //这样就是动态联绑，会执行实际对象类型的析构函数
	~Base() 
	
3,友元不能是虚函数，因为友元不是类成员，而只有成员才能是虚函数。
4,如果派生类没有重新定义虚函数，将使用该函数的基类版本。如果派生类重新定义了该函数，则将使用最新的虚函数版本，基类的虚函数将被隐藏

//RTTI 运行时类型识别:
RTTI(Run Time Type Identification):运行时类型识别,/就是让程序在运行时能根据基类的指针或引用来获得该指针或引用所指的对象的 实际类型/;
/RTTI指针存储在虚函数表的头部，指向的是一段类型字符串，(例如：Base *)/
C++ 通过以下的两个操作提供RTTI：
1,typeid运算符，该运算符返回指针和引用所指的实际类型。
2,dynamic_cast运算符，该运算符将基类的指针或引用安全地转换为派生类类型的指针或引用。

eg:
class A{
public:
	void fun(){}
};
class B:public A{
public:
	void fun(){}
};
int main(){
	B b;
	A *a=&b;
	cout<<typeid(a).name()<<endl;
	cout<<typeid(*a).name()<<endl;
}
运行结果：
class A*
class A   //当基类中没有虚函数时，Base*p = &derive 语句中基类指针所指的实际的类型为Base 。

class A{
public:
	virtual void fun(){}
};
class B:public A{
public:
	void fun(){}
};
int main(){
	B b;
	A *a=&b;
	cout<<typeid(a).name()<<endl;
	cout<<typeid(*a).name()<<endl;
}
运行结果：
class A*   //指针类型还是A
class B    //实际指向的是B
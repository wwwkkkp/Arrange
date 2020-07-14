
//6.C++继承详解（三）：抽象类和纯虚函数、多重继承与虚基类的底层实现原理详解
纯虚函数
纯虚函数是一种特殊的虚函数，在许多情况下,在基类中不能对虚函数给出有意义的实现，而把它声明为纯虚函数,/它的实现留给该基类的派生类去做。这就是纯虚函数的作用。/
class A
{
	virtual int funcation(int val) = 0; // 定义纯虚函数
}

引入原因：
为了方便使用多态特性，我们常常需要在基类中定义虚函数;

/如果有纯虚函数，那这个类就是抽象类，不能对象化/

//抽象类
凡是含有纯虚函数的类叫做抽象类。这种类不能定义对象,
/如果派生类没有实现这个纯虚函数，那该派生类也是抽象类/


//多重继承
class Base1
{
public:
	Base1() { cout << "Base1()" << endl; }
	~Base1() { cout << "~Base1()" << endl; }
};
class Base2
{
public:
	Base2() { cout << "Base2()" << endl; }
	~Base2() { cout << "~Base2()" << endl; }
};

/*
**  : 之后称为类派生表，表的顺序决定基类构造函数
** 调用的顺序，析构函数的调用顺序正好相反
*/
class Derive : public Base2, public Base1  //先声明Bsae2,再声明Base1,执行构造函数的时候也是先执行Base2的构造函数
{};
int main()
{
	Derive derive;
	return 0;
}


//多重继承会带来各种各样的问题：
1,二义性问题
2,菱形继承导致派生类持有间接基类的多份拷贝

二义性：
class a{
	public:
		a(){}
		~a(){}
		void show(){}
};
class b{
	public:
		b(){}
		~b(){}
		void show(){}
};
class c:public a,public b{};

int main(){
	c d;
	d.show();    //这个是错误的，show是有歧义的，但是可以写成：d.a::show();
}

//当多重继承把派生类赋给基类时
class a{
	public:
		a(){}
		~a(){}
		void show(){}
};
class b{
	public:
		b(){}
		~b(){}
		void show(){}
};
class c:public a,public b{};

int main(){
	c d;
	a *e=&d;  //如果是单继承，这个就是正确的，但是多继承中c有两个地址，所以是错误的，必须类型转换，a *e=(a*)&d;
}


//虚基类
虚继承和虚函数是完全无相关的两个概念。
虚继承是解决C++多重继承问题的一种手段，从不同途径继承来的同一基类，会在派生类中存在多份拷贝。

/* 普通继承（没有使用虚基类）*/
 
class Base
{
public:
	int ma;
};
 
class Derive1 : public Base
{
public:
	int mb;
};
 
class Derive2 : public Base
{
public:
	int mc;
};
 
class Derive3 : public Derive1, public Derive2
{
public:
	int md;  //这个类中就会出现两个ma,分别从Derivel1和Derivel2继承的，但是这两个ma其实是一个值，浪费空间，为了解决这个问题，提出虚基类概念
};

/* 使用虚基类继承*/
class Base
{
public:
	int ma;
};
 
class Derive1 : virtual public Base
{
public:
	int mb;
};
 
class Derive2 : virtual public Base
{
public:
	int mc;
};
 
class Derive3 : public Derive1, public Derive2
{
public:
	int md;  //使用了虚基类继承之后，这个类中就只继承1个ma
};

//从内存布局看虚继承的底层实现原理,
/当使用虚基类继承的时候，派生类 生成一个 虚基类指针vbptr  和 虚基类表vbtable/，虚基类指针 指向 虚基类表，虚基类表维护的是 基类中的成员的地址,/注意:这个成员地址是当前派生类距离该基类成员的地址，而不是基类的首地址，所以继承之后，表的地址会变/

虚基类指针占用派生类4个字节，虚基类表不占用派生类对象的内存

当虚基类继承的派生类作为基类继承时，也会继承虚基类表，通过维护虚基类表，达到只继承一次虚基类的成员,/当需要使用基类成员时，通过虚基类表中的地址偏移实现访问/

注意:/虚基类依旧会在派生类里面存在拷贝，只是仅仅只存在一份而已，并不是不在派生类里面了/；

备注：虚函数也用类似的 虚函数指针 vfptr 和 虚函数表vftable，原理见下一章
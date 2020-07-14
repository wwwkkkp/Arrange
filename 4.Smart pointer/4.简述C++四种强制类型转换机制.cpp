

//4.简述C++四种强制类型转换机制


1,dynamic_cast运算符
2,const_cast运算符
3,static_cast运算符
4,reinterpret_cast运算符


C++支持C风格的强制转换，C风格的类型转换运算符太过松散，可能会带来一些隐患，让一些问题难以察觉。
TypeName b = (TypeName)a;


1,dymamic_cast运算符
除了dynamic_cast以外的转换，其转换行为的都是在编译期就得以确定的，转换是否成功，并不依赖被转换的对象;
/dynamic_cast依赖于 RTTI 信息,dynamic_cast会检查转换的source对象是否真的可以转换成target类型，这种检查不是语法上的，而是真实情况的检查。
dynamic_cast的作用：
,/将基类的指针或引用安全地转换成派生类的指针或引用，并用派生类的指针或引用调用非虚函数/;
/如果是基类指针或引用调用的是虚函数，无需转换就能在运行时调用派生类的虚函数。

,/前提条件：当我们将dynamic_cast用于某种类型的指针或引用时，只有该类型含有虚函数时，才能进行这种转换。否则，编译器会报错。

dynamic_cast运算符的调用形式如下所示：
	dynamic_cast<type*>(e)  // e是指针
	dynamic_cast<type&>(e)  // e是左值
	dynamic_cast<type&&>(e) // e是右值
	
e能成功转换为type*类型的情况有三种：

1,e的类型是目标type的公有派生类：派生类向基类转换一定会成功。
2,/e的类型是目标type的基类，当e是指针指向派生类对象，或者基类引用引用派生类对象时，类型转换才会成功，当e指向基类对象/，试图转换为派生类对象时，转换失败。
3,e的类型就是type的类型时，一定会转换成功。

	#include<iostream>
	using namespace std;

	class Base
	{
	public:
		virtual void show()
		{
			cout << "Base::show()" << endl;
		}
	};

	class Derive : public Base
	{
	public:
		virtual void show()
		{
			cout << "Derive::show()" << endl;
		}
		void fun(){
			cout<<"fun"<<endl;
		}
	};

	int main()
	{
		Base *base1 = new Base();
		Derive* Derive1 = dynamic_cast<Derive*>(base1);//base1是基类指针，指向的的也是基类目标，所以base1转换为派生类指针，转换失败，

		Derive derive2;
		Base* base2 = &derive2;
		Derive* Derive2 = dynamic_cast<Derive*>(base2);//base2是基类指针，指向的是派生类对象，转换能成功，
		Derive2->fun();
	}
	,/转换目的：第二个例子，基类指针指向派生类对象，这个时候，基类指针是无法调用派生类中的非虚函数fun(),当需要调用的时候，就需要强制转换成派生类指针，然后才能调用fun()

总结：

1,dynamic_cast运算符可以在执行期决定真正的类型。
2,如果 downcast 是安全的（也就说，如果基类指针或者引用确实指向一个派生类对象）这个运算符会传回适当转型过的指针。
3,如果 downcast 不安全，这个运算符会传回空指针（也就是说，基类指针或者引用没有指向一个派生类对象）。


//const_cast运算符
const_cast <type-name> (expression)
,/type-name 和 expression 的类型必须相同。

用法如下：
1,常量指针被转化成非常量的指针，并且仍然指向原来的对象；const int* -> int*
2,常量引用被转换成非常量的引用，并且仍然指向原来的对象；const int & -> int&
3,const_cast一般用于修改指针。如const char *p形式。

#include<iostream>
using namespace std;

void change(const int *pt, int n)
{
	int* pc;
	pc = const_cast<int*>(pt);//因为pt的类型是const int*，可以转换成int*，并修改指向地址的值
	*pc += n;
}

int main()
{
	int pop1 = 38383;
	const int pop2 = 2000;

	cout << "pop1, pop2 : " << pop1 << ", " << pop2 << endl;//pop1, pop2 :38383 2000
	change(&pop1, -103);
	change(&pop2, -103);
	cout << "pop1, pop2 : " << pop1 << ", " << pop2 << endl;//pop1, pop2 :38280 2000
}
,/注意：pop2是const修饰的量，在c++中是常量，常量是无法改变的，



//static_cast运算符
static_cast < type-name > ( expression )

,/把expression转换为type-name类型，但没有运行时类型检查来保证转换的安全性。
仅当type-name可被隐式转换为expression所属的类型，或expression可被隐式转换为type-name所属的类型时，上述转换才合法。

它主要有如下几种用法：

1,用于类层次结构中基类（父类）和派生类（子类）之间指针或引用的转换;/向上和向下转换都是合法的，只是安不安全的问题
	1),进行上行转换是安全的（把派生类的指针或引用转换成基类表示）；
	2),/进行下行转换时，由于没有动态类型检查，所以是不安全的（把基类指针或引用转换成派生类表示）。但是可以通过
2,用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这种转换的安全性也要开发人员来保证。
3,把空指针转换成目标类型的空指针。
4,把任何类型的表达式转换成void类型。

#include<iostream>
using namespace std;
int main()
{
	/* 常规的使用方法 */
	float f_pi = 3.141592f;
	int i_pi = static_cast<int>(f_pi); // i_pi 的值为 3
	cout << "i_pi : " << i_pi << endl;

	/* class 的上下行转换 */
	class Base {};
	class Derive :public Base {};

	// 上行 Derive -> Base
	//编译通过，安全
	Derive sub;
	Base* base_ptr = static_cast<Base*>(&sub);
	cout << "base_ptr : " << base_ptr << endl;

	//  下行 Base -> Derive
	// 允许向下类型转换，编译通过，但是不安全
	Base base;
	Derive* derive_ptr = static_cast<Derive*>(&base);
	cout << "derive_ptr : " << derive_ptr << endl;
}

,/注意：static_cast不能转换掉expression的const、volatile、或者__unaligned属性。


//reinterpret_cast运算符
reinterpret_cast< type-name > ( expression )
type-name 必须是一个指针、引用、算术类型、函数指针或者成员指针。

reinterpret_cast是C++中与C风格类型转换最接近的类型转换运算符,/它能够将一种对象类型转换为另一种，不管它们是否相关。

,/注意：reinterpret_cast不能用于内置类型之间的转换，只能用于不同指针之间的转换。

IBM 的 C++指南推荐的使用场景：

1,从指针类型到一个足够大的整数类型
2,从整数类型或者枚举类型到指针类型
3,从一个指向函数的指针到另一个不同类型的指向函数的指针
4,从一个指向对象的指针到另一个不同类型的指向对象的指针
5,从一个指向类函数成员的指针到另一个指向不同类型的函数成员的指针
6,从一个指向类数据成员的指针到另一个指向不同类型的数据成员的指针


#include <iostream>
using namespace std;
int main()
{
	struct dat
	{
		short a;
		short b;
	};

	long value = 0xA224B118;
	dat* pd = reinterpret_cast<dat*>(&value);
	cout << hex << "pd->a : " << pd->a << endl;
	cout << hex << "pd->b : " << pd->b << endl;
}

,/reinterpret_cast运算符并不支持所有的类型转换。/
例如,/可以将指针类型转换为足以存储指针表示的整形，但不能将指针转换为更小的整形或浮点型。/另一个限制是，不能将函数指针转换为数据指针，反之亦然。
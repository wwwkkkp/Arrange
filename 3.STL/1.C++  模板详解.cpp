
//1.C++ | 模板详解

模板是C++支持参数化多态的工具，使用模板可以使用户为类或者函数声明一种一般模式，使得类中的某些数据成员或者成员函数的参数、返回值取得任意类型。

通常有两种形式：函数模板和类模板；
函数模板针对仅参数类型不同的函数；
类模板针对仅数据成员和成员函数类型不同的类。

什么是函数模板
函数模板，实际上是建立一个通用函数，它所用到的数据的类型（包括返回值类型、形参类型、局部变量类型）可以不具体指定，而是用一个虚拟的类型来代替（实际上是用一个标识符来占位），等发生函数调用时再根据传入的实参来逆推出真正的类型。这个通用函数就称为函数模板（Function Template）。
什么是类模板
C++ 除了支持函数模板，还支持类模板（Class Template）。函数模板中定义的类型参数可以用在函数声明和函数定义中，类模板中定义的类型参数可以用在类声明和类实现中。类模板的目的同样是将数据的类型参数化。


//模板类型参数
类型参数由关键字class或typename后接说明符构成

template<class T>
void fun(T a, T b){}
// fun(12,56.2)  == > error //但是可以写成fun<int>(12,56.2);

//模板非类型参数
模板的非类型参数也就是内置类型参数，如
template<class T, int a> 
class B{};
其中int a就是非类型的模板参数。
非类型形参在模板定义的内部是常量值,/也就是说非类型形参在模板的内部是常量。/

template<int a>int fun() {
	cout << a << endl;
	return a;
}
int main() {
	const int a = 10;
	fun<a>();  //在调用时，<>中的参数必须是const int，非类型形参在模板的内部是常量。
	return 0;
}

全局变量的地址或引用，全局对象的地址或引用const类型变量是常量表达式，可以用作非类型模板形参的实参。
template <class T, int a> 
class A{};

int b;
A<int, b> m;  // error,b不是常量

// 改为下面形式
const int b;
A<int , b>m; // 正确，因为这时b是常量。//也就是说模板外面定义的b和<>中引用的b是同一个b


非类型模板形参的形参和实参间所允许的转换
① 允许从数组到指针，从函数到指针的转换。
template <int * a> 
class A{}; 

int b[1]; 
A<b> m; // 即数组到指针的转换
 
② const修饰符的转换。
template<const int * a> 
class A{}; 

int b; 
A<&b> m; // 即从int* 到const int *的转换。
 
③ 提升转换。
template<int a> 
class A{}; 

const short b = 2; 
A<b> m; // 即类似从short到int的类型提升转换
 
④ 整值转换。
template<unsigned int a> 
class A{};   

A<3> m; //即从int 到unsigned int的转换
 
⑤ 常规转换。



//模板的特殊化

template<typename T>
bool compare(const T &a, const T &b)
{
	return a > b; 
}
int main()
{
	int a = 10;
	int b = 20;
	compare<int>(a, b);
	return 0;
}
上面模板不适于字符串的比较，因此我们继续编写一个针对char*类型数据的特例化版本。
template<>
bool compare<char *>( char* const &a,  char* const &b)
{
	return strcmp(a, b) > 0;
}

//函数模板问题：
能不能把 函数模板 和 模板的调用 写在两个不同的源文件中?
/不能，由于模板不编译，模板代码都写在头文件中，各个源文件直接include使用就可以。/


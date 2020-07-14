

//7.类成员方法的简单总结

//static静态成员方法:

1.类中static成员是类共有的,/静态成员变量是在程序编译时分配空间，而在程序结束时释放空间。/
2./初始化静态成员变量要在类的外面进行./
	class a {
		static int b ; //直接给b赋值是错误的
	};
	int a::b = 2; 
	
3.可以通过 类名 来对静态成员变量进行引用，也可以通过 对象名来对静态成员变量进行引用。
4.普通成员函数和静态成员函数的区别是:/普通成员函数在参数传递时编译器会隐藏地传递一个this指针，通过this指针来确定调用类产生的哪个对象；/	,
	/但是静态成员函数没有this指针，不知道应该访问哪个对象中的数据，//*所以在程序中不可以用静态成员函数访问类中的普通变量。*/
	即普通成员方法编译时会自动添加this指针，静态成员方法编译时不会添加this指针。

//const常成员函数:
1,可以任意访问自己其它private私有成员，但是只能读，不能写
2,/常对象不能调用普通方法，常对象只能调用常方法/（因为常成员方法相当于在this指针参数前加了一个const限定符，普通方法没有，而默认的情况下const type* 是不能转换为type* 	   的，即不能调用普通方法是因为实参是常对象指针，而普通方法的形参是普通对象指针）


static和const的区别：
1.释放时间：
	const定义的常量在超出其 作用域 之后其空间会被释放，
	static定义的静态常量在函数执行后不会释放其存储空间。在程序结束时释放

2.定义方法：
	static静态成员变量不能在类的内部初始化。
	const通常在类的实现文件中初始化,/const成员变量也不能在类定义处初始化/，只能通过构造函数初始化列表进行，并且必须有构造函数。

//类成员方法的简单总结
	普通方法可以调用常方法，反之，不可以
	常方法可以调用静态方法，反之，不可以
	普通方法可以调用静态方法，反之，不可以
	常方法不能修改普通成员，但可以修改静态成员，由于静态成员被类对象所共享
	
补充：
class A{
	int *b;
public:
	int g(){return *b;}    ==>1
};
int main(){
	A a;
	int &c=a.g();//err，原因是它们同时使用了1语句的返回值初始化整形引用，这是错误的，因为1语句返回值是由寄存器带出来的一个常量（立即数），对于常量（立即数）是不能进行取地址操作的，注意 引用 & 必须初始化，右边的表达式必须要能够取地址。
}
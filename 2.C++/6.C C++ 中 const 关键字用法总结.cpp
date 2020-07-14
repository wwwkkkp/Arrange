
//6.C/C++ 中 const 关键字用法总结

const本身是一个修饰符,/所谓“修饰符”，就是在编译器进行编译的过程中，给编译器一些“要求”或“提示”，但修饰符本身，并不产生任何实际代码。/
const修饰符的作用主要是利用编译器帮助我们检查自己代码的正确性。我们使用const在源码中标示出“不应该改变”的地方，然后利用编译器，帮助我们检查这些地方是否真的没有被改变过。

在C/C++中，常见 const 用法有以下几种：
C语言 ：
① const 定义的变量可以初始化，也可以不初始化
② const修饰的量不能用于左值
③ 不能当作常量来使用，其实const修饰的应该叫做 常变量
④ 常变量const的编译方式，和普通变量的编译方式一样
C++：
① const修饰的变量一定要初始化
② const定义的量叫做  常量，这是真常量，可以用其来定义数组长度   //注意：c中const定义的是常变量，c++中定义的量是常量
③ C++的常量也可以变为常变量，例如 如下代码：
	int b =20;
	const int a = b;
	int array[a] ={0}; // 出错，编译时期b值不确定，且b为变量，不能用变量定义数组大小
④ 常量const的编译方式:/若初始化给出立即数， 在编译时期，拿常量的值把常量的名字替换掉，若用变量初始化，将退化为常变量/

//常见错误：
1.作为左值了
eg: const int a = 10;
	a = 20;
	
2、把const量的地址或者引用给泄露出去了
eg: const int a = 10;
	int *p = &a; // 泄露a的地址,可能会修改a,可修改为 const int *p = &a，//int* = const int* 错误
	int &b = a; 


const和一级指针结合
	int a = 10;
	const int *p = &a; // const修饰 *p, 即*p不可改变, 但p的指向可以改变
	int const *p = &a; // 同上
	int *const p = &a; // p的指向不可改变, 但 *p可以修改
	
	/// int *  = const int *  err
	/// int *  = int  *const  ok  //int *const相当于地址不可改的int*
	/// const int * = int * ok

常引用变量，才能引用常量
	const int a = 10;
	const int &b = a; // const与引用结合这只有一种形式
	
const与二级指针的结合
	int a = 10;
	int *p = &a;
	
	/// const int **  = int **   err
	/// int ** = const int **    err
	/// int * = const int *      err
	/// const int * = int *      ok   //主要记住三种允许赋值的

	/// int *const * = int**  	ok
	/// int ** = int *const *    err
	/// int **const = int**      ok
	/// int *const * = const int** err

引用
	int a = 10
	int *p = &a;
	
	int *const p = &a;
	int **q = &p; 
	// int ** = int *const *   err
	
	int a = 10;
	const int *p = &a;
	int *&q = p;// 相当于int**q = &p    int ** = const int ** err



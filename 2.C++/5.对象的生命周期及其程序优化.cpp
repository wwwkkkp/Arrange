

//5.对象的生命周期及其程序优化

#include <iostream>
using namespace std;
class Test
{
public:
	Test(int data = 100) : ma(data) 
	{
		cout << this <<": Test(int)" << endl;
	}

	Test(const Test &src) : ma(src.ma)
	{
		cout << this <<": Test(const Test &)" << endl;
	}

	Test & operator = (const Test &src)
	{
		ma = src.ma;
		cout << this <<": Test& operator=(const Test &)" << endl;
		return *this;
	}

	~Test()
	{
		cout << this <<": ~Test()" << endl;
	}

	int getData() { return ma; }
private:
	int ma;
};

Test GetTestObject(Test t)
{
	int value = t.getData();
	Test tmp(value);
	return tmp;
}

int main()
{
	Test t1;
	Test t2;
	t2 = GetTestObject(t1);
	cout << t2.getData() << endl;
}

//运行结果：
000000FD2F16FB14: Test(int)								// 构造t1
000000FD2F16FB34: Test(int)								// 构造t2
000000FD2F16FC14: Test(const Test &)					// GetTestObject(t1)实参t1通过值传递给Test GetTestObject(Test t) 形参 t ，调用拷贝构造
000000FD2F16F9B4: Test(int)								//Test tmp(value); 构造对象tmp
000000FD2F16FC54: Test(const Test &)					//return tmp; 将返回值tmp拷贝构造 main函数栈帧上的临时对象  
000000FD2F16F9B4: ~Test()								// 析构tmp   //注意：是先将tmp拷贝给临时对象最后再析构tmp
000000FD2F16FC14: ~Test()								// 析构形参 t  //这个时候作用阈已经离开函数，在临时变量和t2之间
000000FD2F16FB34: Test& operator=(const Test &)			// t2 = GetTestObject(t1); 临时对象调用赋值函数赋值给t2
000000FD2F16FC54: ~Test()								// 析构临时对象
100														// 打印 ma
000000FD2F16FB34: ~Test()								// 析构t2
000000FD2F16FB14: ~Test()								// 析构t2




//改变GetTestObject

Test GetTestObject(Test &t)
{
	int value = t.getData();
	return Test(value);
}

int main()
{
	Test t1;
	Test t2;
	t2 = GetTestObject(t1);
	cout << t2.getData() << endl;
}

//运行结果：
00000086C90FF8B4: Test(int)                              //构造t1
00000086C90FF8D4: Test(int)                              //构造t2
00000086C90FF9B4: Test(int)                              //构造临时对象 Test(value)
00000086C90FF8D4: Test& operator=(const Test &)          //将临时变量赋值给t2
00000086C90FF9B4: ~Test()                                //析构临时变量
100
00000086C90FF8D4: ~Test()                                //析构t2
00000086C90FF8B4: ~Test()                                //析构t1


//改变GetTestObject  

Test GetTestObject(Test &t)
{
	int value = t.getData();
	return Test(value);
}

int main()
{
	Test t1;
	Test t2 = GetTestObject(t1);
	cout << t2.getData() << endl;
}

//运行结果：//按理说会生成一个临时对象，然后执行拷贝构造函数给t2，但是运行结果只是赋值，原因不详

000000B19CEFF644: Test(int)								//构造t1
000000B19CEFF664: Test(int)								//构造t2  //大概Test t2 = GetTestObject(t1);就相当于Test t2=Test(value);
100
000000B19CEFF664: ~Test()							    //析构t1
000000B19CEFF644: ~Test()								//析构t2

//4.拷贝构造函数 与 赋值运算符      ///我试了一下，并没有出现浅复制的情况，是已经解决了吗


对于类，拷贝构造函数和赋值运算都是默认有的，但是可以删除，具体如下
class Person
{
public:
    Person(const Person& p) = delete;
    Person& operator=(const Person& p) = delete;
private:
    int age;
    string name;
};


用法：
假设motto是一个StringBad对象，则下面四种声明都将 调用拷贝构造函数：
StringBad ditto(motto);
StringBad str = motto;  //注意，这个也要调用拷贝构造函数
StringBad also = StringBad(motto);
StringBad * pStringBad = new StringBad(motto);

其中中间的两种声明可能会使用拷贝构造函数直接创建 str 和 also，也可能使用拷贝构造函数生成一个临时对象，然后将临时对象的内容赋给 str 和 also，这取决于具体的实现。最后一种声明使用 motto 初始化一个匿名对象，并将新对象的地址赋给 pstring指针。


/*判断使用了拷贝构造函数还是赋值运算符：如果被赋值得我对象已经存在，用的就是赋值运算符，如果被赋值的对象是在创建过程中，那使用的就是拷贝运算符*/

//默认拷贝构造函数

对于默认拷贝构造函数有一个问题，
class A{//没有定义，会自动生成一个
	int a,b;
	string s;
};
int main(){
	A n1;
	A n2(n1);
}

默认拷贝构造函数相当于是类中各个元素对应相等,/默认的拷贝构造函数逐个复制非静态成员（成员复制也成为浅拷贝），复制的是成员的值/。即：
n2.a=n1.a;
n2.b=n1.b;
n2.s=n1.s;

/对于string类型的数据结构直接用等号赋值是有问题的，属于浅复制，即只是将n1.s的首地址赋值给n2.s，n1.s和n2.s指向的其实是同一个地方/，
在析构的时候会执行语句delete[] s;n2先执行，string区域被释放，然后n1执行，由于已经释放过了，再释放要出问题,
/针对以上情况，所有用new开辟空间的数据结构都会出现这个问题/

StringBad::StringBad(const StringBad & st)
{
	len = st.len;
	str = new char[len + 1];
	std::strcpy(str, st.str);
}


总结：
如类中包含了使用new初始化的指针成员，应当定义一个拷贝构造函数，以复制指向的数据，而不是指针，这被称为深度复制(即深拷贝)。复制的另一种形式(成员复制或浅复制)只是复制指针值。浅拷贝仅浅浅地复制指针信息，而不会深入“挖掘”以复制指针引用的结构。

//赋值运算符
当给一个已经存在的类赋值的时候，用的是赋值运算符
class A{};
int main(){
	A a;
	A b(a);      //拷贝构造函数
	A c;         
	c=a;         //赋值运算符
}
,
/和拷贝构造函数一样，默认的赋值运算符也是 浅复制/
赋值运算符重写
class StringBad{
	int len;
	char str[];
}:
StringBad & StringBad::operator=(const StringBad & st)
{
	if(this == &st)  	//首先检查自我复制
		return *this;
	detele []str;       //首先删除被赋值对象的str
	len = st.len;       //赋值其他项
	str = new char[len + 1];   //重新创建str
	std::strcpy(str, st.str);
	return *this;
}

//使用new的注意事项
new和delete是一对一对应的，
new[]和delete[]是一对一对应的，加[]是一对，不加的是一对
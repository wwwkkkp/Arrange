

//3. C++11 lambda表达式与函数对象
lambda表达式可以编写内嵌的匿名函数，用以替换独立函数或者函数对象，并且使代码更可读;/优点就是可读性强，因为是在原地生成，原地调用;

,/在类中，可以重载函数调用运算符()，此时类的对象可以将具有类似函数的行为，我们称这些对象为函数对象，广义的说，所有lambda表达式都是函数对象

//lambda表达式
格式
[ capture-list ] ( params ) -> ret { body }  

[ capture-list ] :捕捉列表，不能省略,可以捕捉该函数对象外的变量，捕捉列表总是作为lambda的开始，即出现于lambda的开始处。它是lambda的引出符
( params )：参数列表
-> ret：ret返回值类型
{ body } :函数体

捕获方式：
[]：默认不捕获任何变量；
[=]：捕获外部作用域中所有变量，并拷贝一份在函数体中使用(值捕获)
[&]：捕获外部作用域中所有变量，并作为引用在函数体中使用(引用捕获)
[x]：仅以值捕获x，其它变量不捕获；
[&x]：仅以引用捕获x，其它变量不捕获；
[=, &x]：捕获外部作用域中所有变量，默认是值捕获，但是x是例外，通过引用捕获；
[&, x]：默认以引用捕获所有变量，但是x是例外，通过值捕获；
[this]：通过引用捕获当前对象（其实是复制指针）；
[*this]：通过传值方式捕获当前对象；


	// 指明返回类型
	auto add = [](int a, int b) -> int { return a + b; };

	// 自动推断返回类型
	auto multiply = [](int a, int b) { return a * b; };
	 
	int sum = add(2, 5);   // 输出：7
	int product = multiply(2, 5);  // 输出：10

[]的意义：这是lambda表达式一个很要的功能，就是闭包;
/闭包的一个强大之处是其可以通过传值或者引用的方式捕捉其封装作用域内的变量/，前面的方括号就是用来定义捕捉模式以及变量，我们又将其称为lambda捕捉块。

int x = 10;

auto add_x = [x](int a) { return a + x; };  // 复制捕捉x，可以理解成拷贝，也算是一个参数，但是这个参数是不可修改的
auto multiply_x = [&x](int a) { return a * x; };  // 引用捕捉x,对于引用捕获方式，无论是否标记mutable，都可以在lambda表达式中修改捕获的值

cout << add_x(10) << " " << multiply_x(10) << endl;// 输出：20 100
return 0;

/lambda表达式无法修改通过复制形式捕捉的变量，因为函数调用运算符的重载方法是const属性的。想改动传值方式捕获的值，那么就要使用mutable
int main()
{
    int x = 10;
 
    auto add_x = [x](int a) mutable { x *= 2; return a + x; };  // 复制捕捉x,一旦将lambda表达式标记为mutable，那么实现的函数调用运算符是非const属性的
 
    cout << add_x(10) << endl; // 输出 30
    return 0;
}


,/注意：lambda表达式是不能被赋值的：lambda表达式禁用了赋值运算符
auto a = [] { cout << "A" << endl; };
auto b = [] { cout << "B" << endl; };
 
a = b;   // 非法，lambda无法赋值,因为lambda表达式禁用了赋值运算符
auto c = a;   // 合法，生成一个副本


关于[=]	、[&],默认捕获所有变量，使用是有风险的,如
std::function<int(int)> add_x(int x)
{
    return [&](int a) { return x + a; }; //因为这个函数对象引用了x,是临时变量,所以添加到容器的函数返回值放到容器中后，x就被析构了，引用就失效了，导致结果失效
}
使用[=]可以解决上面问题，但是依然风险，
class Filter
{
public:
    Filter(int divisorVal):
        divisor{divisorVal}{}
 
    std::function<bool(int)> getFilter() 
    {
        return [=](int value) {return value % divisor == 0; };//[=]是无法赋值divisor的，但是[&]可以，因为[&]其实调用的是this指针，即[this]
    }
private:
    int divisor;
};


/lambda表达式还用于对象的排序准则
class Person
{
public:
    Person(const string& first, const string& last):
        firstName{first}, lastName{last} {} 

    Person() = default;
 
    string first() const { return firstName; }
    string last() const { return lastName; }
private:
    string firstName;
    string lastName;
};
 
int main()
{
    vector<Person> vp;
    // ... 添加Person信息
 
    // 按照姓名排序
    std::sort(vp.begin(), vp.end(), [](const Person& p1, const Person& p2){ return p1.last() < p2.last() || (p1.last() == p2.last() && p1.first() < p2.first()); });
        // ...
    return 0;
}

//函数对象
1,所有的普通函数名都是函数对象
2,重载了()符号的类也可以是函数对象

例1：
bool add_x(int x,int y)
{
	return x<y;
}

template<typename OP>
bool a(int x, int y, OP op) {
	return op(x, y);
}
int main()
{
	bool b=a(1, 2,add_x);//add_x作为函数名，是可以用做函数对象的
	return 0;
}

例2：
class add_x
{
public:
	bool operator()(int x,int y) {
		return x<y;
	}
};

template<typename OP>
bool a(int x, int y, OP op) {
	return op(x, y);
}
int main()
{
	bool b = a(1, 2, add_x{}); //重载了()符号的类也可以是函数对象，不过注意要加{}
	return 0;
}

,/类函数对象要比普通函数要快


这里我们看一个可以拥有状态的函数对象，其用于生成连续序列：
class IntSequence
{
public:
    IntSequence(int initVal) : value{ initVal } {}
 
    int operator()() { return ++value; }
private:
    int value;
};
 
int main()
{
    vector<int> v(10);
    std::generate(v.begin(), v.end(), IntSequence{ 0 });
	//这里的 IntSequence{ 0 } 相当于调用了构造函数，生成了一个初始值为0的对象，然后在这个对象的基础上进行()重载函数的执行
    /*  lambda实现同样效果
        int init = 0;
        std::generate(v.begin(), v.end(), [&init] { return ++init; });
    */
    std::for_each(v.begin(), v.end(), [](int x) { cout << x << ' '; });
    //输出：1, 2, 3, 4, 5, 6, 7, 8, 9, 10
 
    return 0;
}


关于排序算法：
vector<int> v{3, 4, 2, 9, 5};
// 升序排序
std::sort(v.begin(), v.end());  // output: 2, 3, 4, 5, 9
// 降序排列
std::sort(v.begin(), v.end(), std::greater<int>{}); // output: 9, 5, 4, 3, 2  这里的greater<int>{},也是相当于生成了一个greater对象，但是在最大堆定的时候就不用，


//补充，相关知识还有谓词等，看C++ PPT

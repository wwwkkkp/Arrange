
//结构体和共同体

//结构体
结构体(struct)指的是一种数据结构，是C语言中聚合数据类型(aggregate data type)的一类。结构体可以被声明为变量、指针或数组等，用以实现较复杂的数据结构。结构体同时也是一些元素的集合，这些元素称为结构体的成员(member)，且这些成员可以为不同的类型，成员一般用名字访问。


struct tag { 
    member-list
    member-list 
    member-list  
    ...
} variable-list ;

tag、member-list、variable-list 这 3 部分至少要出现 2 个。


声明1：

 此声明声明了拥有3个成员的结构体，分别为整型的a，字符型的b和双精度的c同时又声明了结构体变量s1,这个结构体并没有标明其标签 */
struct 
{
    int a;
    char b;
    double c;
} s1;
 
 
声明2：
 此声明声明了拥有3个成员的结构体，分别为整型的a，字符型的b和双精度的c
结构体的标签被命名为SIMPLE,没有声明变量 */
struct SIMPLE
{
    int a;
    char b;
    double c;
};
用SIMPLE标签的结构体，另外声明了变量t1、t2、t3
  struct SIMPLE t1, t2[20], *t3;
上述两个声明被编译器当作两个完全不同的类型，即使他们的成员列表是一样的，如果令 t3=&s1，则是非法的。
 
 
声明3：

也可以用typedef创建新类型
typedef struct AA
{
    int a;
    char b;
    double c; 
} Simple2;
现在可以用AA或者Simple2作为类型声明新的结构体变量
AA u1, u2[20], *u3;
Simple2 u4, u5[20], *u6;

结构体的成员可以包含其他结构体，也可以包含指向自己结构体类型的指针，而通常这种指针的应用是为了实现一些更高级的数据结构如链表和树等。 但是不能包含自己的对象


两个结构体互相包含，则需要对其中一个结构体进行不完整声明。

struct B;    //对结构体B进行不完整声明
			//结构体A中包含指向结构体B的指针
struct A
{
    struct B *partner;
    //other members;
};
 
			//结构体B中包含指向结构体A的指针，在A声明完后，B也随之进行声明
struct B
{
    struct A *partner;
    //other members;
};


初始化

 struct Student    //struct只是一个关键字
{
	char name[10];
	int age;
	char sex[5];
}st={"z",18,"man"};  //聚合类型，初始化只有一次机会
或者在定义的时候初始化
Student a={"z",18,"man"};


//typedef

typedef是在计算机编程语言中用来为复杂的声明定义简单的别名，它与宏定义有些差异。它本身是一种存储类的关键字

int (*P)[3];         //此时P是数组指针类型的变量变量
typedef int (*P)[3]; //此时P代表数组指针类型，用它可以定义一个数组指针类型的变量

int (*Pfun)(int,int); //此时Pfun是函数指针类型的变量
typedef int (*Pfun)(int,int); //此时Pfun代表Pfun是函数指针类型，它可以定义一个函数指针类型的变量
Pfun k;  //k也是一个两参数的函数指针，

typedef int A[10];  //此时A代表一个整形数组类型，它可以定义一个整形数组
A a;                //a就是一个大小为10的数组

typedef int *PP;   //由int*类型变量提升为int*类型 
const PP p1 = &i;   // const修饰指针p1，p1不可变
PP const p2 = &i;    // const修饰指针p2，p2不可变
上面两个指针 p1和p2 都相当于 int* const;可以改变值，不能改变地址，如果要const int* 的效果，就要typedef const int*  p;p a;


typedef 和 define
typedef int *PP;   // PP a,b  a,b都是int*类型
#define P int*;    //  p a,b  a是int*类型  b是int类型

//结构体的大小与内存对齐

结构体的大小不是结构体元素单纯相加就行的，因为我们主流的计算机使用的都是32bit字长的CPU，对这类型的CPU取4个字节的数要比取一个字节要高效，也更方便。所以在结构体中每个成员的首地址都是4的整数倍的话，取数据元素时就会相对更高效，这就是内存对齐的由来。
内存对齐原则：

第一条：编译器在给结构体开辟空间时，首先找到结构体中最宽的基本数据类型，然后寻找内存地址能被该基本数据类型所整除的位置，作为结构体的首地址。将这个最宽的基本数据类型的大小作为上面介绍的对齐模数。

第二条：为结构体的一个成员开辟空间之前，编译器首先检查预开辟空间的首地址相对于结构体首地址的偏移是否是本成员大小的整数倍，若是，则存放本成员，反之，则在本成员和上一个成员之间填充一定的字节，以达到整数倍的要求，也就是将预开辟空间的首地址后移几个字节。

第三条：结构体的总大小为结构体最宽基本类型成员大小的整数倍，如有需要编译器会在最末一个成员之后加上填充字节{trailing padding}。


struct C
{
	char a;   // 1 + 3  [0,1,2,3]
	int b;    // 4  [4,5,6,7]
	short c;  // 2 + 6  [8-15]
	double d; // 8  [16-23]
}; // [0-23]大小为24,向前对齐

struct F
{
    int a;  // 4 [0,1,2,3]
    char c; // 1 + 3  [4,5,6,7]  //最宽数据类型的整数倍
}; //[0-7]大小为8，向后对齐，一般只有两个数据成员

struct H
{
    char  a;  //1 +1
    short b;   //2
    char  c;  //1 +3
    int   d;  //4
    char  e[3]; //3 +1
};   // 大小为16


//共用体
共用体是一种特殊的数据类型，允许在相同的内存位置存储不同的数据类型。可定义一个带有多成员的共用体，但是任何时候只能有一个成员带有值。共用体提供了一种使用相同的内存位置的有效方式。//就是同一块区域可以转化成不同的数据类型
联合体中的所有成员是共享一段内存，因此每个成员的存放首地址相对于联合体变量的基地址的偏移量为 0，即所有成员的首地址都是一样的。为了使得所有成员能够共享一段内存，因此该空间必须足够容纳这些成员中最宽的成员。 
规则： 
同一内存在每一瞬时只能保存一个成员
起作用的成员是最后一次赋值的成员
只能对联合体/共用体的第一个成员进行初始化，不然后面的赋值会覆盖掉第一个的值
共用的体变量的地址和他的各成员地址都是同一个地址，就是首地址
共用体结构可以互相嵌套

//共同体内存对齐
union 的大小必须是union中不同数据类型的整数倍，

union u2 
{ 
	char arr[10];  // 10 + 6 满足能被8整除
	int n; //4
	double d;  //8
};  //大小为16
union sample2
{
	char ch[5];
	char ch1[7];
};   //大小等于7，因为char大小是1，不是5和7


//位域
C语言允许在一个结构体中以位为单位来指定其成员所占内存长度，这种以位为单位的成员称为“位段”或称“位域”( bit field) 。利用位段能够用较少的位数存储数据。

在C语言中，位段的声明和结构体（struct）类似，但它的成员是一个或多个位的字段，这些不同长度的字段实际储存在一个或多个整型变量中。在声明时，位段成员必须是整形或枚举类型（通常是无符号类型），且在成员名的后面是一个冒号和一个整数，整数规定了成员所占用的位数。位域不能是静态类型。不能使用&对位域做取地址运算，因此不存在位域的指针，编译器通常不支持位域的引用


struct CHAR
{
    unsigned int ch   : 8;    //8位
    unsigned int font : 6;    //6位
    unsigned int size : 18;   //18位
};   //大小是32,18+6+8=32

注意有符号和无符号  //如果赋值位数超过规定位数，取低位
#include<stdio.h>
typedef struct Demo 
{  
	int a : 1;  
	unsigned int b : 2;  
	unsigned int c : 3; 
}demo; 
 
int main() 
{  
	demo d;  
	d.a = 1;  //  a存储1位有符号整形数据   二进制(01)最低位 1  输出 -1   //在有符号位中，最高位代表正负，1为负，0为正
	printf("%d\n",d.a); // -1  
 
	d.a = 2;  //  a存储1位有符号整形数据   二进制(10)最低位 0  输出 0
	printf("%d\n",d.a); // 0  
 
	d.a = 3;  //  a存储1位有符号整形数据   二进制(11)最低位 1  输出 -1
	printf("%d\n",d.a); // -1
 
	d.b = 7;
	printf("%d\n",d.b); // 3  b存储两位无符号整形数据，0111输出最低位（11）输出 3
 
	d.b = 10;
	printf("%d\n",d.b); // 2  b存储两位无符号整形数据，1010输出最低位（10）输出 2
	return 0; 
}

//位段大小

例1：

#include<stdio.h>

typedef struct Demo 
{  
	unsigned int a : 1;  
	unsigned int b : 2; 
	unsigned int c : 3; 
}demo;   //大小是4字节，也就是一个int的大小，abc都存在int中，还剩下26位没有用


例2：

#include<stdio.h>
typedef struct Demo 
{  
	unsigned int a : 10;   //a开辟了一个int类型空间，还剩22位
	unsigned int b : 30;   //b是30位，不会使用A剩余的22位，会重新开辟一个int类型空间,还剩两位
	unsigned int c : 20;   //c是20位，不会使用B剩余的两位，会重新开辟一个int类型空间
}demo;  //大小是12字节，

例3：将上例中b与c的位置互换

#include<stdio.h>
typedef struct Demo 
{  
	unsigned int a : 10;   //a开辟了一个int类型空间，还剩22位
	unsigned int c : 20;   //c是20位，可以继续使用A剩余的空间，此时还剩两位
	unsigned int b : 30;   //b是30位，不会使用A剩余的两位，会重新开辟一个int类型空间
}demo;  //大小是8字节，因为a剩下的空间可以存储b，不用另外申请

例4：

#include<stdio.h>
struct S 
{  
	char ch;//1+3  
	char *ptr;//4  
	char buff[6];//6+2  ==> 16    
	union ru
	{   
		short a;   
		short b; 
		short c;   
		short d;  //2
		struct st   
		{    
			unsigned int x : 2;    
			unsigned int z : 10;    
			unsigned int y : 1;   
		}; //st大小是 4 ，
	}rr;  //4  ，以最大的数据结构/变量为准
	struct S * p;  //指针4个字节
};   //s大小是24字节


 



 

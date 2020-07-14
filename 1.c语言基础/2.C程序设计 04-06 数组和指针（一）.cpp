//《C程序设计 04-06 数组和指针（一）》

//C语言提供了几种聚合类型（aggregate types），即相同类型的数据集合，包括数组、指针、结构、共用体（联合）、位域和枚举等。

1、数组存放在哪个位置？ 数组分配的是一块    栈    上的内存
2、数组什么时候确定大小？                   编译时
3、什么时候给数组分配内存？                 运行时
4、数组越界的原理是什么？                   栈是受保护的，变量之间有两个哨兵位保护
5、最多分配多大的内存？                     根据栈大小分配 1M-2M

//数组在内存中的存放：

int arr[5]={1,2,3,4,5};
数组是存放在栈中的
arr[4]在栈底(高地址)，arr[0]在栈顶(低地址)
，所以是arr[4]先放到栈里面去的，

//sizeof:

sizeof(arr);  //代表整个数组的字节数
int arr[5]={1,2,3,4,5}
int len =sizeof(arr)/sizeof(arr[0])  //  20/4，此语句必须和数组定义位置在一起


void Show(int *p,int len)
{
	//int len = sizeof(p)/sizeof(p[0]);   //错误error，要与数组定义在一起
	for(int i = 0;i < len;i++)
	{
		printf("%d ",p[i]);   //*(p+i);  *解引用   []:自带解引用
	}
	printf("\n");
}
int main()
{
	int arr[5] = {1,2,3,4,5};//20
	int len = sizeof(arr)/sizeof(arr[0]);  //sizeof(arr):代表整个数组的字节数  20/4 = 5
	Show(arr,len);    //地址 数组首元素的地址
}
注意：
char *str="123456";
sizeof(str)=4 or 8,因为这里的str只是一个指针，返回的是指针的大小，在32位系统中是4，在64位系统中是8

char str[6]="123456"; //错误,str申请空间太小，因为char最后要加一个'\0';
char str[4]="123",int a=sizeof(str); //a=4，
char str[]="123",int a=sizeof(str); //a=4，

//strlen:返回的是数组的大小，到'\0'位置，不包括'\0'
char str[]="123456"，int a=strlen(str);//a=6

//sizeof与strlen的区别与联系
sizeof 返回的是变量声明后所占的内存数，不是实际长度，计算时包括 '\0',此外sizeof不是函数，仅仅是一个操作符，strlen是函数。 
strlen()是一个函数，测量的是字符的实际长度，以'\0' 结束，但计算时不包括 '\0',即使'\0'后面还有字符，也不计入计算了


//指针： 指针是一个变量，其值为另一个变量的地址，即，内存位置的直接地址。 指针也是要占用空间的 

int *p;  //野指针
int *p = NULL;   //0号地址   不能访问0号地址
printf("%d",p[i])    // *(p+i);  *解引用    []自带解引用
int *p       //p+1表示p向后挪4个字节（int* 类型）


//常量指针：
int *const p; 地址初始化之后就不能改，但是地址上的值可以改

int *const 和 const int* 和 int const* 和 const int* const ;
int *const:地址不能改，但是地址上的值可以改， 
const int* 和 int const* :等价，就是修饰符的位置不一样，可以互换，地址可以改，但是地址上的值不能改
const int* const :地址上的值和地址都不能改

//访问数组中的元素
int arr[5] = {5,4,3,2,1};
&arr+1 :指向的是arr数组的最后一个元素后面的位置，等于arr.end();

//字符串与字符数组:

字符串存放在rodata段，值不可修改，存储在相同区域
char *str = "hello";   //字符串，存放在rodata段，不可修改char *str2 = "hello";printf("%d %d",str,str2); //str，str1指向同一区域，值相等

字符数组存放在read段，值可修改 ，存储在不同区域
char str3[] = "hello";  //字符数组，存放在read区char str4[] = "hello";printf("%d %d",str3,str4); //str3，str4值不相等

数组名不能做左值

int arr[]={1,2,3,4};arr++;   //error,arr++即arr=arr+1,arr是指针常量，指向数组首元素的首地址，数组名不能做左值



".rodata"段存放的是只读数据，一般是程序里面的只读变量（如const修饰的变量）和字符串常量。单独设立".rodata"段有很多好处，不光是在语义上支持了C++的const关键字，而且操作系统在加载的时候可以将".rodata"段的属性映射成只读，这样对于这个段的任何修改操作都会作为非法操作处理，保证了程序的安全性。



//strcpy()字符串拷贝函数
char *str="Tulun";
char *str2="Hello";
printf("%s\n",strcpy(str,str2));  //error,字符串不能修改


char crr4[10] = "abcdef";
char crr5[10] = crr4;   //error,数组的整体赋值只有一次机会——初始化,这里应该直接给常数，给个首地址是不行的




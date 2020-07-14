
//C语言 可变参数列表源码剖析及实现

可变参数的限制 
	可变参数必须从头到尾逐个访问。如果你在访问了几个可变参数之后想半途终止，这是可以的，但是，如果你想一开始就访问参数列表中间的参数，那是不行的。
	参数列表中至少有一个命名参数。如果连一个命名参数都没有，就无法使用va_start。
	这些宏是无法直接判断实际存在参数的数量。
	这些宏无法判断每个参数的类型。
	如果在va_arg中指定了错误的类型，那么其后果是不可预测的。

结合实例看va_list va_start va_arg() va_end()

求平均值
#include<stdio.h>
#include<stdarg.h>
 
int average(int n, ...)  //因为这里是可变参数，所以用...代替，注意：参数排列是按照第一个参数在最低位，最后一个参数在最高位，也就是说，最后一个参数先入栈
{
	va_list arg;  //定义了一个char类型的指针，char*
	va_start(arg, n); //指针arg指向n后面的那个参数的首地址
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
            sum += va_arg(arg, int);//先将arg移动到下一个参数的首地址，然后通过arg-sizeof(int)把当前参数带入计算
	}
	va_end(arg);//将arg指向空指针
	return sum/n;
}
int main()
{
	int ave = average(5,  2, 3, 7,10,18);
	printf("%d\n",ave);
	return 0;
}


va_list arg;  // char * arg; 用于访问参数列表的未确定部分



va_start(arg, n);
/*//因为参数都是 连续放置 的，所以参数n后面跟着的就是第一个要代入计算的参数，

	va_start(arg, n)的意思就是arg以n的首地址为起点，偏移sizeof(int)个单位，最终指向的是第一个要带入计算的参数，也就是2的首地址

	arg = (char *)&n + sizeof(int);

	arg = (char *)&n + 4;

	#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )

*/

 

va_arg(arg, int);
/*
	获取参数va_arg(va_arg list,type),一定要保证参数类型正确，
	va_arg返回这个参数的值，并且va_arg指向下一个可变参数
	sum += ( *(int *)((arg += sizeof(int)) - sizeof(int) );
	
	//这个算是分两步，	第一步执行arg += sizeof(int)，先将arg指向下一个参数的首地址，
						第二步执行sum+=( *(int *)(arg-sizeof(int));//就是再通过arg-4的操作指向当前位置，
	//所以是先 偏移 再 带入计算。
	
	sum += ( *(int *)((arg += 4) - 4);
	#define va_arg(ap,t)  ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
*/


	
va_end(arg);
/*
	清空arg  //就是把指针指向0
	( arg = (char*)0 );
	#define va_end(ap)      
*/
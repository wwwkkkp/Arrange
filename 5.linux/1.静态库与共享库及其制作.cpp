

//静态库与共享库及其制作

//什么是库？
库是预先编译好的方法(函数)的集合。 本质上来说,/库是一种可执行代码的二进制形式，可以被操作系统载入内存执行。

分为两种形式：静态库(.a .lib)和共享库也称动态库(.so .dll)。

Linux存放库文件的标准路径：/lib、/usr/lib
存放库文件的标准路径：/usr/include
存放命令：/usr/bin、/bin


//静态库

缺省扩展名是 .a 

,/链接静态库就是将库中被调用的代码复制到调用模块中/;/静态库占用空间大，库中代码一旦修改必须重新链接/。使用静态库的代码在运行时无需依赖库，且执行效率高。
再运行代码的时候，就不需要再使用静态库，


//创建静态库

add.c
	#include "my.h"
	int add(int x,int y)
	{
		return x+y;    
	}

max.c
	#include "my.h"
	int max(int x ,int y)
	{
		return x>y ? x:y;    
	}	

my.h
	int max(int x,int y);
	int add(int x,int y);
	
main.c
	#include <stdio.h>
	#include <stdlib.h>
	#include <my.h>
	//#include <unistd.h>

	int g = 66;
	int main()
	{
		int a = 22;
		printf("add=%d,max=%d\n",add(a,g),max(a,g));
		exit(0);
	}

想把上面的add.c和max.c	编译成静态库，步骤如下
1,把add.c和max.c文件编译成.o文件，gcc -c add.c gcc -c max.c
2,打包做出库 ar crv libmyfoo.a add.o max.o     libmyfoo.a为静态库名
3,编译main.c,因为libmyfoo.a没有在库函数的标准位置(usr/lib),所以要指定调用，gcc -o main main.c -L. -lmyfoo  ，-L后即为指定调用的库
4,当然，也可以将libmyfoo.a放进标准库文件usr/lib中，把my.h放进标准头文件库usr/include
具体见 c++/kumodel/


//共享库

,/链接共享库并不需要将库中被调用的代码复制到调用模块中，被嵌入到调用模块中的仅仅是 被调用代码在共享库中的相对地址

如果共享库中的代码同时为多个进程所用，共享库的实例在整个内存空间中仅需一份，这正是共享的意义所在。共享库占用空间小，即使修改了库中的代码，只要接口保持不变，无需重新链接。使用共享库的代码在运行时需要依赖库，执行效率略低。
而共享库的缺省扩展名是： .so

//生成共享库
 gcc -shared -fPIC -o libXXX.so *.o   //最后的*.o就是当前文件夹中的所有.o文件，
 
 
 
 
 备注：	在执行程序编译后，删除静态库，不影响程序的正常运行；但是删除共享库不行
		


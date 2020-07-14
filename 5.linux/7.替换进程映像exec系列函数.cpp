

//7.替换进程映像exec系列函数
注意4点：
1,跳转到新进程，进程号和原ID一样
2,不返回，除非发生错误
3,原进程打开的文件描述符依然打开
4,原进程打开的目录流关闭，因为执行文件地址变了，以前打开的相对位置什么的目录没有意义了

以字母p结尾的函数通过搜索PATH环境变量来查找新程序的可执行文件的路径。
/**exec函数可以把当前进程替换为一个新进程，新进程由path或file参数指定。可以使用exec函数将程序的执行从一个程序切换到另一个程序。*/

	#include <unistd.h>

	extern char **environ;

	// ···为可变参函数，必须以空指针结束，即以 (char *)0 结束
	int execl(const char *path, const char *arg, ..., (char *)0); //path:要跳转程序的存储地址，后面的参数是程序参数，第一个参数一定是程序名
	int execlp(const char *file, const char *arg, ..., (char *)0);
	int execle(const char *path, const char *arg,...,, (char *)0,  char * const envp[]);
	int execv(const char *path, char *const argv[]);
	int execvp(const char *file, char *const argv[]);
	int execve(const char *filename, char *const argv[], char *const envp[]);

	举例：
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <assert.h>

	int main(int argc, char* argv[], char *envp[])
	{
		printf("pid = %d\n", getpid());
		char *myargv[10] = {"ps", "-f"};
		
		execl("/bin/ps", "ps", "-f", (char *)0); //execl执行成功，不返回，其下代码不会执行 
		exit(0);
	}
	ps是一个shell指令，这个就相当于执行了 ps -f 指令,
	
	/当exec跳转以后，一般情况下，exec函数是不会返回的，除非发生了错误。当前函数exec后面的程序也不会再执行
	/*由exec启动的新进程继承了原进程的许多特性。特别的，在原进程中已打开的 文件描述符 在新进程中仍保持打开，除非它们的“执行时关闭标志”(close on exec flag)被置位。
	任何在原进程中已打开的目录流都将在新进程中被关闭。*/
	
	例子：
	b.c
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <assert.h>
	int main(int argc, char* argv[], char *envp[])
	{
		printf("b.c -> pid = %d\n",getpid());
		int i;
		for(i = 0; i < argc; i++)
		{
			printf("argv[%d] = %s\n",i, argv[i]);
		}
	}

	test3.c
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <assert.h>
	int main(int argc, char* argv[], char *envp[])
	{
		printf("test.c - > pid = %d\n", getpid());
		
		execl("./b", "Hello", "World", "Linux", (char *)0); //跳转到b.c执行

		exit(0);
	}

	运行结果：
	test.c -> pid = 26885
	b.c -> pid = 26885
	argv[0] = Hello
	argv[1] = World
	argv[2] = Linux
	
	/*注意：跳转前和跳转后的进程号是一样的*/


//4.底层文件访问

主要是write(),read(),open();

当一个程序开始运行时，它一般会有3个已经打开的文件描述符：

0：标准输入
1：标准输出
2：标准错误

//write系统调用
系统调用write的作用是把缓冲区buf的前nbytes个字节写入与文件描述符fildes关联的文件中。

write返回的是写成功的数，如果这个函数返回0，就表示未写入任何数据；如果它返回的是-1，就表示在write调用中出现了错误，错误代码保存在全局变量errno里。

例子：
	#include <unistd.h>
	#include <stdlib.h>

	int main()
	{
		if((write(1, "Here is some data\n", 18)) != 18)   //标准输出，
			write(2, "A write error has occurred on file descriptor \n", 46);  //输出错误

		exit(0);
	}

注意：
write可能会报告写入的字节比你要求的少，这并不一定是个错误，在程序中，你需要检查errno以发现错误，然后再次调用write写入剩余的数据。



//read系统调用

#include <unistd.h>
size_t read(int fildes, void *buf, size_t nbytes);

从与文件描述符fildes相关联的文件里读入nbytes个字节的数据，并把它们放到数据区buf中

例子：
	#include <unistd.h>
	#include <stdlib.h>

	int main()
	{
		char buffer[128];
		int nread;
		
		nread = read(0, buffer, 128);  //标准输入，返回读成功多少个数
		if(nread == -1)  //读取失败
		{
			write(2, "A read error has occueeed\n", 26);
		}
		if((write(1, buffer, nread)) != nread)  //标准输出
		{
			write(2, "A write error has occurred\n", 27);
		}    
		exit(0);
	}



//open系统调用
为了创建一个新的文件描述符，你需要使用系统调用open。	

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int open(const char *path, int oflags);
int open(const char *path, int oflags, mode_t mode);// 严格来说，在遵循POSIX规范的系统上，使用open系统调用并不需要包括头文件sys/types.h和sys/stat.h。

oflags有三种模式：	O_RDONLY  只读
					O_WRONLY  只写
					O_RDWR	  读写

oflags还可以设置成以下模式：   	O_APPEND   把写入数据追加在文件末尾
								O_TRUNC    从文件头开始写，丢弃已有内容
								O_EXCL     和O_CREAT一起使用，确保调用者创建出文件，如果文件已经存在，open调用失败，open是原子操作
								
								
	#include <stdio.h>
	#include <unistd.h>
	#include <string.h>
	#include <assert.h>
	#include <stdlib.h>
	#include <fcntl.h>

	int main()
	{
		int fd = open("a.txt",O_WRONLY|O_CREAT,0600);
		assert(fd != -1);

		write(fd,"hello",5);

		close(fd);

		exit(0);
	}
	
//文件描述符

具体见https://zhaoyang.blog.csdn.net/article/details/87546602，这里只说个大概

/*文件描述符表*/：用户区的一部分，除非通过使用文件描述符的函数，否则程序无法对其进行访问。对进程中每个打开的文件，文件描述符表都包含一个条目。
/*系统文件表*/：为系统中所有的进程共享。对每个活动的open, 它都包含一个条目。每个系统文件表的条目都包含文件偏移量、访问模式（读、写、or 读-写）以及指向它的文件描述符表的条目计数。
/*内存索引节点表*/: 对系统中的每个活动的文件（被某个进程打开了），内存中索引节点表都包含一个条目。几个系统文件表条目可能对应于同一个内存索引节点表（不同进程打开同一个文件）;


/系统文件表包含一个偏移量，给出了文件当前的位置/。
若2个进程同时打开一个文件做读操作，每个进程都有自己相对于文件的偏移量，而且读入整个文件是独立于另一个进程的；
如果2个进程打开同一个文件做写操作,/写操作是相互独立的，每个进程都可以重写另一个进程写入的内容。

如果在open以后又执行了close函数，操作系统会删除对应的文件描述符表，和系统文件表的对应条目（若指向它的描述符表唯一），并对内存索引节点表条目中的计数减1，如果自减以后变为0，系统文件表和内存索引节点表都存储着一个计数，自己被指向的数量，当数量减为0，就删除该条目


//文件描述符的继承


父进程打开某个文件，fork()后，子进程也可以访问该文件，即父子进程共享该文件，指向的系统文件表的位置一样，共享偏移量；
父进程先fork，再打开文件，父子进程各自独享文件，互不影响。

///注意：父进程和子进程会共享文件描述符0,1,2,，这是系统自带的
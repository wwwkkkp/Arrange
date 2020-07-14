



//2.fork复制进程 和 写时拷贝机制

//fork()
功能：创建子进程，
返回值： 若成功调用一次则返回两个值，子进程返回0，父进程返回子进程PID；否则，出错返回-1。

备注：无法确定fork之后是子进程先运行还是父进程先运行


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int n = 0;
    char * s = NULL;

    pid_t pid = fork();
    assert(pid != -1);

    if(pid == 0)
    {
        n = 5;
        s = "child";
    }
    else
    {
        n = 7;
        s = "parent";
    }

    int i = 0;
    for( ; i < n ; i++)
    {
        printf("curr_pid = %d, curr_ppid = %d, s = %s, &n = %x, n = %d\n", getpid(), getppid(), s, &n , n); //getppid():返回父进程进程号
        sleep(1);   
    }
    exit(0);
}

root@Wkp:/home/c++# ./fork
curr_pid = 3668, curr_ppid = 3169, s = parent, &n = bd44cb2c, n = 7  //这个&n是虚拟地址，为什么父进程和子进程一样？？？？
curr_pid = 3669, curr_ppid = 3668, s = child, &n = bd44cb2c, n = 5
curr_pid = 3668, curr_ppid = 3169, s = parent, &n = bd44cb2c, n = 7
curr_pid = 3669, curr_ppid = 3668, s = child, &n = bd44cb2c, n = 5
curr_pid = 3668, curr_ppid = 3169, s = parent, &n = bd44cb2c, n = 7
curr_pid = 3669, curr_ppid = 3668, s = child, &n = bd44cb2c, n = 5
curr_pid = 3668, curr_ppid = 3169, s = parent, &n = bd44cb2c, n = 7
curr_pid = 3669, curr_ppid = 3668, s = child, &n = bd44cb2c, n = 5
curr_pid = 3668, curr_ppid = 3169, s = parent, &n = bd44cb2c, n = 7
curr_pid = 3669, curr_ppid = 3668, s = child, &n = bd44cb2c, n = 5
curr_pid = 3668, curr_ppid = 3169, s = parent, &n = bd44cb2c, n = 7
curr_pid = 3668, curr_ppid = 3169, s = parent, &n = bd44cb2c, n = 7



1,练习1
	#include <stdio.h>
	#include <assert.h>
	#include <stdlib.h>
	#include <unistd.h>

	int main()
	{
		fork() || fork();
		printf("A");
		exit(0);
	}
	输出：AAA;   
	当父进程执行第一个fork()时，返回的是子进程ID，所以||后的fork()就不用执行了，输出一个A
	子进程返回的是0，所以要执行第二个fork(),所以子进程又生成了一个子进程，所以输出2个A，一共三个A

2,练习2
	#include <stdio.h>
	#include <assert.h>
	#include <stdlib.h>
	#include <unistd.h>

	int main()
	{
		int i = 0;
		for( ; i < 2 ; i++)
		{
			fork();
			printf("A\n");
			sleep(3);
		}
		exit(0);
	}
	输出：
	A
	A 
	A 
	A 
	A 
	A 
	一共输出6个A，一个进程变2个，循环一个变4个，所以一共输出6个
	
3,练习3
	#include <stdio.h>
	#include <assert.h>
	#include <stdlib.h>
	#include <unistd.h>

	int main()
	{
		int i = 0;
		for( ; i < 2 ; i++)
		{
			fork();
			printf("A"); //注意和练习2的区别，这里没有\n
			sleep(3);
		}
		exit(0);
	}
	输出：AAAAAAAA
	一共输出8个A，这是因为printf("A") 把" A "放入了缓冲区中，并没有真正的输出,而在生成子进程的时候，把缓冲区的拷贝给了子进程，所以最后4个子进程的缓冲区中都是AA，一共8个A;
	若将printf(“A”)改为printf(“A\n”)，就是6个"A"了，因为程序遇到”\n"，或是EOF，或是缓冲区满，或是文件描述符关闭，或是主动flush，或是程序退出，就会把数据刷出缓冲区。
	
	
	Unix下的设备有“块设备”和“字符设备”的概念,/所谓块设备，就是以一块一块的数据存取的设备，字符设备是一次存取一个字符的设备。/磁盘、内存都是块设备，字符设备如键盘和串口;/块设备一般都有缓存，而字符设备一般都没有缓存/。
	还有一个是网络设备
	
//写时拷贝机制 copy-on-write technology 
关于子进程和父进程空间的问题
一个程序要运行，有4个空间，text段，data段，堆，栈

在生成子进程时，内核给子进程分配了新的虚拟内存，包括data段，堆，栈；而子进程的text段的虚拟内存还是父进程的text段，注意：这时候只是开辟了3个空间的虚拟内存地址
但是物理内存指向的都是父进程的data段，堆，栈，所以这个时候物理地址没有新开任何空间，当子进程在运行过程中会对data段，堆，栈进行修改的时候，才额外分配新的物理地址，
text段也会重新给物理地址：当子进程执行exec函数族的时候，跳转到其他文件执行后，就需要重新给一个物理地址


https://www.cnblogs.com/biyeymyhjob/archive/2012/07/20/2601655.html
1. 现在P1用fork()函数为进程创建一个子进程P2，
内核：
（1）复制P1的正文段，数据段，堆，栈这四个部分，注意是其内容相同。
（2）为这四个部分分配物理块，P2的：正文段－＞P1的正文段的物理块，其实就是不为P2分配正文段块，让P2的正文段指向P1的正文段块，数据段－＞P2自己的数据段块（为其分配对应的块），堆－＞P2自己的堆块，栈－＞P2自己的栈块。

2.  写时复制技术:
/内核只为新生成的子进程创建 虚拟空间结构 ，它们来复制于父进程的虚拟空间结构，但是不为这些段分配物理内存，/它们共享父进程的物理空间,/当父子进程中有更改相应段的行为发生时，再为子进程相应的段分配物理空间/。





 vfork()：这个做法更加火爆，内核连子进程的虚拟地址空间结构也不创建了，直接共享了父进程的虚拟空间，当然了，这种做法就顺水推舟的共享了父进程的物理空间
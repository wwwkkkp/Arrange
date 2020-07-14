

//3,僵尸进程的产生原因和避免方法



//产生原因
当父进程生成子进程之后，如果子进程比父进程先结束，那子进程就会变成僵尸进程，僵尸进程只保留子进程的进程号，运行时间，退出状态等信息，方便父进程查看，同时释放其他内存，

如果父进程比子进程早退出，那子进程会被init接管，结束后直接释放，不会形成僵尸进程。

//危害
僵尸进程如果不清除，会一直存在，占用进程号，导致进程号不足

//释放方法
父进程中需要调用wait()或者waitpid()系统调用取得子进程的终止状态。
	
	//代码实现
	#include <stdio.h>
	#include <unistd.h>
	#include <string.h>
	#include <assert.h>
	#include <stdlib.h>
	#include <sys/wait.h>

	int main()
	{
		int n = 0;
		char * s = NULL;

		pid_t pid = fork();
		assert(pid != -1);

		if(pid == 0)
		{
			n = 4;
			s = "child";
		}
		else
		{
			n = 10;
			s = "parent";
			
			int val = 0;
			pid_t id = wait(&val);
			if(WIFEXITED(val))
			{
				printf("exit code = %d\n",WEXITSTATUS(val));
			}
		}

		int i = 0;
		for( ; i < n; i++)
		{
			printf("s = %s, curr_pid = %d, curr_ppid = %d\n",s,getpid(),getppid());
			sleep(1);
		}
		exit(3); // 退出码设置为3
	}

//wait()函数

#include <sys/types.h> /* 提供类型pid_t的定义 */
#include <sys/wait.h>
pid_t wait(int *status)

当父进程执行到wait()函数时，就立即阻塞自己,/由wait自动分析是否当前进程的某个子进程已经退出，如果让它找到了这样一个已经变成僵尸的子进程，wait就会收集这个子进程的信息，并把它彻底销毁后返回；/
如果没有找到这样一个子进程，wait就会一直阻塞在这里，直到有一个出现为止。

参数status用来保存被收集进程退出时的一些状态

pid = wait(NULL);

如果成功，wait会返回被收集的子进程的进程ID，如果调用进程没有子进程，调用就会失败，此时wait返回-1，同时errno被置为ECHILD。


参数status:
/如果参数status的值不是NULL，wait就会把子进程退出时的状态取出并存入其中，这是一个整数值（int），指出了子进程是正常退出还是被非正常结束的（一个进程也可以被其他进程用信号结束，我们将在以后的文章中介绍），以及正常结束时的返回值，或被哪一个信号结束的等信息。/
由于这些信息被存放在一个整数的不同二进制位中,/所以用常规的方法读取会非常麻烦，人们就设计了一套专门的宏（macro）来完成这项工作，下面是其中最常用的两个：

1、WIFEXITED(status) 这个宏用来指出子进程是否为正常退出的，如果是，它会返回一个非零值。
（请注意，虽然名字一样，这里的参数status并不同于wait唯一的参数–指向整数的指针status，而是那个指针所指向的整数）

2、WEXITSTATUS(status)  当WIFEXITED返回非零值时，我们可以用这个宏来提取子进程的返回值 ，如果子进程调用exit(5)退出，WEXITSTATUS(status)就会返回5；如果子进程调用exit(7)，WEXITSTATUS(status)就会返回7。
请注意，如果进程不是正常退出的，也就是说，WIFEXITED返回0，这个值就毫无意义。


WIFEXITED(status)和WEXITSTATUS(status)使用wait()函数定义的两个宏，
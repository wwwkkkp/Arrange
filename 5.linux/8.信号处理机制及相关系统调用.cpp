


//8.信号处理机制及相关系统调用

对于 Linux来说，信号的实质是一种软中断，许多重要的程序都需要处理信号。
信号，为 Linux 提供了一种处理异步事件的方法。比如，终端用户输入了 ctrl+c 来中断程序，会通过信号机制停止一个程序。


//信号概述
软中断信号（signal，又简称为信号）用来通知进程发生了异步事件;
		/进程之间可以互相通过系统调用kill()发送软中断信号，内核也可以因为内部事件而给进程发送信号，通知进程发生了某个事件/;
		/注意，信号只是用来通知某进程发生了什么事件，并不给该进程传递任何数据。

信号的接收处理
1,捕获(catch)：执行进程指定的信号处理函数被调用  //这个就相当于中断,执行中断处理函数
2,忽略(Ignore)：执行操作系统指定的缺省处理       //就是默认处理操作
	例如：进程终止、进程挂起等
3,屏蔽（Mask）：禁止进程接收和处理信号			 //就是不接收处理信号，如在登录程序的时候，ctrl+c是无法终止程序的
	可能是暂时的(当处理同样类型的信号)
	
//信号处理机制
1,内核对信号的基本处理方法
内核给一个进程发送软中断信号的方法，是在进程所在的 进程表项 的信号域设置对应于该信号的位。
如果信号发送给一个正在睡眠的进程,/那么要看该进程进入睡眠的优先级/，如果进程睡眠在可被中断的优先级上，则唤醒进程；否则仅设置进程表中信号域相应的位，而不唤醒进程。

进程检查是否收到信号的时机是:/1,进程在即将从内核态返回到用户态时；2,在一个进程要进入或离开一个适当的低调度优先级睡眠状态时。
内核处理一个进程收到的信号的时机:/是在一个进程从内核态返回用户态时/。当在内核态收到信号的时候，是不会立刻反应的，要等到将返回用户态时才处理。
内核处理一个进程收到的软中断信号是在该进程的上下文中:/因此，进程必须处于运行状态。

进程从内核态返回用户态时执行用户定义的函数(捕获)。
而且执行用户定义的函数的方法很巧妙:/内核是在用户栈上创建一个新的层，该层中将返回地址的值设置成用户定义的处理函数的地址，这样进程从内核返回弹出栈顶时就返回到用户定义的函数处，从函数返回再弹出栈顶时， 才返回原先进入内核的地方。

注意事项：
1,一个进程处理完中断信号返回用户态之前,/内核清除用户区中设定的对该信号的处理例程的地址,除非在下一次信号到来之前再次使用signal系统调用。这可能会使得进程 在调用signal之前又得到该信号而导致退出。
2,如果要捕捉的信号发生于进程正在一个系统调用中时，并且该进程睡眠在可中断的优先级上，这时该信号引起进程作一次longjmp，跳出睡眠状态，返回用户态并执行信号处理例程,
/当从信号处理例程返回时，进程就像从系统调用返回一样，但返回了一个错误代码，指出该次系统调用曾经被中断。
/*进程在进入内核态的时候，是处于睡眠状态的，这个时候收到信号，如果睡眠优先级高，就立刻终止该进程的内核系统调用，返回用户态，执行中断处理函数*/

3,子进程终止（SIGCLD）信号,作用是唤醒一个睡眠在可被中断优先级上的进程。当进程检查出收到了一个子进程终止的信号时,不会有任何反应，除非父进程执行了wait()函数，

4,如果一个进程调用signal系统调用，并设置了SIGCLD的处理方法，并且该进程有子进程处于僵死状态，则内核将向该进程发一个SIGCLD信号。

//有关信号的系统调用
signal系统调用
函数原型：
#include <signal.h> 
void (*signal(int signum, void (*handler)(int)))(int);   //第一个参数是信号，第二个参数是处理方法，可以是函数对象，可以是系统设定好的宏操作

第二个参数 宏操作：
SIG_IGN：忽略参数signum所指的信号。 
SIG_DFL：恢复参数signum所指信号的处理方法为默认值。 

例子：
	#include <stdio.h>
	#include <unistd.h>
	#include <signal.h>

	void ouch(int sig)
	{
		printf("OUCH!-I got signal %d\n",sig);
		(void) signal(SIGINT, SIG_DFL);   //执行完成后，系统恢复SIGINT的默认处理方法
	}

	int main()
	{
		(void) signal(SIGINT, ouch);  //设置SIGINT信号的处理方法是ouch，

		while(1)					//当没有收到信号的时候程序在这里无限循环，当收到SIGINT信号后，就去执行ouch()
		{
			printf("Hello World!\n");
			sleep(1);
		}
	}
	执行
	root@Wkp:/home/c++# ./signal 
	Hello World!
	Hello World!
	Hello World!
	Hello World!
	^COUCH!-I got signal 2   //第一次输入ctrl+c，执行ouch函数，
	Hello World!
	Hello World!
	Hello World!
	Hello World! 			
	^C						//第二次输入ctrl+c，执行默认值，也就是终止进程


//kill系统调用

#include <sys/types.h>
#include <signal.h>

int kill (pid_t pid, int sig);

kill函数的作用：把参数sig给定的信号发送给由参数pid给出的进程号所指定的进程，成功时它返回0。要想发送一个信号，发送进程必须拥有相应的权限。
				这通常意味着两个进程必须拥有相同的用户ID(即你只能发送信号给属于自己的进程，但超级用户可以发送信号给任何进程)。
				
kill调用会在失败时返回-1并设置errno变量。失败的原因可能是：
1,给定的信号无效（errno 设置为EINVAL）；
2,发送进程权限不够（errno设置为EPERM）；
3,目标进程不存在（errno设置为ESRCH）。


例子：
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <assert.h>
	#include <signal.h>

	int main(int argc , char * argv[] )
	{
		if(argc != 3) // 由于第一个参数是当前程序名，因此传递两个参数arc应该为3
		{
			printf("argc error\n");
			exit(0);
		}

		int pid = 0;
		int sig = 0;

		sscanf(argv[1], "%d", &pid);
		sscanf(argv[2], "%d", &sig);  //输入一个进程号和 信号
		if(kill(pid, sig) != 0)  // 2  15  9   //如果发送后，返回不是0，就发送错误，
		{
			perror("Kill Error");
		}

		exit(0);
	}



//alarm函数模拟
#include <unistd.h>
unsigned int alarm(unsigned int seconds);

闹钟功能。进程可以通过调用alarm函数在经过预定时间后发送给目前的进程一个SIGALRM信号。把参数seconds设置为0将取消所有已设置的闹钟请求。

如果在发送到SIGALRM信号之前再次调用alarm函数，则闹钟重新开始计时。每个进程只能有一个闹钟时间。alarm函数的返回值是以前设置的闹钟时间的余留秒数，如果调用失败则返回-1。

通过fork、sleep和signal来模拟它的效果：
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <signal.h>
	#include <sys/types.h>

	static int alarm_fired = 0;

	void ding(int sig)
	{
		alarm_fired = 1;
	}

	int main()
	{
		pid_t pid = fork();
		
		printf("alarm application starting\n");

		switch(pid)
		{
			case -1: // Failure
				perror("fork failed");
				exit(1);
			case 0:  // child
				sleep(5);
				kill(getppid(), SIGALRM);  //向父进程发送SIGNALRM信号
				exit(0);
		}

		// parent
		printf("waiting for alarm to go off\n");
		(void) signal(SIGALRM, ding);

		pause();
		if(alarm_fired)
			printf("Ding\n");

		printf("done\n");
		exit(0);
	}
	root@Wkp:/home/c++# ./alarm 
	alarm application starting
	waiting for alarm to go off
	alarm application starting
	Ding
	done
	闹钟模拟程序通过fork调用启动新的进程，这个子进程休眠5秒后向其父进程发送一个SIGALRM信号。父进程在安排好捕获SIGALRM信号后暂停运行，直到接收到一个信号为止。我们并未在信号处理函数中直接调用printf，而是通过在该函数中设置标志，然后在main函数中检查该标志来完成消息的输出。



这个程序用到了一个新的函数pause,/它的作用很简单，就是把程序挂起直到有一个信号出现为止。
当程序接收到一个信号时，预设好的信号处理函数将开始运行，程序也将恢复正常的执行。pause函数的定义如下所示：
	#include <unistd.h>

	int pause(void);

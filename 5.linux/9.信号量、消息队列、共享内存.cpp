


//9.信号量、消息队列、共享内存

临界资源
指同一时刻，只允许一个进程（或线程）访问的资源

临界区
指访问临界资源的代码段。

信号量
信号量是一种特殊的变量，访问具有原子性。只允许对它进行两个操作：   //这个在 18-2 信号量使用 说明的比较详细，有经典的生产者-消费者问题
① p操作
当信号量值为0时，进程阻塞；当信号量值大于0时，信号量减1，进程获得资源继续运行。
② v操作
将信号量值加1，不会发生阻塞，v操作代表释放资源

信号量的分类
① 计数信号量：计数信号量的初始值其实就是共享资源的数量。有几个进程访问，信号量就减去几，直到再次没有资源可以使用。
② 二值信号量：二值信号量可以理解成计数信号量的一种特殊形式，即初始化为仅有一个资源可以使用，当临界资源被获取了，信号量值就是0，临界资源被释放，信号量值就是1，把这种只有0 和1 两种情况的信号量称之为二值信号量。

说简单点 	计数信号量就是允许sem个进程同时访问，有一个进程访问了，sem--，直到减到0，就不允许其他进程访问，
			二值信号量就是只允许1个进程访问，sem=1，先执行p操作，减到0之后不允许访问，访问完以后执行v操作，其他进程就可以访问了，
			
进程间同步控制  //信号量可以完成同步，但是在 18-2 信号量使用 中有详细例子
① 同步执行：两个或多个进程需要协同执行，进程A的执行需要进程B提供支持
② 异步执行：进程A和进程B互不干扰，在B给A发送数据前，A不会等待数据到达。 只有B给A发送数据后，A去处理数据。（类似信号）


//Linux的信号量机制
Linux提供了一组信号量API，声明在头文件 <sys/sem.h> 中。

1,semget函数
,/semget函数的作用是创建一个新信号量或获取一个已有信号量的键。

int semget(key_t key, int num_sems, int sem_flags);

key：信号量键值，可以理解为信号量的唯一性标记。
num_sems：信号量的数目，一般为 1
sem_flags：有两个值，IPC_CREATE 和 IPC_EXCL，
IPC_CREATE表示若信号量已存在，返回该信号量标识符。
IPC_EXCL表示若信号量已存在，返回错误。

返回值：成功则返回相应的信号量标识符，失败返回-1

2,semop函数
,/semop函数用于改变信号量的值，它的定义如下所示：
int semop(int sem_id, struct sembuf *sem_opa, size_t num_sem_ops);

sem_id：信号量标识符
sem_opa：该参数为sembuf结构的指针，定义如下
		struct sembuf{  
			short sem_num;//sem_num为信号量编号除非使用一组信号量，否则它为0  
			short sem_op;//信号量在一次操作中需要改变的数据，通常是两个数，一个是-1，即P（等待）操作，一个是+1，即V（发送信号）操作。  
			short sem_flg;//通常为SEM_UNDO,使操作系统跟踪信号，  
						  //并在进程没有释放该信号量而终止时，操作系统释放信号量  
		}; 

3,semctl函数
,/semctl用来直接控制信号量信息，常用来进行信号量的初始化和销毁。
int semctl(int sem_id, int sem_num, int command, [union semun sem_union]);

sem_id：由semget返回的信号量标识符。
sem_num：信号量编号，当需要用到成组的信号量编号时，就要用到这个参数，他一般取值为0，表示这是第一个也是唯一的一个信号量。
command：是将要采取的动作，有两个值SETVAL，IPC_RMID，分别表示初始化和删除信号量。
sem_union：可选参数，是一个union semun结构，它至少包含以下几个成员：
	union semun{  
		int val; 
		struct semid_ds *buf;  
		unsigned short *arry;  
	}; 

一般用到的是val，表示要传给信号量的初始值。注意：semun联合结构必须由程序员自己定义。

	例子：
	sem.h
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include <sys/sem.h>

	void sem_init();
	void sem_p();
	void sem_v();
	void sem_destroy();

	sem.c
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include <sys/sem.h>
	#include "sem.h"
	union semun // man semctl
	{
		int val;
	};

	static int sem_id;
	void sem_init()
	{
		sem_id = semget((key_t)1234, 1, IPC_CREAT | IPC_EXCL | 0600); // 尝试创建一个信号量
		if(sem_id == -1) // 信号量已存在或者创建失败
		{
			sem_id = semget((key_t)1234, 1, 0600); // 获取已有信号量的id
			if(sem_id == -1) // 判断是否成功获得信号量id
			{
				perror("semget erorr");
				return;
			}
		}
		else
		{
			union semun a;
			a.val = 1;

			if(semctl(sem_id, 0, SETVAL, a) == -1) // 信号量赋初值
			{
				perror("semctl error");
			}
		}
	}

	void sem_p()
	{
		struct sembuf buf;
		buf.sem_num = 0;
		buf.sem_op = -1; // p操作
		buf.sem_flg = SEM_UNDO;

		if(semop(sem_id, &buf, 1) == -1)
		{
			perror("semop error");
		}
	}

	void sem_v()
	{
		struct sembuf buf;
		buf.sem_num = 0;
		buf.sem_op = 1; // v操作
		buf.sem_flg = SEM_UNDO;

		if(semop(sem_id, &buf, 1) == -1)
		{
			perror("semop error");
		}
	}

	void sem_destroy()
	{
		if(semctl(sem_id, 0, IPC_RMID) == -1)
		{
			perror("semctl error");
		}
	}

	as.c
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include "sem.h"

	int main(int argc, char *argv[])
	{
		sem_init();  //as.c和b.c是同一个信号量，看上面的定义就知道了
		int i = 0;
		for(; i < 5; i++)
		{
			sem_p();   //如果这个程序先执行，那其他进程只能等待，直到执行了sem_v();
		
			printf("A");
			fflush(stdout);
			
			int n = rand() % 3;
			sleep(n);

			printf("A");
			fflush(stdout);
			
			n = rand() % 3;
			sleep(n);

			sem_v();
		}

		exit(0);
	}

	bs.c
	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include "sem.h"

	int main(int argc, char *argv[])
	{
		sem_init();   				 //as.c和b.c是同一个信号量，看上面的定义就知道了
		int i = 0;
		for(; i < 5; i++)
		{
			sem_p();				//如果这个程序先执行，那其他进程只能等待，直到执行了sem_v();
		
			printf("B");
			fflush(stdout);
			
			int n = rand() % 3;
			sleep(n);

			printf("B");
			fflush(stdout);
			
			sem_v();
			
			n = rand() % 3;
			sleep(n);
		}

		sleep(10);
		sem_destroy();
		exit(0);
	}
	同时执行as.c和b.c
	./as& ./b&
	AABBAABBAABBAABBAABB
	
	上述程序我们使用了信号量，A 和 B 对共享资源的访问是互斥的，即A和B分别都是成对出现的，例如AA表示A进程访问，A进程释放。
	
	
//消息队列

消息队列提供了一种在两个不相关的进程之间传递数据的 简单高效 的方法。
,/与有名管道比较起来，消息队列的优点在独立于发送与接收进程，这减少了在打开与关闭有名管道之间同步的困难。

1,msgget函数
功能：创建和访问一个消息队列
原型：
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/msg.h>
	int msgget(key_t key, int msgflag);

参数：
key：某个消息队列的名字，用ftok()产生
	#include <sys/types.h>
	#include <sys/ipc.h>
	key_t ftok(const char *pathname, int proj_id);// 调用成功返回一个key值，用于创建消息队列，如果失败，返回-1

msgflag：有两个选项IPC_CREAT和IPC_EXCL，单独使用IPC_CREAT，如果消息队列不存在则创建之，如果存在则打开返回；单独使用IPC_EXCL是没有意义的；两个同时使用，如果消息队列不存在则创建之，如果存在则出错返回。
返回值：成功返回一个非负整数，即消息队列的标识码，失败返回-1

2,msgctl函数
功能：消息队列的控制函数
原型：
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/msg.h>
	int msgctl(int msqid, int cmd, struct msqid_ds *buf);

参数：
msqid：由msgget函数返回的消息队列标识码
cmd：有三个可选的值

IPC_STAT 把msqid_ds结构中的数据设置为消息队列的当前关联值
IPC_SET 在进程有足够权限的前提下，把消息队列的当前关联值设置为msqid_ds数据结构中给出的值
IPC_RMID 删除消息队列

返回值：
成功返回0，失败返回-1

3,msgsnd函数
功能：把一条消息添加到消息队列中
原型：
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/msg.h>
	int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);

参数：

msgid：由msgget函数返回的消息队列标识码
msgp：指针指向准备发送的消息
msgze：msgp指向的消息的长度（不包括消息类型的long int长整型）
msgflg：默认为0

返回值：成功返回0，失败返回-1
消息结构一方面必须小于系统规定的上限，另一方面必须以一个long int长整型开始，接受者以此来确定消息的类型
	struct msgbuf
	{
		 long mtype;
		 char buff[32];
	};
	
4,msgrcv函数
功能：从一个消息队列收消息 
原型：
	ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg); 

参数：与msgsnd相同  msgtyp默认是1
返回值：成功返回实际放到接收缓冲区里去的字符个数，失败返回-1

//共享内存
,/使得多个进程可以访问同一块内存空间，是最快的可用IPC形式。

Linux的共享内存机制

1,shmget函数
,/shmget函数用来创建共享内存或者返回一个已存在的共享内存标识。
	int shmget(key_t key, size_t size, int shmflg);

第一个参数，共享内存段的命名，shmget函数成功时返回一个与key相关的共享内存标识符（非负整数），用于后续的共享内存函数。调用失败返回-1。
其它的进程可以通过该函数的返回值访问同一共享内存，它代表进程可能要使用的某个资源，程序对所有共享内存的访问都是间接的，程序先通过调用shmget函数并提供一个键，再由系统生成一个相应的共享内存标识符（shmget函数的返回值），只有shmget函数才直接使用信号量键，所有其他的信号量函数使用由semget函数返回的信号量标识符。
第二个参数，size以字节为单位指定需要共享的内存容量(字节)。
第三个参数，shmflg是权限标志，它的作用与open函数的mode参数一样，如果要想在key标识的共享内存不存在时，创建它的话，可以与IPC_CREAT做或操作。共享内存的权限标志与文件的读写权限一样，举例来说，0644，它表示允许一个进程创建的共享内存被内存创建者所拥有的进程向共享内存读取和写入数据，同时其他用户创建的进程只能读取共享内存。

2,shmat函数
,/shmat函数启动对该共享内存的访问。
	void *shmat(int shm_id, const void *shm_addr, int shmflg);

第一次创建完共享内存时，它还不能被任何进程访问，shmat函数的作用就是用来启动对该共享内存的访问，并把共享内存连接到当前进程的地址空间。
第一个参数，shm_id是由shmget函数返回的共享内存标识。
第二个参数，shm_addr指定共享内存连接到当前进程中的地址位置，通常为空，表示让系统来选择共享内存的地址。
第三个参数，shm_flg是一组标志位，通常为0。
调用成功时返回一个指向共享内存第一个字节的指针，如果调用失败返回-1。

3,shmdt函数
,/shmdt函数将共享内存从当前进程中分离。
	int shmdt(const void *shmaddr);
该函数用于将共享内存从当前进程中分离。注意，将共享内存分离并不是删除它，只是使该共享内存对当前进程不再可用。
参数shmaddr是shmat函数返回的地址指针，调用成功时返回0，失败时返回-1。

4,shmctl函数
,/shmctl函数用于控制共享内存。
	#include <sys/shm.h>
	int shmctl(int shmid, int cmd, struct shmid_ds *buf);

第一个参数，shmid是shmget函数返回的共享内存标识符。
第二个参数，cmd是要采取的操作，它可以取下面的三个值 ：
IPC_STAT：把shmid_ds结构中的数据设置为共享内存的当前关联值，即用共享内存的当前关联值覆盖shmid_ds的值。
IPC_SET：如果进程有足够的权限，就把共享内存的当前关联值设置为shmid_ds结构中给出的值
IPC_RMID：删除共享内存段

第三个参数，buf是一个结构指针，它指向共享内存模式和访问权限的结构。
shmid_ds结构如下：
	struct shmid_ds 
	{
		struct ipc_perm shm_perm;    /* Ownership and permissions */
		size_t	shm_segsz;   /* Size of segment (bytes)	  */
		time_t	shm_atime;   /* Last attach time */
		time_t	shm_dtime;   /* Last detach time */
		time_t	shm_ctime;   /* Last change time */
		pid_t	shm_cpid;    /* PID of creator */
		pid_t	shm_lpid;    /* PID of last shmat(2)/shmdt(2) */
		shmatt_t	shm_nattch;  /* No. of current attaches */
		...
	};

例子见：
https://zhaoyang.blog.csdn.net/article/details/88147272
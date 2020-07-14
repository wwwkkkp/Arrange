
//12.多线程环境编程

一个进程中可以创建多少线程:32位linux系统中，300个左右，影响线程数量的主要是 调用栈大小 和 用户可以创建的最大进程数，
							创建一个线程大概需要10M,内存最大4G，可用3G，进程理论大小就是可用内存大小3G,所以是300个左右
							
进程最多可以创建的线程数是根据分配给调用栈的大小，以及操作系统（32位和64位不同）共同决定的。

	#include <stdio.h>
	#include <assert.h>
	#include <string.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <pthread.h>

	void * thread_fun(void * arg)
	{
		while(1)
		{
			char buff[128] = {"a b c d e f g h i g"};
			char *safePtr = NULL;
			char *s = strtok_r(buff, " ", &safePtr);  //将buff按照" "分割开来，*safePtr指向下一个分割的变量的地址
			while(s != NULL)
			{
				printf("fun s = %s\n", s);
				sleep(1);
				s = strtok_r(NULL, " ", &safePtr);
			}
		}
	}

	int main()
	{
		pthread_t id; 
		int res = pthread_create(&id , NULL, thread_fun, NULL);  //生成一个线程，执行函数thread_fun()；
		char buf[128] = {"1 2 3 4 5 6 7 8 9 10"};  //主线程照常进行
		char *safePtr = NULL;
		char *s = strtok_r(buf, " ", &safePtr);
		while(s != NULL)
		{
			printf("main s = %s\n", s);
			sleep(1);
			s = strtok_r(NULL, " ", &safePtr);
		}
		exit(0);
	}

	root@Wkp:/home/c++# ./thread 
	main s = 1
	fun s = a
	main s = 2
	fun s = b
	main s = 3
	fun s = c
	fun s = d
	main s = 4
	fun s = e
	main s = 5
	main s = 6
	fun s = f
	main s = 7
	fun s = g
	main s = 8
	fun s = h
	main s = 9
	fun s = i
	main s = 10
	fun s = g
	
	可以看出主线程和子线程交替进行

//在多线程环境中使用fork
在多线程环境中使用fork
我们先来分析一个程序，主线程中创建子线程，然后进行fork操作，子线程中进行加解锁操作，在子进程中同样进行加解锁操作，查看运行结果。
	#include <stdio.h>
	#include <assert.h>
	#include <string.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <pthread.h>

	pthread_mutex_t  mutex;
	void * thread_fun(void * arg)
	{
		pthread_mutex_lock(&mutex);//上锁
		printf("fun get lock\n");
		sleep(5);
		pthread_mutex_unlock(&mutex);  //解锁
		printf("fun unlock\n");
	}
	int main()
	{
		pthread_t id; 
		pthread_mutex_init(&mutex, NULL);  //新建一个锁
		int res = pthread_create(&id , NULL, thread_fun, NULL);
		sleep(1);
		pid_t pid = fork();
		assert(pid != -1);
		if(pid == 0)
		{
			printf("child will get lock\n");
			pthread_mutex_lock(&mutex);
			printf("child get lock\n");
			pthread_mutex_unlock(&mutex);
			printf("child unlock\n");
			exit(0);
		}
		wait(NULL);
		pthread_join(id, NULL);
		pthread_mutex_destroy(&mutex);
		printf("main over\n");
		exit(0);
	} 
	输出：
	fun get lock
	child will get lock
	fun unlock
	
	在多线程程序中fork出一个子进程，发现子进程无法正常工作。不能获得锁
	
	使用fork时会将原来进程中的所有内存数据复制一份保存在子进程中。但是在拷贝的时候，线程是无法被拷贝的。如果在原来线程中加了锁，在使用的时候会造成死锁。
	,/就是在拷贝的时候，加了锁，那子进程永远也不能获得锁，因为在子进程空间中，锁一直是上着的，因为进程是无法像线程一样访问主进程空间。
	
//pthread_atfork
pthread线程库为我们提供了pthread_atfork函数，用以解决在多线程环境中执行fork所引发的问题。

/*当父进程有多线程时，子进程继承父进程所有的互斥量、读写锁和条件变量的状态，子进程只存在一个线程，它是由父进程中调用fork的线程的副本构成的。如果父进程中的线程占有锁（任一线程），子进程同样占有这些锁。 */

将上面程序修改成：
	#include <stdio.h>
	#include <assert.h>
	#include <string.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <pthread.h>

	pthread_mutex_t  mutex;
	void * thread_fun(void * arg)
	{
		pthread_mutex_lock(&mutex);
		printf("fun get lock\n");
		sleep(5);
		pthread_mutex_unlock(&mutex);
		printf("fun unlock\n");
	}

	void fun_lock(void) //加锁
	{
		pthread_mutex_lock(&mutex);
	}

	void fun_unlock(void)  //解锁
	{
		pthread_mutex_unlock(&mutex);
	}

	int main()
	{
		pthread_t id; 
		pthread_mutex_init(&mutex, NULL);
		pthread_atfork(fun_lock, fun_unlock, fun_unlock);
		
		int res = pthread_create(&id , NULL, thread_fun, NULL);
		sleep(1);
		
		pid_t pid = fork();
		
		assert(pid != -1);
		if(pid == 0)
		{
			printf("child will get lock\n");
			pthread_mutex_lock(&mutex);
			printf("child get lock\n");
			pthread_mutex_unlock(&mutex);
			printf("child unlock\n");
			exit(0);
		}
		wait(NULL);
		pthread_join(id, NULL);
		pthread_mutex_destroy(&mutex);
		printf("main over\n");
		exit(0);
	} 


pthread_atfork函数在fork之前，但是直到程序执行到fork时，才会调用pthread_atfork函数，
在程序执行fork()之前，父进程会首先执行fun_lock进行加锁，之后父进程调用fun_unlock解锁，子进程从父进程复制过来的锁状态会调用fun_unlock解锁，程序正常执行。

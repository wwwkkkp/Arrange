

//基于TCP实现服务器端、多客户端通信（多线程、多进程并发编程）

前面举得TCP的例子都是 单客户机环境下的服务器端与客户端的通信，在实际使用时，更多的是并发的多客户机的访问，
实现多客户的并发访问，使用两种方式:/多线程方式和多进程方式

//单客户机问题
while (1)
	{
		accept(); // 接收连接  accept函数是阻塞的，当连上一个客户端后，直到等到断开才能连接第二个,注意：accept在调用期间是阻塞的，返回值后不阻塞
		while (1)
		{
			/* 读写处理 */
			···
			recv();
			send();
		}
		close(); // 关闭连接
	}
两个连接请求同时到，服务器先连接了一个
此刻服务器的主线程正在执行与第一个客户端进行读写处理，不能去处理第二个客户端的连接请求（accept函数），因此第二个客户端阻塞。
直到第一个客户端关闭套接字后，主线程退出读写处理模块，继续循环读取新连接，这时第二个客户端的连接请求才从监听队列中拿出


//多线程方式实现客户端并发访问
,/每收到一个连接请求，就创建一个新线程来处理它，我们把之前的读写处理模块放入线程执行函数中
	// TCP客户端 服务器端通信 ：多线程实现
	#include <stdio.h>
	#include <unistd.h>
	#include <assert.h>
	#include <string.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <pthread.h>

	/* 线程函数，新连接的读写处理 */
	void* thread_fun(void* arg)
	{
		int connfd = *(int*)arg;

		while (1)
		{
			char buffer[128] = { 0 };

			int n = recv(connfd, buffer, 127, 0);
			if (n <= 0) /* recv返回0表示通信对方已经关闭连接 */
			{
				break;
			}
			printf("buffer(%d) = %s\n", n, buffer);
			send(connfd, "OK", 2, 0);
		}
		printf("One client over!\n");
		/* close关闭套接字 */
		close(connfd);
	}

	int main()
	{
		/* 1、通过socket函数创建监听套接字 */
		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		assert(sockfd != -1);

		/* 定义服务器和客户端的专用socket地址*/
		struct sockaddr_in saddr, caddr;
		memset(&saddr, 0, sizeof(saddr));// 将其内存清空

		/* 设置地址族、端口号、ip地址 */
		saddr.sin_family = AF_INET; // 
		saddr.sin_port = htons(6000);
		saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		/* 2、通过bind将套接字与socket地址绑定起来 */
		int res = bind(sockfd,
		 (struct sockaddr*) & saddr, sizeof(saddr));
		assert(res != -1);

		/* 3、创建监听队列，监听队列长度设为5 */
		listen(sockfd, 5);

		while (1)
		{
			int len = sizeof(caddr);

			/*
			** accept监听socket，若存在，则从监听队列中接受一个连接
			** 函数返回一个链接套接字，否则，没有新连接请求，则阻塞等待
			*/
			int connfd = accept(sockfd,
			 (struct sockaddr*) & caddr, (socklen_t*)& len);

			/* accept失败返回-1表示没有获取到连接，继续循环 */
			if (connfd < 0)
			{
				continue;
			}

			printf("accept connfd = %d, ip = %s, port = %d\n",connfd, 
			inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

			pthread_t id; // 定义线程号
			/* 创建新线程，将连接套接字connfd作为参数传入 */
			pthread_create(&id, NULL, thread_fun, (void*)& connfd);
		}
		close(sockfd);
	}


//多进程方式实现客户端并发访问
,/和上面一样的思路：我们采用多进程的方式，每次收到连接请求都创建一个子进程，子进程负责处理读写模块。
	// TCP客户端 服务器端通信（多客户机) ：多进程实现
	#include <stdio.h>
	#include <unistd.h>
	#include <assert.h>
	#include <string.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <pthread.h>
	#include <signal.h>
	#include <sys/wait.h>

	void sig_fun(int sig)
	{
		//int val = 0;
		while (waitpid(-1, &sig, 0) > 0) {}
	}

	int main()
	{
		signal(SIGCHLD, sig_fun);

		/* 通过socket函数创建监听套接字 */
		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		assert(sockfd != -1);

		/* 定义服务器和客户端的专用socket地址*/
		struct sockaddr_in saddr, caddr;
		memset(&saddr, 0, sizeof(saddr));// 将其内存清空

		/* 设置地址族、端口号、ip地址 */
		saddr.sin_family = AF_INET; // 
		saddr.sin_port = htons(6000);
		saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		/* 通过bind将套接字与socket地址绑定起来 */
		int res = bind(sockfd, 
		(struct sockaddr*) & saddr, sizeof(saddr));
		assert(res != -1);

		/* 创建监听队列，监听队列长度设为5 */
		listen(sockfd, 5);

		while (1)
		{
			int len = sizeof(caddr);

			/*
			** accept监听socket，若存在，则从监听队列中接受一个连接
			** 函数返回一个链接套接字，否则，没有新连接请求，则阻塞等待
			*/
			int connfd = accept(sockfd, 
			(struct sockaddr*) & caddr, (socklen_t*)& len);

			/* accept失败返回-1表示没有获取到连接，继续循环 */
			if (connfd < 0)
			{
				continue;
			}

			printf("accept connfd = %d, ip = %s, port = %d\n",connfd, 
			inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
			
			/** 每收到一个连接请求都创建一个子进程 */
			pid_t pid = fork();
			if (pid == -1)
			{
				continue;
			}
			else if (pid == 0) // 在子进程中实现读写处理
			{
				while (1)
				{
					char buffer[128] = { 0 };

					int n = recv(connfd, buffer, 127, 0);
					if (n <= 0) /* recv返回0表示通信对方已经关闭连接 */
					{
						break;
					}
					printf("buffer(%d) = %s\n", n, buffer);
					send(connfd, "OK", 2, 0);
				}
				printf("One client over!\n");
				/* close关闭套接字 */
				close(connfd);
			}
		}
		close(sockfd);
	}

//解决多进程方式下僵尸进程问题
我们可以看到上述程序虽然运行正确，但仍存在问题，即若由一方客户端退出，那么在服务器程序中，就会产生子进程先于父进程结束的情况，即会产生僵尸进程，若客户端非常多，那么这就会产生严重的问题。


1、通过wait方法，解决僵尸进程
signal(SIGCHLD, sig_fun);   //当子进程死亡之后，会向父进程发送信号SIGCHLD，在父进程中 就可以捕捉这个信号，并调用wait函数，处理僵尸进程
void sig_fun(){wait(NULL);}
	
2、通过waitpid方法，解决僵尸进程
signal(SIGCHLD, sig_fun);
void sig_fun(){waitpid(-1, NULL, WNOHANG);} // WNOHANG表示该系统调用非阻塞模式

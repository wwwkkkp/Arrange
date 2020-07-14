

//Linux网络编程  IO复用 : select系统调用详解（实现改进的多客户/服务器） 

Linux下实现IO复用的系统调用主要有select、poll和epoll，本文主要介绍select，后两个将在后续文章介绍。

以下情况下需要使用io复用：
1,客户端同时处理多个socket（如：非阻塞的connect技术）；
2,客户端程序需要同时处理用户输入和网络连接（如：聊天室程序）；
3,TCP服务器要同时处理监听socket和连接socket；
4,服务器要同时处理TCP请求和UDP请求（如：回射服务器）；
5,服务器同时监听多个端口，或者处理多种服务（xinetd服务器）；

select系统调用的主要用途是：在指定的一段时间内，轮询监听用户感兴趣的文件描述符，即用户添加记录到fd_set中的文件描述符，当监听到任何文件描述符有可读，可写和异常事件发生时，就会返回。


轮询：即一遍又一遍的循环监听从0到我们记录的这些文件描述符中的最大值。
fd_set：是一个结构体，这个结构体中仅包含一个整型数组，这个整型数组的每个元素的每个位代表一个文件描述符，所以select能同时处理的文件描述符的最大数量由这个数组的总位数决定，这个最大值为<sys/select.h>头文件中定义的一个常量FD_SETSIZE。


//select系统调用

#include <sys/select.h>
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

nfds:被监听的文件描述符的总数,它通常是readfd，writefd，exceptfd这三个描述符集中的最大描述符编号加1，因为文件描述符是从0开始计数的。

readfd，writefd，exceptfd:分别指向可读，可写，异常事件对应的文件描述符集合。
		这3个参数是fd_set结构指针类型,elect调用返回时，内核将修改它们来通知应用程序哪些文件描述符已经就绪。
		(可读：某个进程收到了数据，等待接收，可写:某个进程发送数据，)
		
timeout:设置select函数的超时时间,表示select愿意等待多长时间
	struct timeval{
			long    tv_sec;     //秒数
			long    tv_usec;    //微秒数
	};

select成功时返回就绪的文件描述符的总数，
如果在超时时间内没有任何描述符就绪，select返回0，select失败返回-1并设置errno。
如果在select等待期间，程序收到信号，则select立即返回-1，并设置errno为EINTR。


//程序示例一：读取键盘(标准输入)
	/*
	** Sample HTTP Server
	** AUTHOR：ZYZMZM
	** DATE: 17/4/2019
	*/
	// select系统调用：读取键盘
	#include <stdio.h>
	#include <unistd.h>
	#include <string.h>
	#include <assert.h>
	#include <stdlib.h>
	#include <sys/time.h>
	#include <sys/select.h>

	/* 标准输入：文件描述符为0 */
	#define STDIN 0 

	int main()
	{
		/* fd为标准输入文件描述符 0  */
		int fd = STDIN;
		fd_set fdset;

		while (1)
		{
			/* fdset初始化为空集合 */
			FD_ZERO(&fdset); 

			/* 在集合中添加fd传递的描述符 */ 
			FD_SET(fd, &fdset); 

			/* 超时时间设置为5s，即在标准输入stdin上最多等待5s */
			struct timeval tv = { 5, 0 };

			/* select返回值为n，表示有n个状态发生变化的描述符 */
			int n = select(fd + 1, &fdset, NULL, NULL, &tv); //只轮询可读信息

			/* select失败返回-1并设置errno */
			if (n == -1)		//当在等待期间有信号接入，终止等待，并返回-1
			{
				perror("select error");
			}
			/* select为0表示文件描述符都没有变化，那么打印出超时信息 */
			else if (n == 0)
			{
				printf("time out\n"); //超时时间是5s，所以没有就绪的进程时，就5s打印一次
			}
			else
			{
				/* 
				** 判断参数fd指向的文件描述符是否是由参数
				** fdset指向的fd_set集合中的一个元素 
				*/
				if (FD_ISSET(fd, &fdset))
				{
					char buffer[128] = { 0 };

					/* 从标准输入stdin读取数据到buffer中 */
					int res = read(fd, buffer, 127);

					/* 将buffer中的数据打印 */
					printf("read(%d) = %s\n", res, buffer);
				}
			}
		}
	}





//程序示例二：改进的多客户/服务器
通过用select调用来同时处理多个客户就无需再依赖于子进程了。


服务器可以让select调用同时检查监听套接字和客户的连接套接字。一旦select调用指示有活动发生，就可以用FD_ISSET来遍历所有可能的文件描述符，以检查是哪个上面有活动发生。

	如果是监听套接字可读，这说明正有一个客户试图建立连接，此时就可以调用accept而不用担心发生阻塞的可能
	如果是某个客户描述符准备好，这说明该描述符上有一个客户请求需要我们读取和处理(recv、send)
	如果读操作返回零字节，这表示有一个客户进程已结束，那么就关闭该套接字并把它从描述符集合中删除。

/*
** Sample HTTP Server
** AUTHOR：ZYZMZM
** DATE: 17/4/2019
*/

// select系统调用：改进的多客户/服务器
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include<sys/select.h>

#define MAXFD 10

/* 向集合fds中添加文件描述符fd */
void fds_add(int fds[], int fd)
{
	int i = 0;
	for (; i < MAXFD; i++)
	{
		if (fds[i] == -1)
		{
			fds[i] = fd;
			break;
		}
	}
}

/* 在集合fds中删除文件描述符fd */
void fds_del(int fds[], int fd)
{
	int i = 0;
	for (; i < MAXFD; i++)
	{
		if (fds[i] == fd)
		{
			fds[i] = -1;
			break;
		}
	}
}

int main()
{
	/* 创建监听套接字（socket描述符），指定协议族ipv4，字节流服务传输 */
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);

	/* socket专用地址信息设置 */
	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* 命名套接字，将socket专用地址绑定到socket描述符上 */
	int res = bind(sockfd, (struct sockaddr*) & saddr, sizeof(saddr));
	assert(res != -1);

	/* 创建监听队列 */
	listen(sockfd, 5);

	fd_set fdset;

	/* 初始化文件描述符集合fds */
	int fds[MAXFD];
	int i = 0;
	for (; i < MAXFD; i++)
	{
		fds[i] = -1;
	}

	/* 将sockfd添加到文件描述符集合fds中 */
	fds_add(fds, sockfd);

	while (1)
	{
		/* fdset初始化为空集合，清除fdset的所有位 */
		FD_ZERO(&fdset);

		int maxfd = -1;
		int i = 0;
		/* 循环遍历找到最大的文件描述符 */
		for (; i < MAXFD; i++)
		{
			if (fds[i] == -1)
			{
				continue;
			}

			/* 设置fdset的fds[i]位 */
			FD_SET(fds[i], &fdset);

			if (fds[i] > maxfd)
			{
				maxfd = fds[i];
			}
		}

		/* 设置超时时间为5秒 */
		struct timeval tv = { 5,0 };

		/* 用n来接收select成功时返回就绪文件描述符的总数 */
		int n = select(maxfd + 1, &fdset, NULL, NULL, &tv);  //这里的fdset中只有sockfd，只要有连接申请，select都会收到，

		/* select失败返回-1并设置errno */
		if (n == -1)
		{
			perror("select error");
		}

		/* select为0表示文件描述符都没有变化，那么打印出超时信息 */
		else if (n == 0)
		{
			printf("time out\n");
		}
		else
		{
			/* 遍历所有可能的文件描述符，以检查是哪个上面有活动发生。*/
			for (i = 0; i < MAXFD; i++)
			{
				if (fds[i] == -1)
				{
					continue;
				}

				/* fdset的fds[i]位已经被标识，即有数据 */
				if (FD_ISSET(fds[i], &fdset)) //这里好像有点问题，如果有描述符3,4,5被标识，sockfd=3，当只有新连接申请来了以后，执行if语句，然后又循环到4,5,强行接收，收不到就中断？？
				//select是怎么判断是那个文件描述符响应，还是一响应就把所有的标识对象都扫描一遍，响应的那个接收数据，没响应的删除？？
				{
					/*
					**	此时有两种情况，若fds[i] == sockfd
					**	说明监听队列中有连接待处理，则使用accept拿出一个连接
					**	否则，没有新连接，我们直接使用recv接收客端数据，并打印
					*/
					if (fds[i] == sockfd) //这个意思就是第一次申请连接，
					{

						struct sockaddr_in caddr;
						int len = sizeof(caddr);

						/* 接收一个套接字已建立的连接，得到连接套接字connfd */
						int connfd = accept(sockfd, (struct sockaddr*) & caddr, (socklen_t *)&len);
						if (connfd < 0)
						{
							continue;
						}

						printf("accept connfd=%d\n", connfd);

						/* 将连接套接字connfd，添加到fds文件描述集合中 */
						fds_add(fds, connfd);  //后面就是connfd维护这个连接，不需要再连接了
					}
					else //轮询已经连接上的进程之间的通信
					{
						
						char buff[128] = { 0 };

						/* recv用来接收客端数据*/
						int res = recv(fds[i], buff, 127, 0);

						/* 接收服务器端的数据是零，即res返回0，说明客户端已经关闭 */
						if (res <= 0)
						{
							/* 关闭文件描述符fds[i] */
							close(fds[i]);
							
							/* 清除fds数组 */
							fds_del(fds, fds[i]);
							printf("one client over\n");
						}
						else
						{
							/* 输出客端发来的数据，并向客端发送一个OK的回复 */
							printf("recv(%d)=%s\n", fds[i], buff);
							send(fds[i], "ok", 2, 0);
						}
					}
				}
			}
		}
	}
}



//Linux网络编程   IO复用  epoll系列系统调用详解


内核事件表、操作函数epoll_ctl
epoll是Linux特有的I/O复用函数。它在实现和使用上与select、 poll有很大差异。首先，epoll使用一组函数来完成任务，而不是单个函数。其次，epoll把用户关心的文件描述符上的事件放在内核里的一个事件表中，从而无须像select和poll那样每次调用都要重复传入文件描述符集或事件集。但 epoll 需要使用一个额外的文件描述符，来唯一标识内核中的这个事件表。这个文件描述符使用如下 epoll_create 函数来创建：

#include <sys/epoll.h>
int epoll_create(int size);

size参数现在并不起作用，只是给内核一个提示，告诉它事件表需要多大。该函数返回的文件描述符将用作其他所有epoll系统调用的第一个参数，以指定要访问的内核事件表。



//操作epoll的内核事件表：

#include <sys/epoll.h>
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

epfd参数是要操作的文件描述符，op参数则指定操作类型，操作类型有如下3种： //对时间表的维护都是这个函数完成
	EPOLL_CTL_ADD，往事件表中注册fd上的事件
	EPOLL_CTL_MOD，修改fd上的注册事件
	EPOLL_CTL_DEL，删除fd上的注册事件
event参数指定事件，它是 epoll_event 结构指针类型。epoll_event的定义如下：
	struct epoll_event 
	{
		__uint32_t   events;      /* Epoll事件 */  比如可读可写等，和poll一样，只是名字在poll前加上E，如EPOLLIN：有数据可读
		epoll_data_t data;        /* 用户数据 */
	};
	data成员用于存储用户数据，其类型 epoll_data_t 的定义如下：

	typedef union epoll_data   //联合体
	{
		void  *ptr;
		int  fd;				//使用最多的是fd，它指定事件所从属的目标文件描述符
		__uint32_t  u32;
		__uint64_t  u64;
	} epoll_data_t;


//epoll_wait函数
epoll系列系统调用的主要接口是epoll_wait函数。它在一段超时时间内等待一组文件描述符上的事件，其原型如下：

#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event *events,
			   int maxevents, int timeout);

该函数成功时返回就绪的文件描述符的个数，**失败时返回 -1 **并设置ermo.
maxevents参数指定最多监听多少个事件

epoll_wait 函数如果检测到事件，就将所有就绪的事件从内核事件表（由epfd参数指定）中复制到它的第二个参数events指向的数组中，
这个数组只用于输出epoll_wait检测到的就绪事件。
而不像select和poll的数组参数那样既用于传入用户注册的事件，又用于输出内核检测到的就绪事件，这就极大地提高了应用程序索引就绪文件描述符的效率。


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define MAXFD 10

/* 向内核事件表epfd 中添加 新事件的文件描述符fd */
void epoll_add(int epfd, int fd)
{
	/* 设置epoll_event的结构成员 */
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = fd;

	/* EPOLL_CTL_ADD添加新事件及描述符到内核事件表 */
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
	{
		perror("epoll_ctl add error\n");
	}
}

void epoll_del(int epfd, int fd)
{
	/* 从内核事件表中移除fd */
	if (epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL) == -1)
	{
		perror("epoll_ctl del error\n");
	}
}

int create_sockfd();

int main()
{
	int sockfd = create_sockfd();
	assert(sockfd != -1);

	/* 创建内核事件表 */
	int epfd = epoll_create(MAXFD);
	assert(epfd != -1);

	/* 设置epoll_event的结构成员 */
	struct epoll_event ev;
	ev.data.fd = sockfd;
	ev.events = EPOLLIN;
	epoll_add(epfd, sockfd);

	/* events数组存放就绪描述符 */
	struct epoll_event events[MAXFD];

	while (1)
	{   
		/* 
		** epoll_wait返回的是前n个已经全就绪，
		** 那么我们不用全部遍历，只遍历前n个就可以
		** 超时时间设置为5秒
		*/
		int n = epoll_wait(epfd, events, MAXFD, 5000);

		/*  epoll_wait 调用失败 */
		if (n == -1)
		{
			perror("epoll wait error!\n");
		}
		else if (n == 0)
		{
			printf("time out!\n");
		}

		/* 只遍历前n个，因为内核已告诉我们前n个有就绪事件 */
		else
		{ 
			int i = 0;
			for (; i < n; ++i)
			{
				int fd = events[i].data.fd;
				if (fd == -1)
				{
					continue;
				}

				/* events 为内核为我们返回的就绪事件 */
				if (events[i].events & EPOLLIN)
				{
					if (fd == sockfd)
					{
						struct sockaddr_in caddr;
						int len = sizeof(caddr);
						
						/* 接收一个套接字已建立的连接，得到连接套接字connfd */
						int connfd = accept(sockfd, (struct sockaddr*) & caddr, (socklen_t *)&len);

						if (connfd < 0)
						{
							continue;
						}
						printf("connfd : %d\n", connfd);

						/* 将连接套接字connfd，添加到内核事件表中 */
						epoll_add(epfd, connfd);
					}
					else
					{
						char buff[128] = { 0 };

						/* recv用来接收客端数据 */
						int res = recv(fd, buff, 127, 0);
						if (res <= 0)
						{
							/* 
							** 注意：这里不能先close，应该先调用epoll_del，
							** 因为先调用close关闭了文件描述符后，再调用epoll_del
							** 内核将不能找到所要从内核事件表中移除的文件描述符
							**/
							epoll_del(epfd, fd);
							close(fd);
							printf("one client over\n");
							continue;
						}
						printf("buff %d = %s\n", fd, buff);
						send(fd, "OK", 2, 0);
					}
				}
			}
		}
	}
}

int create_sockfd()
{
	/* 创建监听套接字（socket描述符），指定协议族ipv4，字节流服务传输 */
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		return -1;
	}

	/* socket专用地址信息设置 */
	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* 命名套接字，将socket专用地址绑定到socket描述符上 */
	int res = bind(sockfd, (struct sockaddr*) & saddr, sizeof(saddr));
	if (res == -1)
	{
		return -1;
	}
	/* 创建监听队列 */
	listen(sockfd, 5);
	return sockfd;
}





//LT 和 ET模式
epoll 对文件描述符的操作有两种模式：

LT （Level Trigger，电平触发）模式
ET （Edge Trigger，边沿触发）模式


LT模式是默认的工作模式，这种模式下epoll 相当于一个效率较高的poll。

对于采用LT工作模式的文件描述符，当 epoll_wait 检测到其上有事件发生并将此事件通知应用程序后，应用程序可以不立即处理该事件，这样，当应用程序下一次调用epoll_wait时，epoll_wait会再次向应用程序通告此事件，直到该事件被处理。

而对于采用ET工作模式的文件描述符，当epoll_wait检测到其上有事件发生并将此事件通知应用程序后，应用程序必须立即处理该事件，因为后续的epoll_wait用将不再向应用程序通知这一事件，可见，ET模式在很大程度上降低了同一个epoll事件被重复触发的次数，因此效率要比LT模式高。


在ET工作模式下，我们不能使用普通的阻塞IO，因为数据的接收效率太低
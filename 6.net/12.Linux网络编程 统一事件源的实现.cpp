




//Linux网络编程 统一事件源的实现


简单的说就是可以通过IO复用舰艇管道等信息


下面我们给出了统一事件源的一个简单实现，程序只是简单的读取 Ctrl + C 信号，将其信号值打印屏幕上，并结束程序。但实际中，我们可以根据需要，将不同的信号指向不同的处理逻辑。

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define MAXFD 10

// 创建管道描述符数组pipefd
int pipefd[2];

/* 信号处理函数：将信号值写入管道的写端 */
void fun(int sig)
{
	write(pipefd[1], &sig, sizeof(sig));
}

/* 将文件描述符设置为非阻塞  */
void setnonblock(int fd)
{
	int oldfl = fcntl(fd, F_GETFL);
	int newfl = oldfl | O_NONBLOCK;
	if (fcntl(fd, F_SETFL, newfl) == -1)
	{
		perror("fcntl error");
	}
}

/* 向内核事件表epfd 中添加 新事件的文件描述符fd */
void epoll_add(int epfd, int fd)
{
	/* 设置epoll_event的结构成员 */
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = fd;

	/* EPOLL_CTL_ADD添加新事件及描述符到内核事件表 */
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
	{
		perror("epoll_ctl add error\n");
	}
	setnonblock(fd);
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

	/* 创建管道 */
	pipe(pipefd);

	/* 创建内核事件表 */
	int epfd = epoll_create(MAXFD);
	assert(epfd != -1);

	epoll_add(epfd, sockfd);

	/** 添加管道的读端到内核事件表 */
	epoll_add(epfd, pipefd[0]);
	signal(SIGINT, fun);

	/* events数组存放就绪描述符 */
	struct epoll_event events[MAXFD];

	int run = 1;
	while (run)
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
			if (errno != EINTR)
			{
				perror("epoll wait error!\n");
			}
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
						int connfd = accept(sockfd, (struct sockaddr*) & caddr, (socklen_t*)& len);

						if (connfd < 0)
						{
							continue;
						}
						printf("connfd : %d\n", connfd);

						/* 将连接套接字connfd，添加到内核事件表中 */
						epoll_add(epfd, connfd);
					}
					/** 若是管道的读端就绪，说明有信号产生，打印信号值 */
					else if (fd == pipefd[0])
					{
						int sig = 0;
						read(pipefd[0], &sig, sizeof(sig));
						printf("sig = %d\n", sig);
						run = 0;
					}
					else
					{   /* 拿到一个就绪的文件描述符后，循环读取  */
						while (1)
						{
							char buff[128] = { 0 };

							/* recv用来接收客端数据 */
							int res = recv(fd, buff, 1, 0);
							if (res == 0)
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
							/* 如果返回-1，则数据已被读取完毕，结束  */
							else if (res == -1)
							{
								send(fd, "OK", 2, 0);
								break;
							}
							else
							{
								printf("buff %d = %s\n", fd, buff);
							}
						}
					}
				}
			}
		}
	}
	close(sockfd);
	close(epfd);
	printf("main over!\n");
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

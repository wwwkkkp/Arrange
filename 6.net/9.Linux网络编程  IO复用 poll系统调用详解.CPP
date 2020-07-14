
//Linux网络编程  IO复用 : poll系统调用详解

poll系统调用
poll系统调用和select类似，也是在指定时间内轮询一定数量的文件描述符，以测试其中是否有就绪者，poll的原型如下：

#include <poll.h>
int poll(struct pollfd *fds, nfds_t nfds, int timeout);

fds参数是一个 pollfd 结构类型的数组，它指定所有我们感兴趣的文件描述符上发生的可读、可写和异常等事件，pollfd结构体的定义如下：
	struct pollfd 
	{
	   int   fd;         /* 文件描述符 */
	   short events;     /* 注册的事件 */
	   short revents;    /* 实际发生的事件，由内核返回 */
	};
	fd成员指定文件描述符；
	events成员告诉poll监听fd上的哪些事件      POLLIN	有数据可读;POLLOUT	数据可写
	revents成员则由内核修改，以通知应用程序上fd实际发生了哪些事件

nfds 参数指定被监听事件集合 fds 的大小
timeout参数指定poll的超时值，单位是亳秒，

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#define MAXFD 10

/* 向fds数组中添加文件描述符fd、并指定关注的事件 */
void fds_add(struct pollfd fds[], int fd)
{
    int i = 0;
    for(; i < MAXFD ;++i)
    {
        if(fds[i].fd == -1)
        {
            fds[i].fd = fd;
            fds[i].events = POLLIN;
            fds[i].revents = 0;
            break;
        }
    }
}

/* 在fds数组中删除指定文件描述符fd及其相关事件信息 */
void fds_del(struct pollfd fds[], int fd)
{
    int i = 0;
    for(; i < MAXFD ;++i)
    {
        if(fds[i].fd == fd)
        {
            fds[i].fd = -1;
            fds[i].events = 0;
            fds[i].revents = 0;
            break;
        }
    }
}

/* 初始化fds数组，其中文件描述符fd置为-1，其余都置为0 */
void fds_init(struct pollfd fds[])
{
    int i = 0;
    for(;i < MAXFD; ++i)
    {
        fds[i].fd = -1;
        fds[i].events = 0;
        fds[i].revents = 0;
    }
}

int create_sockfd();

int main()
{
	
    int sockfd = create_sockfd();
    assert(sockfd != -1);
    
	/* 初始化pollfd类型的结构体数组fds */
    struct pollfd fds[MAXFD];  //这里定义的是结构体数组，每一个结构体表示一个监听事件
	
	/* 初始化fds数组：fd置为-1表示无效 */
    fds_init(fds);

	/* 将sockfd添加到fds数组中 */
    fds_add(fds, sockfd);
	
    while(1)
    {
		/* 使用poll系统调用轮询，测试其中是否有就绪者 */
        int n = poll(fds, MAXFD, 5000);
        if(n < 0)
        {
            perror("poll error");
        }
		/* 返回0表示超时：都没有变化 */
        else if(n == 0) 
        {
            printf("time out\n");
        }
		
		/* fds数组存在就绪的文件描述符 */
        else
        {
			/* 循环遍历fds数组 */
            int i = 0;
            for(; i < MAXFD; i++)
            {
                if(fds[i].fd == -1)
                {
                    continue;
                }

				/* 
				** 可获得是哪个文件描述符上就绪 
				** fds[i]中的成员revents由系统内核修改
				*/
                if(fds[i].revents & POLLIN) //该文件描述符有数据可读
                {
					/*
					**	此时有两种情况，若fds[i].fd == sockfd
					**	说明监听队列中有连接待处理，则使用accept拿出一个连接
					**	否则，没有新连接产生，是有客端发来了数据，我们直接使
					**  用recv接收客端数据，并打印
					*/
                    if(fds[i].fd == sockfd) //描述符是连接套接字，说明是连接申请
                    {
                        struct sockaddr_in caddr;
                        int len = sizeof(caddr);
						
						/* 接收一个套接字已建立的连接，得到连接套接字connfd */
                        int connfd = accept(sockfd,(struct sockaddr*) &caddr,&len);

                        if(connfd < 0)
                        {
                            continue;
                        }

                        printf("connfd : %d\n", connfd);
						
                        /* 将新的连接套接字connfd，添加到pollfd结构类型的数组fds */
                        fds_add(fds, connfd);
                    }
                    else  //如果不是连接申请，那就是和其他已经连接的上的客户端的通信
                    {
                        char buffer[128] = {0};
						/* recv用来接收客端数据 */
                        int n = recv(fds[i].fd, buffer, 127, 0);
						
						/* 接收服务器端的数据是零，即n返回0，说明客户端已经关闭 */
                        if(n <= 0)
                        {
							/* 关闭文件描述符fds[i].fd */
                            close(fds[i].fd);
							
							/* 从fds数组中删除此文件描述符 */
                            fds_del(fds, fds[i].fd);
                            printf("one client over\n");
                            continue;
                        }
						/* n不为0，即接收到了数据，那么打印数据，并向客端回复一条信息 */
                        printf("recv[%d] = %s\n",fds[i].fd, buffer);
                        send(fds[i].fd ,"ok", 2, 0);
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
    if(sockfd == -1)
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
    int res = bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if(res == -1)
    {
        return -1;
    }
	/* 创建监听队列 */
    listen(sockfd, 5);
    return sockfd;
}

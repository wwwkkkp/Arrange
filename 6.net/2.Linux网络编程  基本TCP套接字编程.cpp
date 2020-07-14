
//Linux网络编程 | 基本TCP套接字编程

// TCP客户端 服务器端通信（单客户机) ：服务器端
#if 0
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	/* 1、通过socket函数创建监听套接字，参数AF_INET表示使用IPv4协议
	** SOCK_STREA提供面向连接的稳定数据传输,即TCP协议
	** 第三个参数为0表示默认协议，因为前两个参数已经确定了它的协议类型
	**/
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
	int res = bind(sockfd, (struct sockaddr*) & saddr, sizeof(saddr));
	assert(res != -1);

	/* 3、创建监听队列，监听队列长度设为5 */
	listen(sockfd, 5);

	while (1)
	{
		int len = sizeof(caddr);

		/*
		** 4、accept监听socket，若存在，则从监听队列中接受一个连接
		** 函数返回一个链接套接字，否则，没有新连接请求，则阻塞等待
		*/
		int connfd = accept(sockfd, (struct sockaddr*) & caddr, (socklen_t*)& len);

		/* accept失败返回-1表示没有获取到连接，继续循环 */
		if (connfd < 0)
		{
			continue;
		}

		printf("accept connfd = %d, ip = %s, port = %d\n",
			connfd, inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

		while (1)
		{
			char buffer[128] = { 0 };

			/*
			** 5、recv读取链接套接字connfd缓冲区buffer的内容
			** 成功返回实际读取到的数据的长度，flag置0使用默认
			*/
			int n = recv(connfd, buffer, 127, 0);
			if (n <= 0) /* recv返回0表示通信对方已经关闭连接 */
			{
				break;
			}
			printf("buffer(%d) = %s\n", n, buffer);

			/* 6、send向链接套接字connfd上写入数据，flag置0使用默认 */
			send(connfd, "OK", 2, 0);
		}
		printf("One client over!\n");
		/* close关闭套接字 */
		close(connfd);
	}
}


//查看
使用netstat命令查看系统上所有的网络套接字连接情况
	-a (all)显示所有选项，默认不显示LISTEN相关
	-t (tcp)仅显示tcp相关选项
	-u (udp)仅显示udp相关选项
	-n 拒绝显示别名，能显示数字的全部转化成数字。
	-l 仅列出有在 Listen (监听) 的服務状态

	-p 显示建立相关链接的程序名
	-r 显示路由信息，路由表
	-e 显示扩展信息，例如uid等
	-s 按各个协议进行统计
	-c 每隔一个固定时间，执行该netstat命令。

	提示：LISTEN和LISTENING的状态只有用-a或者-l才能看到

// TCP客户端 服务器端通信（单客户机) ：客户端
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	/* 1、socket函数创建套接字 */
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);

	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	
	/* 设置要连接的服务器端的IP地址和端口等属性 */
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	/** 
	** 2、connect函数与服务器端三次握手建立连接，建立成功后，
	** sockfd就唯一地标识这个连接，客户端就可以通过读写sockfd
	** 来与服务器进行数据通信
	*/
	int res = connect(sockfd, (struct sockaddr*) & saddr, sizeof(saddr));
	assert(res != -1);

	while (1)
	{
		printf("input:");
		char buffer[128] = { 0 };
		fgets(buffer, 128, stdin); //从键盘输入字符

		/* 客户端发送bye，即标识客户端要终止连接 */
		if (strncmp(buffer, "bye", 3) == 0)
		{
			printf("Connect will close······\n");
			break;
		}
		/* 3、send向sockfd即写入数据，即向服务器发送数据，flag位默认 */
		send(sockfd, buffer, strlen(buffer), 0);
		memset(buffer, 0, 128); // 清空buffer，准备下次读取

		/* 4、recv从sockfd读入数据，即读取服务器回复的数据，flag位默认 */
		recv(sockfd, buffer, 127, 0);
		printf("buffer = %s\n", buffer);
	}
	/* 5、close关闭连接 */
	close(sockfd);
}

/**
当客户端通过close关闭连接（四次挥手）时，出现的状态，由下图我们可以看出，客户端进入了TIME_WAIT状态，处理此服务端发送的数据和网络中由这个连接产生的报文，收到后都丢弃；TIME_WAIT状态会持续2MSL的时间，然后连接关闭。*/具体为什么要有这个TIME_WAIT见后面章节


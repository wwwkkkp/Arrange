



//Linux网络编程 | 基本UCP套接字编程

,/UDP是无连接的、不可靠的数据报协议，它尽最大努力交付，不保证可靠交付，需要上层协议来处理数据确认和超时重传，UDP协议没有拥塞控制，其支持一对一、一对多、多对一和多对多的交互。



// UDP客户端 服务器端通信：服务器端
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	/* 1、创建socket， SOCK_DGRAM表示使用数据报套接字(UDP) */
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	assert(sockfd != -1);

	struct sockaddr_in saddr, caddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* 2、命名socket：bind，将套接字地址与sockfd绑定 */
	int res = bind(sockfd, (struct sockaddr*) & saddr, sizeof(saddr));
	assert(res != -1);

	while (1)
	{
		int len = sizeof(caddr);
		int buff[128] = { 0 };
		
		/* 3、recvfrom：循环接收来自客户端的数据 */
		int connfd = recvfrom(sockfd, buff, 127, 0,
			(struct sockaddr*) & caddr, (socklen_t *)&len);
		if (connfd == -1)
		{
			continue;
		}
		printf("port : %d, buff = %s\connfd",
		 ntohs(caddr.sin_port), buff);
		 
		/* 4、sendto：把UDP数据报发给客户端 */
		sendto(sockfd, "OK", 2, 0,
			(struct sockaddr*) & caddr, sizeof(caddr));
	}
	/* 5、close：关闭网络连接(套接字) */
	close(sockfd);
}


// UDP客户端 服务器端通信：客户端
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main()
{
	/* 1、创建socket， SOCK_DGRAM表示使用数据报套接字(UDP) */
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	assert(sockfd != -1);

	struct sockaddr_in saddr, caddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	/* 2、命名socket：bind，将套接字地址与sockfd绑定 */
	int res = bind(sockfd, (struct sockaddr*) & saddr, sizeof(saddr));
	assert(res != -1);

	while (1)
	{
		char buffer[128] = { 0 };
		printf("input : \n");

		fgets(buffer, 128, stdin);
		
		/* 3、sendto：把UDP数据报发送给服务器 */
		sendto(sockfd, buffer, 127, 0, (struct sockaddr*) & saddr, sizeof(saddr));
		int len = sizeof(saddr);
		memset(buffer, 0, 128); // 清空缓冲区，准备下次写入
		
		/* 4、recvfrom：循环接收来自服务器响应的数据 */
		recvfrom(sockfd, buffer, 127, 0, (struct sockaddr*) & saddr, (socklen_t *)&len);
		printf("buffer = %s\n", buffer);
	}
	/* 5、close：关闭网络连接(套接字) */
	close(sockfd);
}



//其实是UDP是可以不分服务器和看客户端的，因为两端代码差不多，就是一发一收
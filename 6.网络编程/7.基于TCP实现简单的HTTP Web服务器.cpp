

//基于TCP实现简单的HTTP Web服务器



/*
** Sample HTTP Server
** AUTHOR：ZYZMZM
** DATE: 17/4/2019
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IPSTR "192.168.204.129" /* 服务器IP address */
#define PORT 80 /* http协议默认的80端口 */
#define BFSIZE 100 /* 定义接收缓冲区的大小为100 */

/*  
** 函数声明：创建套接字、命名套接字、
** 创建监听队列等操作，函数返回socket描述符
*/
int create_socket(); 

int main()
{
	/* 获取到已创建的套接字描述符 */
	int sockfd = create_socket();
	assert(sockfd != -1);

	while (1)
	{
		struct sockaddr_in caddr;
		int len = sizeof(caddr);

		/* accept接收新的客户连接 */
		int connfd = accept(sockfd, (struct sockaddr*) & caddr, (socklen_t *)&len);

		/* 没有新连接则继续循环监听 */
		if (connfd <= 0) 
		{
			continue;
		}

		char buff[BFSIZE] = { 0 };

		int n = recv(connfd, buff, BFSIZE - 1, 0);
		printf("recv(%d):\%s\n", n, buff);

		/*  以下为HTTP请求报文的构造 */
		char* s = strtok(buff, " ");
		if (s == NULL)
		{
			close(connfd);
			continue;
		}

		/* 拿到"方法字段" */
		printf("method:%s\n", s);
		s = strtok(NULL, " ");

		/* 构造资源URL" */
		char path[128] = { "/home/zy/Desktop/MyCode" };
		if (strcmp(s, "/") == 0)
		{
			/* 默认返回主页index.html */
			strcat(path, "/index.html"); 
		}
		else
		{
			/* 否则将客端请求的页面返回 */
			strcat(path, s); 
		}

		/* 打开资源文件，准备返回给客端 */
		int fd = open(path, O_RDONLY);

		/* 以下为404错误的响应报文构造*/
		if (fd == -1)
		{
			char res_buff[256] = { "HTTP/1.1 404 Not Found\r\n" };
			strcat(res_buff, "Server: myhttp\r\n");
			strcat(res_buff, "Content-Length: 3\r\n");
			strcat(res_buff, "\r\n");
			strcat(res_buff, "404\r\n");
			
			/* 将错误信息直接返回给客端 */
			send(connfd, res_buff, strlen(res_buff), 0);
			close(connfd);
			continue;
		}

		/* 以下为请求成功时的响应报文构造 */

		/* 将文件指针重新定位到文件末尾获取文件大小 */
		int size = lseek(fd, 0, SEEK_END);
		lseek(fd, 0, SEEK_SET); /* 将文件指针置回文件起始位置 */

		/* 
		** 状态行字段：协议版本、状态码、短语
		** 最后有回车和换行(\r\n)
		*/
		char head_buff[128] = { "HTTP/1.1 200 OK\r\n" };
		strcat(head_buff, "Server: myhttp\r\n");
		sprintf(head_buff + strlen(head_buff), "Content-Length: %d\r\n", size);
		strcat(head_buff, "\r\n");
		
		/* 将响应报文发送给客户端 */
		send(connfd, head_buff, strlen(head_buff), 0);
	
		/* 将响应报文信息在服务器端进行打印 */
		printf("\nsend:\n%s\n", head_buff);

		char send_buff[1024] = { 0 };

		/* 
		** 接下来是将客户请求的资源文件(例如html文件，默认为index.html) 
		** 发送给客端，若是html文件则由客端的WEB浏览器负责解释执行
		*/
		int num = 0;
		while ((num = read(fd, send_buff, 1024)) > 0)
		{
			send(connfd, send_buff, num, 0);
		}
		close(fd); // 关闭资源文件描述符
		close(connfd); // 关闭连接套接字
	}

}

/*
** create_socket函数负责创建套接字、命名套接字、
** 创建监听队列等操作，返回创建成功的socket描述符
*/
int create_socket()
{
	/* 使用socket函数指定协议族ipv4，并使用字节流传输服务 */
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* 若创建失败，则直接将-1返回，在程序中进行断言 */
	if (sockfd == -1)
	{
		return -1;
	}

	/* 
	** 创建专用socket地址：设置服务器ip、
	** 端口(使用http协议默认的80号端口)
	*/
	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);
	saddr.sin_addr.s_addr = inet_addr(IPSTR);

	/* 
	** 命名套接字：将上面创建好的本地专用socket
	** 地址绑定到创建的socket描述符上
	*/
	int res = bind(sockfd, (struct sockaddr*) & saddr, sizeof(saddr));

	/* 命名失败直接将-1返回，在主程序中进行断言 */
	if (res == -1)
	{
		return -1;
	}

	/* 创建sockfd的监听队列，设置可以进行连接的队列长度为20 */
	listen(sockfd, 20);

	/* 将创建好的socket描述符返回给主程序，在主程序中进行其余操作 */
	return sockfd;
}



当请求一个网页后，收到一个html文件，浏览器进行解码，解码中出现图片等文件，http会自动请求这些文件。
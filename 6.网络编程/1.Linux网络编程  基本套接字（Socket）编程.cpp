

//Linux网络编程 | 基本套接字（Socket）编程

//TCP/IP协议簇
其实TCP/IP协议簇已经帮我们解决了这个问题，网络层的“ip地址”可以唯一标识网络中的主机，而传输层的“协议+端口”可以唯一标识主机中的应用程序（进程）。这样利用三元组（ip地址，协议，端口）就可以标识网络的进程了，网络中的进程通信就可以利用这个标志与其它进程进行交互。


1.socket函数
#include <sys/types.h>
#include <sys/socket.h>
int socket(int domain,int type, int protocol);

domain:遵循的是什么网络协议    	+---------------------------------------------
								|   domain        |              说  明       
								|---------------- | --------------------------
								|   AF_INET       |             IPv4协议      
								|   AF_INET6      |             IPv6协议      
								|   AF_LOCAL      |             Unix域协议    
								|   AF_ROUTE      |             路由套接字    
								|   AF_KEY        |             秘钥套接字    
								+---------------------------------------------    
type:   哪种通信方式			+---------------------------------------------
								|   type          |          说     明        
								|---------------- | --------------------------
								|  SOCK_STREAM    |         字节流套接字(TCP)      
								|  SOCK_DGRAM     |         数据报套接字(UDP)     
								|  SOCK_SEQPACKET |         有序分组套接字    
								|  SOCK_PAM       |         原始套接字        
								+---------------------------------------------

protocol为协议类型常值，取值如下：
								+---------------------------------------------
								|   protocol      |          说      明       
								|---------------- | --------------------------
								|   IPPROTO_TCP   |          TCP传输协议      
								|   IPPROTO_UDP   |          UDP传输协议      
								|   IPPROTO_SCTP  |          SCTP传输协议     
								+---------------------------------------------


2.bind函数
,/将socket创建的文件描述符绑定到一个指定的socket地址空间也就是对应的IP的端口号指定的一个进程。
#include <sys/types.h>
#include <sys/socket.h>

int bind(int sockfd,const sockaddr* my_addr,socklen_t addrlen);
sockfd：socket创建的文件描述符
my_addr：储存待链接的IP地址和端口号等的结构体
addrlen：参数2结构体的长度

3.listen函数
,/socket被命名之后还不能马上接受客户的连接，需要创建一个监听队列存放待处理的客户连接。为指定的socket设置监听队列，设置队列的长度。默认是5
#include <sys/socket.h>
int listen(int sockfd, int backlog);
backlog：允许队列的最大长度

4.accept函数
当目标客户端发链接请求的时候，服务器收到，并通过accpt建立链接
#include <sys/types.h>
#include <sys/socket.h>
int accept(int sockfd,struct sockaddr *addr, socklen *addrlen);

5.connect函数
客户端发起连接，客户端通过connect调用主动的与服务器建立连接。
#include <sys/types.h>
#include <sys/socket.h>
int connect(int sockfd,const struct sockaddr *serv_addr,socklen_t addrlen);
serv_addr：储存当前客户端的IP地址和申请进程的端口号的结构体
addrlen：结构体大小

6.close函数
关闭连接
#include <unistd.h>
int close(int fd);
fd是待关闭的socket的描述符，

7.TCP数据读写
对文件的读写操作read和write同样适用于socket。
同时socket编程接口也提供几个专门的数据读写的系统调用，增加对数据的读写控制。
#include <sys/types.h>
#include <sys/socket.h>
ssize_t recv(int sockfd,void *buf,size_t len,int flags);
ssize_t send(int sockfd,const void *buf,size_t len,int flags);

8.UDP读写
recvto
sendto
具体见例题


//主机字节序和网络字节序
大端字节序：一个整数的高位字储存在内存的低地址处。
小端字节序：是指整数的高位字节存储在内存的高地址。

主机字节序：小端字节序，因此称为主机字节序。
网络字节序：大端字节序也称为网络字节序。



		#include<netinet/in.h>
		unsigned long int htonl(unsigned long int hostlong);
		 
		unsigned short int htons(unsigned short int hostshort);
		 
		unsigned long int ntohl(unsigned long int netlong);
		 
		unsigned short int ntohs(unsigned short int netshort);

		//他们的含义很明确，比如htonl表示为：“host to nettwork long”

		//在这四个函数中，长整型函数通常用来转换IP地址，

		//短整型函数用来转换端口号。


//客户端 / 服务器模式及编程流程
服务器端：socket -> bind -> listen -> accept -> 数据处理 -> close
客户端：socket -> connect -> 数据处理 -> close
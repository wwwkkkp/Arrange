


//6.虚拟内存技术


虚拟内存:可让系统看上去具有比实际物理意义内存大的多的内存空间，并为实现多道程序的执行创造了条件。

虚拟内存的大小和CPU程序计数器有关，32位处理器最多访问2^32个地址，也就是4G大小的内存空间，也就是0x00000000~0xFFFFFFFF

,/因为32位处理器最多访问4g的内存，所以如果物理地址也是4G的话，那处理器要访问的地址和物理地址就一一对应了，但是这是理想情况

但遗憾的是，实际上计算机所配置内存的实际空间常常小于处理器的寻址范围，也就是内存小于4G的情况很多，

如果实际内存是1G，需要运行4G 的程序，是无法满足的

实践和研究都证明:/**一个应用程序总是逐段被运行的，而且在一段时间内会稳定运行在某一段程序里。*/
/把要运行的那一段程序从辅存复制到内存中来运行，而其他暂时不运行的程序段就让它仍然留在辅存。

在计算机技术中,/把内存中的程序段复制回外存的做法叫做“ 换出 ”，而把外存中程序段映射到内存的做法叫做“ 换入 ”。/经过不断有目的的换入和换出，处理器就可以运行一个大于实际物理内存的应用程序了;/或者说，处理器似乎是拥有了一个大于实际物理内存的内存空间。于是，这个存储空间叫做虚拟内存空间，而把真正的内存叫做实际物理内存，或简称为物理内存。

/*综上所述，虚拟内存技术的实现，是建立在应用程序可以分成段，并且具有“在任何时候正在使用的信息总是所有存储信息的一小部分 ”的局部特性基础上的。*/

	#include <stdio.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <assert.h>

	int main()
	{
		char * s = (char *)malloc(128);
		assert(s != NULL);

		pid_t pid = fork();
		assert(pid != -1);
		
		if(pid == 0)
		{
			strcpy(s,"child");
		}
		else
		{
			strcpy(s,"parent");
		}
		printf("s= %s,s=%x\n",s,s);  //%x是取地址符
		sleep(1);
		printf("s=%s,s=%x\n",s,s);

		exit(0);
	}
	输出：
	s=parent,s=9ccc008  //这里父子进程的地址是一样的，但由于其为两个不同的进程，那么其物理地址实际是不同的。
	s=chlid,s=9ccc008
	s=parent,s=9ccc008
	s=chlid,s=9ccc008
	
	

//Linux的虚拟内存技术
页：Linux把虚存空间分成若干个大小相等的存储分区，每个分区就叫页
页框：与虚拟内存对应，物理内存也被分成若干块 ，每一块叫页框
页与页框一般4K大小

虚拟内存与物理内存之间的映射关系的表叫做页表，这个在PDF中比较清楚

处理器遇到的地址都是虚拟地址。
虚拟地址和物理地址都分成页码（页框码）和偏移值两部分;
/在由虚拟地址转化成物理地址的过程中，偏移值不变。而页码和页框码之间的映射就在一个映射记录表——页表中。


//请页与交换
虚存页面到物理页框的映射叫做页面的加载。

当处理器试图访问一个虚存页面时，首先到页表中去查询该页是否已映射到物理页框中，并记录在页表中。
1,如果在，则MMU会把页码转换成页框码，并加上虚拟地址提供的页内偏移量形成物理地址后去访问物理内存；
2,如果不在，则意味着该虚存页面还没有被载入内存，这时MMU就会通知操作系统：发生了一个页面访问错误（页面错误），会触发缺页中断
	,/接下来系统会启动所谓的“请页”机制，调用相应的系统操作函数，判断该虚拟地址是否为有效地址。

	如果虚拟地址有效，就从虚拟内存中将该地址指向的页面读入到内存中的一个空闲页框中，并在页表中添加上相对应的表项，最后处理器将从发生页面错误的地方重新开始运行；
	如果是无效的地址，则表明进程在试图访问一个不存在的虚拟地址，此时操作系统将终止此次访问。
	
换页
在请页成功之后，内存中已没有空闲物理页框了。
这时，系统必须启动所谓地“换页”机制，即调用相应的内核操作函数，在物理页框中寻找一个当前不再使用或者近期可能不会用到的页面所占据的页框。
找到后，就把其中的页移出，以装载新的页面;
/对移出页面根据两种情况来处理：如果该页未被修改过，则删除它；如果该页曾经被修改过，则系统必须将该页写回辅存/;

/为了公平地选择将要从系统中抛弃的页面，Linux系统使用最近最少使用（LRU）页面的换页算法。///其他换页算法见pdf
最近最少使用（LRU）页面换页算法：根据系统中每个页面被访问的频率，为物理页框中的页面设置了一个叫做年龄的属性。页面被访问的次数越多，则页面的年龄最小；相反，则越大。而年龄较大的页面就是待换出页面的最佳候选者。



//快表
在系统每次访问虚存页时，都要在内存的所有页表中寻找该页的页框，这是一个很费时间的工作;/但是，人们发现，系统一旦访问了某一个页，那么系统就会在一段时间内稳定地工作在这个页上。/;
/所以，为了提高访问页表的速度，系统还配备了一组正好能容纳一个页表的硬件寄存器，这样当系统再访问虚存时，就首先到这组硬件寄存器中去访问，系统速度就快多了。
这组存放当前页表的寄存器叫做快表。/*注意：快表是硬件寄存器，不在内存中*/


//页的共享
在多程序系统中，常常有多个程序需要共享同一段代码或数据的情况。linux中的方法:/使这些相关程序的虚拟空间的页面在页表中指向内存中的同一个页框。

//页的保护
页表实际上是由虚拟空间转到物理空间的入口。因此，为了保护页面内容不被没有该页面访问权限的程序所破坏，就应在页表的表项中设置一些访问控制字段，用于指明对应页面中的内容允许何种操作，从而禁止非法访问。
/*页的保护机制是在页框码上*/一个页框码代表4k的物理内存，只需要12位的地址，在实际情况中，一个页框码的前20位是存地址，后12位是放权限,/但是Linux并没有这样做，反而重新定义了一个结构体来存放，通过“或”运算来将两者结合。

//多级页表
如果一个页表很大，查找不方便，就需要多级页表，
二级页表：虚拟地址32位，32~22 查询一级页表，21~12 查询二级页表  11~0是偏移量

,/Linux系统使用了三级页表结构：页目录（Page Directory，PGD）、中间页目录（Page Middle Directory，PMD）、页表（Page Table，PTE）。

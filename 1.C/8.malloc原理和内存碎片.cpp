

//malloc原理和内存碎片

malloc的内存分配方式有两种 brk和mmap （不考虑共享内存）

brk:当malloc申请的空间小于128k的时候，使用这个方式
mmap:当malloc申请空间大于128k的时候，使用mmap方式

因为malloc是动态内存分配，所以是存储在data段的堆区

brk:在堆指针的基础上 向高地址延伸，  _edata指针即为堆顶的指针，通过移动_edata指针实现brk内存分配
mmap:在堆和栈之间的区域寻找一块空闲区域作为虚拟内存，并赋初值为0.

注意：brk和mmap分配的都是虚拟存储，而不是物理存储，当系统第一次访问到这些区域的时候，发生缺页中断，然后系统才分配物理存储，并将虚拟存储和物理存储映射起来
	  如果用malloc分配了A这块内容，然后从来不访问它，那么，A对应的物理页是不会被分配的。 
	  
当一个进程发生缺页中断的时候，进程会陷入内核态，执行以下操作： 
1、检查要访问的虚拟地址是否合法 
2、查找/分配一个物理页 
3、填充物理页内容（读取磁盘，或者直接置0，或者啥也不干） 
4、建立映射关系（虚拟地址到物理地址） 
5、重新执行发生缺页中断的那条指令 
如果第3步，需要读取磁盘，那么这次缺页中断就是majflt，否则就是minflt。 



区分brk和mmap的目的：在操作系统中，  brk分配的内存需要等到高地址内存释放以后才能释放；而mmap分配的内存可以单独释放。

//关于free:
如果进程a分配了30k的地址空间，然后进程b分配了40k的地址空间，如果在b还没有释放空间之前，就执行了语句free(a)，那a的30k的区域不会释放物理内存和虚拟内存，但是可以作为空闲区域给后面申请空间小于等于30k的进程使用，但是会产生内存碎片，如何处理见操作系统课程






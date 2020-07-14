


//5.内核态与用户态

内核态:/CPU可以访问内存所有数据, 包括磁盘和外围设备, 例如硬盘, 网卡， CPU也可以将自己从一个程序切换到另一个程序
用户态:/只能受限的访问内存, 且不允许访问外围设备. 占用CPU的能力被剥夺, CPU资源可以被其他程序获取


//内核态与用户态的转换

/*所有用户程序都是运行在用户态的, 但是有时候程序确实需要做一些内核态的事情, 例如从硬盘读取数据, 或者从键盘获取输入等*/， 而唯一可以做这些事情的就是操作系统, 所以此时程序就需要向操作系统请求以程序的名义来执行这些操作。

这时需要一个这样的机制:/用户态程序切换到内核态，但是不能控制在内核态中执行的指令，这种机制叫系统调用,//** 在CPU中的实现称之为陷阱指令(Trap Instruction)，用户态执行陷阱指令转换成内核态。*/

它们的工作流程如下:
1,/用户态程序将一些数据值放在寄存器eax中, 或者使用参数创建一个堆栈(stack frame), 以此表明需要操作系统提供的服务。/
2,/用户态程序执行陷阱指令，CPU切换到内核态，并跳到位于内存指定位置的指令/，这些指令是操作系统的一部分，它们具有内存保护，不可被用户态程序访问
	这些指令称之为陷阱(trap)或者系统调用处理器(system call handler)。它们会读取程序放入内存的数据参数, 并执行程序请求的服务
	
	注意：/*用户态的时候程序也在cpu中执行，然后CPU执行陷阱指令，cpu进入内核态，去访问指定位置的信息，如内存，外围设备等。*/
3,系统调用完成后, 操作系统会重置CPU为用户态并返回系统调用的结果



//用户态切换到内核态的3种方式
1,系统调用:
/这是用户态进程主动要求切换到内核态的一种方式，/用户态进程通过系统调用申请使用操作系统提供的服务程序完成工作,/系统调用的机制其核心还是使用了操作系统为用户特别开放的一个中断来实现/，例如Linux的int 80h中断。

2,异常
当CPU在执行运行在用户态下的程序时，发生了某些事先不可知的异常，这时会触发由当前运行进程切换到处理此异常的内核相关程序中，也就转到了内核态，比如缺页异常。

3,外围设备的中断
当外围设备完成用户请求的操作后，会向CPU发出相应的中断信号，这时CPU会暂停当前操作转而去执行与中断信号对应的处理程序，如果先前执行的指令是用户态下的程序，那么这个转换的过程自然也就发生了由用户态到内核态的切换。
比如硬盘读写操作完成，系统会切换到硬盘读写的中断处理程序中执行后续操作等。

这3种方式是系统在运行时由用户态转到内核态的最主要方式,/其中系统调用可以认为是用户进程主动发起的，异常和外围设备中断则是被动的。/,
/简单的说，3种方式都是CPU响应了一个中断，从而完成切换，执行中断响应函数


//具体的切换操作
从触发方式上看，可以认为存在前述3种不同的类型,/但是从最终实际完成由用户态到内核态的切换操作上来说，涉及的关键步骤是完全一致的，没有任何区别，都相当于执行了一个中断响应的过程，因为系统调用实际上最终是中断机制实现的，而异常和中断的处理机制基本上也是一致的，关于它们的具体区别这里不再赘述。/关于中断处理机制的细节和步骤这里也不做过多分析，涉及到由用户态切换到内核态的步骤主要包括：

① 从当前进程的描述符中提取其内核栈的ss0及esp0信息。
② 使用ss0和esp0指向的内核栈将当前进程的cs,eip,eflags,ss,esp信息保存起来，这个过程也完成了由用户栈到内核栈的切换过程，同时保存了被暂停执行的程序的下一条指令。
③ 将先前由中断向量检索得到的中断处理程序的cs,eip信息装入相应的寄存器，开始执行中断处理程序，这时就转到了内核态的程序执行了。


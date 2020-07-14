

//5.C++并发编程 | CAS的基本原理剖析（无锁编程、无锁数据结构）

//关于volatile

C/C++ 语言中的volatile关键字作用


易变性：volatile告诉编译器,/某个变量是易变的，当编译器遇到这个变量的时候，只能从变量的内存地址中读取这个变量，不可以从缓存、寄存器、或者其它任何地方读取。


顺序性:/两个包含volatile变量的指令，编译后不可以乱序/。注意是编译后不乱序,/但是在执行的过程中还是可能会乱序的，这点需要由其它机制来保证，例如memory- barriers。

C/C++中的volatile并不是用来解决多线竞争问题的，而是用来修饰一些程序不可控因素导致变化的变量

,/C++11标准明确指出解决多线程的数据竞争问题应该使用 原子操作 或 互斥锁

//CAS的基本原理

高并发服务器经常用到多线程编程，需要对共享数据进行操作，为了保护数据的正确性，有一种有效的方法就是加锁机制，但这种方式存在以下一些缺点：

1,在多线程竞争下，加锁、释放锁会导致比较多的上下文切换和调度延时，引起性能问题
2,一个线程持有锁会导致其他所有需要此锁的线程挂起
3,如果一个优先级高的线程等待一个优先级低的线程释放锁会导致优先级倒置，引起性能风险

,/为了解决多线程并行情况下使用锁造成性能损耗的问题，我们引入了CAS(Compare and Swap)机制，这是一种原子操作，还有一种TS(test and set)指令也是原子操作

判断内存 reg 里的值是不是 oldval，如果是的话，则对其赋值newval。CAS机制如下：
bool compare_and_swap (int* reg, int oldval, int newval)//oldval newval也可以换成bool,
{
  if(*reg == oldval)
  {
  	 *reg = newval;//reg是指针，这句话是改变这个指针的指向，reg不是真实的区域
  	 return true;
  }
  return false;
}

CAS是一种有名的无锁算法;/无锁编程，即不使用锁的情况下实现多线程之间的变量同步，也就是在没有现成被阻塞的情况下实现变量的同步。

总结如下：
1,CAS（Compare And Swap）比较并替换，是线程并发运行时用到的一种技术
2,CAS是原子操作，保证并发安全，而不能保证并发同步
3,CAS是CPU的一个指令
4,CAS是非阻塞的、轻量级的乐观锁,/说CAS是无锁操作是因为CAS没有一个标识位，不需要线程去抢占这个标志位来访问公共资源，而是通过 原子操作 来实现这个功能

//原子操作
可以去看操作系统的pdf

,/使用原子操作模拟互斥锁的行为就是自旋锁,ts指令就是自旋锁

自旋锁（spinlock）：是指当一个线程在获取锁的时候，如果锁已经被其它线程获取，那么该线程将循环等待，当然也有将线程挂起，然后当前线程结束后再唤醒


//ABA问题
所谓ABA问题基本是这个样子：
	进程P1在共享变量中读到值为A
	P1被抢占了，进程P2执行
	P2把共享变量里的值从A改成了B，再改回到A，此时被P1抢占。
	P1回来看到共享变量里的值没有被改变，于是继续执行。
虽然P1以为变量值没有改变，继续执行了，但是这个会引发一些潜在的问题。

为解决ABA为题，我们可以采用 具有原子性的内存引用计数 等等办法。

//CAS与普通锁的区别
CAS：一般是系统底层的一套指令，作用就是同一时刻做这套指令的时候，其他相同的指令的线程不会干扰，保持原子性，常用于自旋锁。

Linux普通锁：同步代码块或者函数，当一个线程拿到锁后，其他线程等待，直到拿到锁的时候释放锁。

两者的时间差别就是:自旋的时间 和 线程上下文切换的时间,		

//CAS的优缺点
优点：在一般情况下，性能优先于锁的使用。
缺点：它将使调用者处理竞争问题（通过重试、回退、放弃），而在锁中能自动处理竞争问题。自旋时间过长，消耗CPU资源，如果资源竞争激烈，多线程自旋长时间消耗资源。


//基于CAS的无锁 并发队列 原理，无锁的意思是当需要改变队列的时候，不需要申请专门的锁，防止多个线程同时改变，通过原子操作，有且只有一个线程能在一个时刻改变队列
我们先来看一下进队列的CAS实现的方式(伪代码)：//CAS中有两个地址head和tail，head指向的是头结，tail=尾结点，要注意
	EnQueue(x) //进队列改良版
	{
		q = new record();
		q->value = x;
		q->next = NULL;  //新结点
	 
		p = tail;
		oldp = p
		do {
			while (p->next != NULL) //加这个循环的目的是：在尾结点加入q之前，别的线程已经成功加入了一个结点，那p->next就不为空了，那do循环就无限循环了，所以要保持p为尾结点
				p = p->next;
		} while( CAS(p->next, NULL, q) != TRUE);//把q的地址赋到p的next中，就是接上链表，
	 
		CAS(tail, oldp, q);//这里不需要判断，因为某个时刻只有一个线程通过了while循环，其他线程都没有通过，不存在执行该语句之前修改队列的情况，但是这为什么用oldp，存疑？
	}


就是说，很有可能在准备在队列尾加入结点时，别的线程已经加成功了，于是tail指针就变了，于是CAS返回了false，于是程序再试，直到试成功为止，即自旋操作。

为什么我们的“置尾结点”的操作不判断是否成功，因为：

1,如果有一个线程T1，它的while中的CAS如果成功的话，那么其它所有的 随后线程的CAS都会失败，然后就会再循环，
	此时，如果T1 线程还没有更新tail指针，其它的线程继续失败，因为tail->next不是NULL了。
2,直到T1线程更新完tail指针，于是其它的线程中的某个线程就可以得到新的tail指针，继续往下走了。


接下来我们再来看一下出队列的CAS实现：
	DeQueue() //出队列
	{
		do{
			p = head;
			if (p->next == NULL){
				return ERR_EMPTY_QUEUE; //队列为空的情况
			}
		while( CAS(head, p, p->next) != TRUE );  //把第二个结点
		return p->next->value;
	}


//解决ABA问题

在普通CAS的基础上加一个计数功能，如果改变了某个地址的值，针对该地址的计数加1，


//基于CAS实现无锁并发栈原理
基于链表的非阻塞堆栈实现
	template <typename T> 
	class Stack { 
		typedef struct Node { 
							  T data;
							  Node* next;
							  Node(const T& d) : data(d), next(0) { } 
							} Node;
		Node *top; 
		public: 
		   Stack( ) : top(0) { }
		   void push(const T& data);//压栈
		   T pop( ) throw (…); //出栈
	};

在非阻塞堆栈中压入数据
	void Stack<T>::push(const T& data) 
	{ 
		Node *n = new Node(data); 
		while (1) { 
			n->next = top->next; //top指向的是头结点的位置(注意：top!=头结点)，放入while循环的原因是top可能在其他线程改变
			if (__sync_bool_compare_and_swap(&top->next, n->next, n)) { // CAS
				break;
			}
		}
	}

从非阻塞堆栈弹出数据
T Stack<T>::pop( ) 
{ 
    while (1) { 
        Node* result = top;
        if (result == NULL) 
           throw std::string(“Cannot pop from empty stack”);      
        if (top && __sync_bool_compare_and_swap(&top, result, result->next)) { // CAS，top指向top->next
            return top->data;
        }
    }
}






//MySQL事务处理与锁机制详解


//MySQL事务处理
事务的基本概念
	事务 是数据库管理系统执行过程中的一个逻辑单位，由一个有限的数据库操作序列构成。
	
1,在 MySQL 中只有使用了 Innodb 数据库引擎的数据库或表才支持事务。
2,事务处理可以用来维护数据库的完整性
3,一个完整的业务需要批量的DML(insert、update、delete)语句共同联合完成
4,事务只和DML语句有关，或者说DML语句才有事务。


事务的ACID特性
	,/事务的ACID特性指的是事务的 原子性、一致性、隔离性和持久性。

1,原子性（Atomicity）
	原子性是指事务包含的所有操作要么全部成功，要么全部失败回滚，

2,一致性（Consistency）
	一致性是指事务必须使数据库从一个一致性状态变换到另一个一致性状态,/数据不一致问题有三种：脏读、不可重复读 和 幻读（虚读)。
	
3,隔离性（Isolation）
	多个并发事务之间要相互隔离。要使每个事务感觉不到其他事务在执行，,/关于事务的隔离性数据库提供了多种隔离级别：未提交读、已提交读、可重复读、串行化，

4,持久性（Durability）
	持久性是指一个事务一旦被提交了，那么对数据库中的数据的改变就是永久性的，即便是在数据库系统遇到故障的情况下也不会丢失提交事务的操作。


//数据不一致问题
1,	脏读
	,/脏读是指在一个事务处理过程里读取了另一个未提交的事务中的数据。
	当一个事务A正在修改数据，一共需要修改两条数据，修改了一条时，这时候另一个事务B读取了这个修改的数据；
	但是后面因为某种原因,事务A回滚了，这个时候事务B读到的数据其实在表中没有改变，这就是脏读

2,	不可重复读
	,/不可重复读是指在对于数据库中的某个数据，一个事务范围内多次查询却返回了不同的数据值，
	例如事务T1在读取某一数据后，而事务T2立马修改了这个数据并且提交事务给数据库，事务T1再次读取该数据就得到了不同的结果，发送了不可重复读。
	不可重复读和脏读的区别是:/脏读是某一事务读取了另一个事务未提交的脏数据，而不可重复读则是读取了前一事务提交的数据。
	有时候不可重复度不是错误。
	
3,	虚读(幻读)
	,/幻读是事务非独立执行时发生的一种现象。
	例如事务T1对一个表中所有的行的某个数据项做了从“1”修改为“2”的操作，这时事务T2又对这个表中插入了一行数据项，而这个数据项的数值还是为“1”并且提交给数据库。而操作事务T1的用户如果再查看刚刚修改的数据，会发现还有一行没有修改，其实这行是从事务T2中添加的，就好像产生幻觉一样，这就是发生了幻读;
	/幻读和不可重复读都是读取了另一条已经提交的事务（这点就和脏读不同），所不同的是不可重复读查询的都是同一个数据项，而幻读针对的是一批数据整体。


//事务的隔离级别
	针对可能的问题，InnoDB 提供了四种不同级别的机制保证数据隔离性：未提交读、已提交读、可重复读、串行化。级别由低到高
	Read uncommitted (未提交读)：最低级别，任何情况都无法保证。
	Read committed (已提交读)：可避免脏读的发生。
	Repeatable read (可重复读)：可避免脏读、不可重复读的发生,/在MySQL数据库中默认的隔离级别为Repeatable read (可重复读)。
	Serializable (串行化)：可避免脏读、不可重复读、幻读的发生。
	
	,/当然级别越高，执行效率就越低。
	像Serializable这样的级别，就是以锁表的方式，使得其他的线程只能在锁外等待，所以平时选用何种隔离级别应该根据实际情况。
	
注意：
	1,/设置数据库的隔离级别一定要是在开启事务之前
	2,隔离级别的设置只对当前链接有效。对于使用MySQL命令窗口而言，一个窗口就相当于一个链接，当前窗口设置的隔离级别只对当前窗口中的事务有效

//事务的提交与回滚
	提交：成功的结束，将所有的DML语句操作历史记录和内存数据进行同步
	回滚：失败的结束，将所有的DML语句操作历史记录全部清空  DML语言就是insert update delete

	在事务进行过程中，未结束之前，DML语句是不会更改底层数据，只是将历史操作记录一下，在内存中完成记录。
	只有在事物结束的时候，而且是成功的结束的时候，才会修改底层硬盘文件中的数据。
	
默认情况下，事务是自动提交的,但是，自动提交机制是可以关闭的。
	将自动提交功能置为ON：
	SET AUTOCOMMIT=0;
	将自动提交功能置为OFF：
	SET AUTOCOMMIT=1;
	
如果存储引擎为 InnoDB 时，当执行了START TRANSACTION或BEGIN命令后，将不会自动提交了，只有明确执行了COMMIT命令后才会被提交，在这之前可以执行ROLLBACK 命令回滚更新操作。

	,/事务的隔离性是通过锁机制实现的，MyISAM使用 表级别锁，InnoDB采用更细粒度的 行级别锁 ，提高了数据表的性能
	表锁就是对整个表上锁，行锁就是对表中的行上锁


//MySQL的锁机制
	锁是计算机协调多个进程或线程并发访问某一资源的机制。

Mysql用到了很多这种锁机制,/比如行锁，表锁，读锁，写锁等，都是在做操作之前先上锁。这些锁统称为悲观锁

MySQL的锁机制比较简单，其最显著的特点是不同的存储引擎支持不同的锁机制。比如：
	1,/MyISAM 和 MEMORY存储引擎采用的是表级锁（table-level locking）
	2,BDB存储引擎采用的是页面锁（page-level locking），但也支持表级锁
	3,/InnoDB存储引擎既支持行级锁（row-level locking），也支持表级锁，但默认情况下是采用行级锁。

这些锁的区别如下：
	表级锁：开销小，加锁快；不会出现死锁；锁定粒度大，发生锁冲突的概率最高，并发度最低。
	行级锁：开销大，加锁慢；会出现死锁；锁定粒度最小，发生锁冲突的概率最低，并发度也最高。
	页面锁：开销和加锁时间界于表锁和行锁之间；会出现死锁；锁定粒度界于表锁和行锁之间，并发度一般

表级锁更适合于以查询为主，只有少量按索引条件更新数据的应用，如Web应用
行级锁则更适合于有大量按索引条件并发更新少量不同数据，同时又有并发查询的应用，如一些在线事务处理（OLTP）系统

//MyISAM表锁
	表共享读锁（Table Read Lock）:消费者
	表独占写锁（Table Write Lock）:生产者

//MyISAM的锁调度
	MyISAM存储引擎的读锁和写锁是互斥的，读写操作是串行的。
	
	一个进程请求某个 MyISAM表的读锁，同时另一个进程也请求同一表的写锁，MySQL如何处理呢？
	答案是写进程先获得锁。,/不仅如此，即使 读请求 先到锁等待队列，写请求 后到，写锁也会插到读锁请求之前！
	这是因为MySQL认为写请求一般比读请求要重要。这也正是MyISAM表不太适合于有大量更新操作和查询操作应用的原因，
	因为,/大量的更新操作会造成查询操作很难获得读锁，从而可能永远阻塞。这种情况有时可能会变得非常糟糕！幸好我们可以通过一些设置来调节MyISAM 的调度行为。

	通过执行命令SET LOW_PRIORITY_UPDATES=1，使该连接发出的更新请求优先级降低。;
	/MySQL也提供了一种折中的办法来调节读写冲突，即给系统参数max_write_lock_count设置一个合适的值，当一个表的读锁达到这个值后，MySQL就暂时将写请求的优先级降低，给读进程一定获得锁的机会。

//InnoDB行锁
	InnoDB实现了以下两种类型的行锁。
	共享锁（读锁）:消费者
	排他锁（写锁）:生产者

	update,delete,insert都会自动给涉及到的数据加上排他锁，select 语句默认不会加任何锁类型
	
	加过排他锁的数据行在其他事务种是不能修改数据的，也不能通过for update（排它锁）和lock in share mode（共享锁）锁的方式查询数据，但可以直接通过select 查询数据,/因为普通查询没有任何锁机制。

另外，为了允许行锁和表锁共存，实现多粒度锁机制，InnoDB还有两种内部使用的意向锁（Intention Locks），这两种意向锁都是表锁。
	意向共享锁（IS）：事务打算给数据行共享锁，事务在给一个数据行加共享锁前必须先取得该表的IS锁。
	意向排他锁（IX）：事务打算给数据行加排他锁，事务在给一个数据行加排他锁前必须先取得该表的IX锁。

如果一个事务请求的锁模式与当前的锁兼容，InnoDB就请求的锁授予该事务；反之，如果两者两者不兼容，该事务就要等待锁释放。

//InnoDB行锁实现方式
InnoDB行锁是通过给索引上的索引项加锁来实现的

只有通过索引条件检索数据，InnoDB才使用行级锁，否则，InnoDB将使用表锁！

//间隙锁（Next-Key锁）
https://www.jianshu.com/p/32904ee07e56


//总结
对于MyISAM的表锁：

	1,共享读锁（S）之间是兼容的，但共享读锁（S）与排他写锁（X）之间，以及排他写锁（X）之间是互斥的，也就是说读和写是串行的。
	2,在一定条件下，MyISAM允许查询和插入并发执行，我们可以利用这一点来解决应用中对同一表查询和插入的锁争用问题。
	3,MyISAM默认的锁调度机制是写优先，这并不一定适合所有应用，用户可以通过设置LOW_PRIORITY_UPDATES参数，
		或在INSERT、UPDATE、DELETE语句中指定LOW_PRIORITY选项来调节读写锁的争用。
	4,由于表锁的锁定粒度大，读写之间又是串行的，因此，如果更新操作较多，MyISAM表可能会出现严重的锁等待，可以考虑采用InnoDB表来减少锁冲突。

对于InnoDB表：

	1,InnoDB的行锁是基于索引实现的，如果不通过索引访问数据，InnoDB会使用表锁。

	2,在了解InnoDB锁特性后，用户可以通过设计和SQL调整等措施减少锁冲突和死锁，包括：

		1,尽量使用较低的隔离级别；精心设计索引，并尽量使用索引访问数据，使加锁更精确，从而减少锁冲突的机会；
		2,选择合理的事务大小，小事务发生锁冲突的几率也更小；
		3,给记录集显式加锁时，最好一次性请求足够级别的锁。比如要修改数据的话，最好直接申请排他锁，而不是先申请共享锁，修改时再请求排他锁，这样容易产生死锁；
		4,不同的程序访问一组表时，应尽量约定以相同的顺序访问各表，对一个表而言，尽可能以固定的顺序存取表中的行。这样可以大大减少死锁的机会；
		5,尽量用相等条件访问数据，这样可以避免间隙锁对并发插入的影响； 不要申请超过实际需要的锁级别；除非必须，查询时不要显示加锁；
		6,对于一些特定的事务，可以使用表锁来提高处理速度或减少死锁的可能。



//全面解析MySQL日志

日志文件中记录着MySQL数据库运行期间发生的变化。	

二进制日志：以二进制文件的形式主要用于记录数据库的变化情况。但不记录查询语句;/可以根据二进制日志中的记录来修复数据库。
错误日志：记录MySQL服务器的启动、关闭和运行错误等信息。
通用查询日志：记录用户登录和记录查询的信息。记录查询语句;
慢查询日志：记录执行时间超过指定时间的操作。

除二进制日志外，其他日志都是文本文件。默认情况下，只有错误日志是打开的，其他三个都是关闭的

//二进制日志：

启动和设置二进制日志
	默认情况下，二进制日志功能是关闭的。
	将log_bin选项加入到 my.cnf 或者 my.ini 文件的［mysqld］组中形式如下：
		-- my.cnf （Linux操作系统下）或者 my.ini （Windows操作系统下）
		[mysqld]
		log-bin[=DIR \ [filename]]

	其中，DIR参数指定二进制文件的存储路径；filename参数指定二进制文件的文件名， 

查看二进制日志
	不能直接打开并查看二进制日志。必须使用mysqlbinlog命令。 mysqlbinlog 命令的语法形式如下：
	mysqlbinlog filename-number
	
删除二进制日志
	二进制日志会记录大量的信息。如果很长时间不清理二进制日志，将会浪费很多的磁盘空间。
	RESET MASTER

使用二进制日志还原数据库
	二进制日志记录了用户对数据库中数据的改变。如INSERT语句、UPDATE语句、 CREATE语句等都会记录到二进制日志中。一旦数据库遭到破坏，可以使用二进制日志来还原数据库。

	使用mysqlbinlog命令进行还原操作时，必须是编号（number）小的先还原。例如binlog.000001 必须在 binlog.000002之前还原。
	示例：下面使用二进制日志来还原数据库：
	mysqlbinlog binlog.000001 | mysql -u root -p 
	mysqlbinlog binlog.000002 | mysql -u root -p 
	mysqlbinlog binlog.000003 | mysql -u root -p 
	mysqlbinlog binlog.000004 | mysql -u root -p

暂时停止二进制日志功能
	SET SQL_LOG_BIN=0;//=1就是开启

//错误日志
错误日志是MySQL数据库中最常用的一种日志。错误日志主要用来记录MySQL服务的开启、关闭和错误信息。

启动和设置错误日志
	在MySQL数据库中，错误日志功能是默认开启的。而且，错误日志无法被禁止。
	my.cnf （Linux操作系统下）或者my.ini （Windows操作系统下）
		[mysqld]
		log-error[=DIR / [filename]

	其中，DIR参数指定错误日志的路径。filename参数是错误日志的名称，
	
查看错误日志
	错误日志中记录着开启和关闭MySQL服务的时间，以及服务运行过程中出现哪些异常等信息。

删除错误日志
	数据库管理员可以删除很长时间之前的错误日志，以保证MySQL服务器上的硬盘空间。
	mysqladmin -u root -p flush-logs

//通用查询日志
	通用查询日志是用来记录用户的所有操作，包括启动和关闭MySQL服务、更新语句 和 査询语句等。本节将为读者介绍通用查询日志的内容。
启动和设置通用查询日志
	-- my.cnf （Linux操作系统下〉或者my.ini （Windows搡作系统下）
	[mysqld]
	general-log[=DIR \ [filename]]

	其中，DIR参数指定通用查询日志的存储路径；filename参数指定日志的文件名。如果不指定存储路径，通用査询日志将默认存储到MySQL数据库的数据文件夹下。如果不指定文件名，默认文件名为hostname.log。hostname是MySQL服务器的主机名。

//删除通用查询日志
	通用查询日志会记录用户的所有操作。如果数据库的使用非常频繁，那么通用查询日志将会占用非常大的磁盘空间。
	mysqladmin -u root -p flush-logs

//慢查询日志
	慢查询日志是用来记录执行时间超过指定时间的查询语句。通过慢查询日志，可以查 找出哪些查询语句的执行效率很低，以便进行优化。

启动
	# my.cnf （Linux操作系统下）或者my.ini （Windows操作系统下）
	[mysqld]
	slow-query-log = 1
	slow_query_log_file="xxx.log"
	long_query_time=n

删除慢查询日志
	mysqladmin -u root -p flush-logs
	注意：通用查询日志和慢查询日志都是使用这个命令，使用时一定要注意。一旦执行这个命令，通用查询日志和慢查询日志都只存在新的日志文件中。如果希望备份旧的慢查询日志，必须先将旧的日志文件复制出来或者改名。然后，再执行上面的 mysqladmin 命令。


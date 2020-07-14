


//MySQL多表联合查询（一）理论基础：外键、操作关联表




1,什么是外键
外键是指引用另一个表的一列或多列，被引用的列应该具有主键约束或唯一性约束。外键用于建立和加强两个表数据之间的连接，


例:
CREATE DATABASE test;

use test;

CREATE TABLE grade(id int(4) NOT NULL PRIMARY KEY,
                  name varchar(36));

CREATE TABLE student(sid int(4) NOT NULL PRIMARY KEY,
                  sname varchar(36),
                  gid int(4) NOT NULL );

其中表student中的gid就是grade中的主键,/被引用的表，即班级表(grade)是主表；引用外键的表，即学生表(student)是从表，两个表是主从关系。

引入外键后，外键列只能插入参照列的值，参照列被参照的值不能被删除，这就保证了数据的参照完整性。

2,为表添加外键约束

alter table student add constraint FK_ID foreign key(gid) REFERENCES grade(id);

为表添加外键约束时，有些地方需要注意:

	1,建立外键约束的表的存储引擎必须是InnoDB，不能是临时表。因为在MySQL中只有InnoDB类型的表才支持外键。
	2,定义外键名时，不能加引号，如constraint ‘FK_ID’ 或 constraint "FK_ID"都是错误的。
	
另外MySQL可以在建立外键时添加 ON DELETE 或 ON UPDATE 子句告诉数据库，避免产生垃圾数据：

alter table 表名 add constraint FK_ID 
foreign key(外键字段名) REFERENCES 外表表名(主键字段名);
[ON DELETE {CASCADE | SET NULL | NO ACTION | RESTRICT}]
[ON UPDATE {CASCADE | SET NULL | NO ACTION | RESTRICT}]

参数的具体含义如下：

	参数名称		功能描述
	CASCADE			删除包含与已删除键值有参照关系的所有记录
	SET NULL		删除包含与已删除键值有参照关系的所有记录，使用NULL值替换(不能用于设置NOT NULL的字段)
	NO ACTION		不进行任何操作
	RESTRICT		拒绝主表删除或修改外键关联列(在不定义上述两个子句时，这是默认设置，也是最安全的设置)


3,删除外键约束
alter table student drop foreign key FK_ID;


4,操作关联表
表之间的关联关系有三种：
	多对一
	多对多
	一对一
	
多对一
	表之间的关系是通过外键建立的。在多对一的表关系中，应该将外键建在多的一方，否则会造成数据的冗余。

多对多
	为了实现这种关系需要定义一张中间表（称为连接表），该表会存在两个外键，连接表的两个外键都是可以重复的，但是两个外键之间的关系是不能重复的，所以这两个外键又是连接表的联合主键。

—对一：
	分清主从关系。从表需要主表的存在才有意义，注意：被引用的主表
	

此时表student和表grade之间是多对一的关系。因为外键列只能插入参照列已存在的值，所以我们先向主表grade添加数据：

INSERT INTO grade(id, name) VALUES(1,'软件一班'),
									(2,'软件2班');
在上述语句中，添加的主键id为1和2，由于student表的外键与grade表的主键关联，因此向student中添加数据时，gid的值只能是1或2，不能使用其他的值：

INSERT INTO student(sid, sname, gid) VALUES(1,'王红',1),
											(2,'李强',1),
											(3,'赵四',2),
											(4,'郝娟',2);

上述语句执行成功后，两个表之间的数据就具有关联性。

假如要查询软件一般有哪些学生，首先需要查询出班级名称为 “软件一班” 的id：

SELECT id FROM grade WHERE name='软件一班';

然后在student表中，查询 gid = 1 的学生，即为软件一班的学生：

SELECT name FROM student WHERE gid=1;


5,删除数据
,/在两个具有关联关系的表中删除数据时，一定要先删除从表的数据，然后再删除主表中的数据，否则会报错。在主表没有从表参照之后就可以删除主表中的数了

注意：在实际情况中，我们想要删除"软件一班"，并不需要删除"软件一班"的学生，可以将表student中的软件一班学生的gid改为NULL，只要主表中该列没有被从表参照就可以删除。
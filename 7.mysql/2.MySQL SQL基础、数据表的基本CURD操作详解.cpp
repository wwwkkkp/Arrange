

//MySQL SQL基础、数据表的基本CURD操作详解


//SQL基础：语句结构、数据类型与运算符
结构化查询语言(Structured Query Language)简称SQL，是一种特殊目的的编程语言，是一种数据库查询和程序设计语言，用于存取数据以及查询、更新和管理关系数据库系统

语句结构：
结构化查询语言包含6个部分：
1,数据查询语言（DQL:Data Query Language）;
	/保留字SELECT是DQL（也是所有SQL）用得最多的动词，
	其他DQL常用的保留字有WHERE，ORDER BY，GROUP BY和HAVING。这些DQL保留字常与其他类型的SQL语句一起使用。
2,数据操作语言（DML：Data Manipulation Language）;
	/其语句包括动词INSERT，UPDATE和DELETE。
	它们分别用于添加，修改和删除表中的行。也称为动作查询语言。
3,事务处理语言（TPL）;
	/它的语句能确保被DML语句影响的表的所有行及时得以更新。
	TPL语句包括BEGIN TRANSACTION，COMMIT和ROLLBACK。
4,数据控制语言（DCL）;
	/它的语句通过GRANT或REVOKE获得许可，确定单个用户和用户组对数据库对象的访问。就是权限管理
	某些RDBMS可用GRANT或REVOKE控制对表单个列的访问。
5,数据定义语言（DDL）;
	/其语句包括动词CREATE和DROP。
	在数据库中创建新表或删除表（CREATE TABLE 或 DROP TABLE）；	为表加入索引等。DDL包括许多与数据库目录中获得数据有关的保留字。它也是动作查询的一部分。
6,指针控制语言（CCL）
	它的语句，像DECLARE CURSOR，FETCH INTO和UPDATE WHERE CURRENT用于对一个或多个表单独行的操作。

数据类型
	整数类型
	浮点数类型
	定点数类型
	日期和时间类型
	字符串类型
	二进制类型。




//数据库的基本操作
见mysql中的总结

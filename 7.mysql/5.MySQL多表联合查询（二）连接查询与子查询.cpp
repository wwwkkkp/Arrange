

//MySQL多表联合查询（二）连接查询与子查询

1,交叉连接
,/交叉连接返回的结果是被连接的两个表中所有数据行的笛卡儿积，也就是返回第一个表中符合查询条件的数据行数乘以第二个表中符合查询条件的数据行数。

 SELECT * from 表1 CROSS JOIN 表2;
	如：满足条件的表1的元组有3个，满足条件的表2的元组有4个，那输出就是12个元组，


2,内连接
,/内连接(Inner Join)又称简单连接或自然连接，
在内连接査询中，只有满足条件的记录才能出现在查询结果中。
	SELECT employee.name, department.dname 
	FROM department
	JOIN employee
	ON employee.did=department.did;
上面的语句和下面的语句效果是一样的
	SELECT employee.name, department.dname 
	FROM department,employee
	WHERE employee.did=department.did;


,/如果在一个连接查询中，涉及的两个表是同一个表，这种查询称为自连接查询。
自连接是一种特殊的内连接，它是指相互连接的表在物理上为同一个表，但逻辑上分为两个表，

3,外连接
前面讲解的内连接查询中，返回的结果只包含符合查询条件和连接条件的数据，
,/然而有时还需要包含没有关联的数据，即返回查询结果中不仅包含符合条件的数据，而且还包括左表（左连接或左外连接）、右表（右连接或右外连接）或两个表（全外连接）中的所有数据，此时就需要使用外连接查询，外连接分为左连接和右连接。

外连接的语法格式和内连接类似，只不过使用的是LEFT JOIN 和 RIGHT JOIN 关键字,/其中关键字左边的表被称为左表，关键字右边的表被称为右表。

在使用左连接和右连接查询时，查询结果是不一致的，具体如下。
	1,LEFT JOIN（左连接）：返回包括左表中的所有记录和右表中符合连接条件的记录。
	2,RIGHT JOIN（右连接）：返回包括右表中的所有记录和左表中符合连接条件的记录。

左连接：
	SELECT department.did,department.dname,employee.name 
	FROM department
	LEFT JOIN employee
	ON department.did=employee.did;

	返回 department中所有类型的数，以及employee中符合department.did=employee.did的列，如果department中有的项在employee中没有对应的，那就用null代替

右连接：
	SELECT department.did,department.dname,employee.name 
	FROM department
	RIGHT JOIN employee 
	ON department.did=employee.did;
	
	返回 employee 中所有类型的数，以及department中符合 department.did=employee.did的列，如果employee中有的项在department中没有对应的，那就用null代替
		
	具体例子见：https://zhaoyang.blog.csdn.net/article/details/90345332

4,复合条件连接查询
复合条件连接查询就是在连接查询的过程中，通过添加过滤条件来限制查询结果，使得查询结果更加精确。


5,子查询
子查询是指一个查询语句嵌套在另一个查询语句内部的查询

//子查询
1,带IN关键字的子查询
,/使用IN关键字进行子查询时，内层查询语句仅返回一个数据列（产生一个临时表存储），这个数据列中的值将供外层查询语句进行比较操作。

查询存在年龄为20的员工的部门：
	SELECT * FROM department WHERE did 
	IN (SELECT did FROM employee WHERE age=20);

2,带EXISTS关键字的子查询
EXISTS关键字后面的参数可以使任意一个子查询，这个子查询的作用相当于测试，它不产生任何数据，只返回TURER或FALSE，当返回值为TRUE时，外层查询才会执行。
	SELECT * FROM department
	WHERE EXISTS(SELECT * FROM employee WHERE age>21); //只有当()中有数的时候，才能执行()外面的数

注意：EXISTS关键字比IN关键字的运行效率高，因为EXISTS关键字不会存储子查询的结果，只会返回TRUE 或FALSE，而IN关键字要暂存子查询结果，会产生临时表。所以在实际开发中，特别是数据量大时，推荐使用EXISTS关键字。


3,带ANY关键字的子查询
ANY关键字表示满足其中任意一个条件，它允许创建一个表达式对子查询的返回值列表进行比较，只要满足内层子查询中的任意一个比较条件，就返回一个结果作为外层查询条件。

使用带ANY关键字的子查询，查询满足条件的部门：
SELECT * FROM department WHERE did > any(SELECT did FROM employee);
//这句话的意思就是显示department中的did列中的数，只要大于任何一个 employee中did列的数，就是符合条件的查询结果。

4,带ALL关键字的子查询
ALL关键字与ANY关键字有点类似，带ALL关键字的子查询返回的结果需要同时满足所有的内层查询条件。
SELECT * FROM department WHERE did > ALL(SELECT did FROM employee);



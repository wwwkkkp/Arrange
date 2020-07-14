

学生表

学生编号   学生姓名	出生年月  学生性别




课程表

课程编号   课程名称		教师编号



教师表

教师编号	教师姓名	




成绩表

学生编号	课程编号	分数



select sdid,avg(成绩)as count from score name from student where score.id=student.id having count>60

select a.score,b.name from score a join student b on a.id=b.id join score c on a.id='01'and c.id='02' having a.score>c.score

select a.kid,COUNT(a.id) AS number FROM score a;

select a.name,AVG(b.score)as sc from kc a join cj b on a.id=b.id group by  AVG(b.score) desc 

select a.id,a.name AVG(b.score) AS sc FROM Sd a JOIN Score b on a.id=b.id having AVG(b.score)>85

selcet 


having 和 where 的区别，where是约束语句，having 是过滤语句，区别就是having可以用聚合函数（AVG,SUM）,但是where不可以用聚合函数

group by 和 order by的区别
group by是用在分组上，比如将编号相同的放在一起，注意，这里是不涉及排序的，不过他是默认从小到大分组

order by 用在排序上，对表进行排序，默认是升序，后面加了DESC就变成降序
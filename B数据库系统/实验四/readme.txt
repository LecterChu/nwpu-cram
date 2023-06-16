数据库系统实验四_ER映射
所属章节：第4章
发布时间：2020-05-23 12:04:01
最晚交作业时间：2020-05-29 23:59
要求：
使用课件中提供的ER映射算法，将ER模型转换为相应的关系模型。按照以下符号约定完成本练习
●	PK ： Primary Key
●	AK ： Alternate Key
●	FK ： Foreign key
要求按照以下格式书写，并详细写出映射的每步操作。
EMP(SSN, Name, DriverLicenseNo, DeptNo);
PK (SSN)
AK (DriverLicenseNo)
FK (DeptNo) -> Dept(DNo)
将以上题目答案书写在名为relational-schema.txt的文本文档中。
书写SQL语句，完成你以上映射产生的所有关系的创建工作。注意，要标识出所有关系的关键字、外键约束等等。将SQL语句保存在relational-model.sql文件中提交。
提交文件：
1.	relational-schema.txt 
2.	relational-model.sql 


附件：
1. exec4.doc
2. SSD7EXER.doc
3. mapping.txt

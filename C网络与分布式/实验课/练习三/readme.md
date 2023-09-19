# EXEC3-RMI

#### 理解：本次实验中的命令分为两类：

#### 	①第一类时在启动RMIClient时使用的完整命令，也即exec3说明文档中给出的有详细说明的几种命令，这些命令有三个作用：连接Server、设置当前Client的User(即launchUser)、执行一条命令；

#### 	②第二类是在启动了Client之后使用的简化版的命令，其中省去了servername、portnumber、username、password四个值，原因是在启动Client时已经由第一类命令设置过连接和当前User



## 1.编译文件并运行RMIServer

![编译以及运行服务器](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\编译以及运行服务器.png)



## 2.设置两个User CYF和CYF2![CYF](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\CYF.png)

![CYF2](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\CYF2.png)



## 3.在register的基础上使用简化的add命令和query命令

![CYF创建会议-含特殊情况](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\CYF创建会议-含特殊情况.png)

##### *几种不能创建的情况：没有其他用户不能创建、其他用户中有不存在的用户不能创建、其他用户中包含创建者自身不能创建，如上图所示*



## 4.使用add创建（以及使用query时的时间问题）

![创建会议的时间上的特殊情况](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\创建会议的时间上的特殊情况.png)

##### *add与query命令执行时要检查时间的正确性：月份数字、日期数字、小时以及分钟是否在合理的范围内（分钟不能出现60 小时不能出现24——24时应该表示成0时）同时在这里一个会议的结束时间等于另一个会议的开始时间时，另一个会议不能被创建，此外还判断了会议起止时间不能颠倒等等。*



## 5.delete命令

![delete](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\delete.png)



## 6.clear命令

![clear](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\clear.png)



## 7.help命令

![help](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\help.png)



## 8.quit命令

![quit](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\quit.png)



## 9.完整的delete——也即启动时的delete命令

![启动时的delete](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\启动时的delete.png)



## 10.完整的query——也即启动时的query

![启动时的query](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\启动时的query.png)



## 11.完整的clear——也即启动时的clear

![启动时的clear-1](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\启动时的clear-1.png)

![启动时的clear-2](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\启动时的clear-2.png)



## 12.完整的add——也即启动时的add

![启动时的add](C:\Users\YiFei-Chu\Desktop\作业\大三上作业\网络与分布式\实验课\练习三\images\启动时的add.png)
# 网络与分布式实验四

#### 环境：IDEA + JDK1.8

#### 一、先写好Server端的代码，然后运行以下指令生成代码和编译好的文件

![image-20221111172249346](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111172249346.png)

![image-20221111172400998](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111172400998.png)

*生成在com.list里*

#### 二、将com.list里的文件放到Client端

![image-20221111172517947](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111172517947.png)

#### 三、功能验证

##### ①先启动服务器，再启动客户端：

​	**Server：**

![image-20221111172602303](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111172602303.png)

​	**Client:**

![image-20221111172631730](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111172631730.png)

*客户端用数字1-7区分各种操作，输入时先输入对应的数字，客户端收到数字以后会给出相应的操作提示*

##### ②用户注册：

![image-20221111172829304](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111172829304.png)

![image-20221111172834915](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111172834915.png)

![image-20221111172921933](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111172921933.png)

​	*重复的用户名不能重复注册*

##### ③添加项目：

![image-20221111173334972](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111173334972.png)

![image-20221111173342522](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111173342522.png)

##### ④查询项目：

![image-20221111173649195](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111173649195.png)

​	*为CYF添加两个项目*

![image-20221111173718710](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111173718710.png)

![image-20221111173754630](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111173754630.png)

​	*查询CYF的项目*

![image-20221111173918667](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111173918667.png)

*查询已注册但没有添加项目的用户时（用户默认有一个待办事项列表）不会返回任何信息*

##### ⑤删除项目

![image-20221111174052121](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111174052121.png)

​	*删除存在的项目*

![image-20221111174130025](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111174130025.png)

​	*删除不存在的项目提示“参数错误”（重复删除ID为1的项目）*

##### ⑥清空项目

![image-20221111174356007](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111174356007.png)

​	*先为CYF再创建一个项目*

![image-20221111174652759](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111174652759.png)

​	*清除项目*

![image-20221111174737339](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111174737339.png)

​	*可以看到所有项目都已经没有了*

##### ⑦帮助菜单

![image-20221111174820472](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111174820472.png)

##### ⑧退出

![image-20221111174902710](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111174902710.png)

​	*当输入不是1-7的信息时会提示参数错误*：

![image-20221111174934658](C:\Users\YiFei-Chu\AppData\Roaming\Typora\typora-user-images\image-20221111174934658.png)








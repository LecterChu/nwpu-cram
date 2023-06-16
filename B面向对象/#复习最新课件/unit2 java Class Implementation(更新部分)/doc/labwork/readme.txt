   加入现将文件夹labwork放在e(其它)盘根目录下：

 1.假设jdk装在e盘跟目录下，java命令(即java,javac等可执行文件)
   的执行需设置环境变量path

  两种方法：  
   方法一：我的电脑-属性—高级-系统变量path中添加：    
                        E:\jdk1.5.0\bin;
  
   方法二：set path=E:\jdk1.5.0\bin;%path%
          注：仅对当前的dos窗口生效

  
 2.执行命令  java -version
  可以查看安装的jdk版本信息

 3.java 虚拟机执行.class文件时，首先要找到该.class文件，
   它是如何寻找.class文件的？
  
   4.1   java虚拟机找出环境变量CLASSPATH;
       
         CLASSPATH包含一个或多个目录，
         每个目录被视为.class文件的查找起点。

   4.2   如果没有CLASSPATH这个环境变量，就默认CLASSPATH=.  
         
         意思是查找起点为当前的工作目录

 5. 假设改变当前的工作目录为 cd E:\labwork\
 
  编译、执行当前工作目录下的文件：
 
  javac ArraySize.java

  java  ArraySize
 
 6. 将5.中的当前工作目录改变到其它的目录；如 cd c:，
    此时当前的工作目录为C:,若要编译、执行非当前工作目录           E:\labwork\下的文件，则需要执行如下命令：

     javac E:\labwork\ArraySize.java

     java  E:\labwork\ArraySize

     如果想执行非当前工作目录下的类，还有以下两种方法6.1,6.2

   6.1 设置CLASSPATH环境变量：

        如果没有CLASSPATH这个环境变量，就默认CLASSPATH=.
        如果有CLASSPATH这个环境变量，就不再有默认值CLASSPATH=.
        如果想让任一目录成为其中一个查找类的起点，就需
        在CLASSPATH中添加相应的工作目录.  
     
     设置CLASSPATH环境变量的方法有两种：例如下例是将目录          E:\labwork\和当前工作目录.作为类的查找起点。     

     方法一：
     我的电脑-属性—高级-环境变量-
     用户变量（在其编辑框内添加变量CLASSPATH=E:\labwork\;.）
     
     方法二：
     set CLASSPATH=E:\labwork\;.
     仅对当前的DOS窗口生效     
    
     现执行命令：

     javac E:\labwork\ArraySize.java

     java  ArraySize     


   6.2  也可以不设环境变量，通过使用下述命令来解决问题 
       
       java -cp 寻找class的目录要执行的.class文件
  
 
      现执行命令：

        javac E:\labwork\ArraySize.java

        java  -cp E:\labwork ArraySize     

   7.在上述条件下执行命令：
      e: 
      cd E:\labwork\    

     javac ICarnegieInfoDemo.java

     java ICarnegieInfoDemo

    此例与上述例子的不同之处在于：
    一个类ICarnegieInfoDemo使用了另一个类ICarnegieInfo的
    实例，即创建类ICarnegieInfo的对象。
    
    8.在上述条件下执行命令：c:

      
     现如何编译执行E:\labwork\ICarnegieInfoDemo.java ？
     
     javac  E:\labwork\ICarnegieInfoDemo.java     
    
     在编译ICarnegieInfoDemo.java的时候，需要查找类ICarnegieInfo
     出现了问题，解决办法：
     
     8.1  设置类路径  classpath=E:\labwork\;.
    
      javac  E:\labwork\ICarnegieInfoDemo.java
      java   ICarnegieInfoDemo
  
     8.2  或者不设置类路径，也可以通过如下命令

      javac -classpath E:\labwork\   E:\labwork\ICarnegieInfoDemo.java

      java -cp E:\labwork\  ICarnegieInfoDemo

    9.  执行命令
      e:
      cd e:\labwork\  
      
     java会从CLASSPATH中的起点开始，并将package名称中的每个句号替换为斜线，
    
     javac LibTest.java

     java  LibTest

   10. 改变工作目录  
   
      c:
      javac E:\labwork\LibTest.java
    
      有问题，解决办法
     
     10.1  设置类路径  classpath=E:\labwork\;.
    
      javac  E:\labwork\LibTest.java
      java   LibTest
  
     10.2  或者不设置类路径，也可以通过如下命令

      javac -classpath E:\labwork\  E:\labwork\LibTest.java

      java -cp E:\labwork\  LibTest







编译并生成包
在当前目录下生成包
 javac –d . Test.java 
在指定目录下生成包
 javac –d E:\unit1 Test.java 

使用jar文件：
压缩： jar -cf 新的jar文档   压缩的目录
       jar -cvf 新的jar文档   压缩的目录
解压：jar -xfv

查看jar文件所包含的内容：
      jar -tf jar文档
          -tvf 更详细的内容
          

## 常用dos命令
</br>dir:列出当下目录下的文件以及文件夹
</br>md:创建目录
</br>rd:删除目录
</br>cd:进入指定目录
</br>cd..&nbsp;:退回到上一级目录
</br>cd\ :退回到根目录
</br>del：删除文件
</br>exit:退出dos命令行

---
## java技术体系平台（过去主要应用）
</br> **Jave SE**
</br> 支持面向<span style="color:pink">桌面级应用</span>的java平台
</br> **Java EE**
</br> 为企业开发环境下的应用程序提供的一套解决方案，包含技术：Servlet,Jsp等，主要针对<span style="color:pink">web开发</span>。
</br> **Java ME**
</br> <span style="color:pink">移动端</span>开发
</br> **Java Card**
</br> 小程序开发

---
### java语言的特点：跨平台性
</br> JVM：<span style="color:pink">java虚拟机</span>对应win，mac，linux三种不同的版本

---
## java核心机制：垃圾回收
</br>

### 垃圾回收：不再使用内存空间应回收
#### &emsp;在c/c++等语言中，由程序员负责回收无用内存</br>
&emsp;java语言提供了一种系统级线程跟踪存储空间的分配情况，并在JVM空闲时，释放空间。（垃圾回收自动进行）

---
## java语言的环境搭建
### </br> 1.下载安装jdk
### </br> 2.配置环境变量
### </br> 3.验证是否成功
### </br> 4.选择合适的文本编辑器或IDE开发
### </br> <span style="color:pink">jdk=jre+开发工具集</span>
### </br> <span style="color:pink">jre=jvm+java SE标准类库</span>
---
注：.java后缀为源文件 &emsp;.class后缀为字节码文件
</br>编译解释源文件:1.首先进入源文件的目录
</br>&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;2.若源代码文件名为HelloWorld.java，输入以下语句进行编译
``` markdown
javac HelloWorld.java
``` 
</br>&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;3.生成字节码文件，<span style="color:pink">其中名字自动变为其中的类名</span>。
</br>&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;4.若字节码文件为HelloChina.class，则输入以下语句进行解释
``` markdown
java HelloChina
``` 
#### 最简单的输出语句：

``` java
System.out.printin("Hello World!");
``` 
---
## IDEA
#### IDEA使用文档：https://www.jetbrains.com/help/idea/configuring-code-style.html
</br>IDEA官方插件库：https://plugins.jetbrains.com/idea
</br>注：代码都写在工程项目的src目录下
#### IDEA模块使用

---
java的三种注释：单行注释(//)，多行注释（*/ ... */），文档注释(java特有)

文档注释格式：/** </br>&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;@author 指定java程序的作者</br>&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;@version 指定源文件的版本</br>&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;*/

<span style="color:pink">文档注释的内容可以被JDK提供的工具javadoc解析，生成一套以**网页文件（html）**形式体现的该程序的说明文档</span>
</br></br>操作方式(若生成文档名为myHello，文件名为HelloJava.java)：

``` markdown
javadoc -d myHello -author -version HelloJava.java
```
---
### Java API
#### API(应用程序编程接口)是java提供的基本编程接口。
#### 下载API：https://www.oracle.com/technetwork/java/javase/downloads/index.html
</br> 注：在一个java源文件中可以声明多个class，但是最多只有一个类声明为public的。<span style="color:pink">而且要求声明为public的类的类名必须与源文件相同。</span>
</br>编译的过程会产生一个或多个字节码文件，<span style="color:pink">字节码文件的文件名与java源文件的类名相同</span>
</br>输出语句
``` java
System.out.println("Hello World!");  //输出数据后自动换行
System.out.print("Hello World!"); 
System.out.println();                //换行
```
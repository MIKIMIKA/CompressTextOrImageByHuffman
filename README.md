# CompressTextOrImageByHuffman
哈夫曼编码压缩文本和图片数据结构课程设计     

# 需求分析及相关注意事项       

## 设计内容和要求   

* 设计内容    
 * 运用哈夫曼编码的相关知识对任意文本文件进行编码、解码。
 * 运用哈夫曼编码的相关知识对bmp(24位位图)格式图片进行压缩、解压缩。(扩展功能)    

* 设计要求   
 * 根据要编码的文件中字符出现的频率生成对应的哈夫曼编码；
 * 得到采用哈夫曼编码后的目标文件，并保存；
 * 根据要解码的文件对应的哈夫曼码表对文件进行解码；
 * 得到解码后的目标文件并保存。



## 所需知识     

* 最优二叉树(哈夫曼树)构建
* 生成哈夫曼编码        
* 文件读取写入保存     
* QTGUI用户界面UI设计及逻辑处理        
* MVC架构      


## 所需数据结构     

* 哈夫曼二叉树    
  压缩数据
* 循环队列    
  构建最优二叉树时使用      

```c
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*定义结构体*/
/*包括结点类型结构体，采取顺序结构存储*/
/*包括循环队列，构建最优二叉树时使用*/

#define MAXSIZE 100
#define PIXELSIZE 256 //像素最大值

typedef unsigned char DataType; //字符类型
typedef unsigned int WeightType; //权值类型

typedef struct {
	DataType data; //每个结点存放的数据
	WeightType weight; //每个结点的权值
	int parent, l_child, r_child; //结点双亲，左右孩子的指针
} TreeNode;

typedef struct {
	int front;
	int rear;
	int tag;
	char info[MAXSIZE];
	DataType length;
} MyQueue;

```   

整体采用顺序结构存储        

## 所需算法    

* 哈夫曼树构建算法    
* 哈夫曼编码算法    
* 快速排序算法(数据权值排序)      

## 所需API    

* C/C++ IO    
  用于文件、图片数据的读取和保存   
* QT GUI Application     
  用于实现用户界面和交互设计    
* C 随机函数    
  随机生成测试用例        

## 团队开发版本控制    
使用GitHub进行代码同步    

## 代码命名规范及代码风格统一        

* 函数变量命名    
下划线分割含义：`int price_count_reader`      

* 类型命名    
类型名称的每个首字母均大写，不含下划线: `MyFirstClass`     

* 宏定义命名    
均大写：`#define MAX 100`     

* 注释风格    
使用`//`或`/**/`都可以    

* 大括号位置    
均换行放置      

```c++
if(a > 10)
{

}
```      

详情参考Google开源项目C++风格指南           
[GoogleC++风格指南](http://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/formatting/#id7)        


## 团队分工     

* 组长 鲍骞月：用户界面设计、结构体设计、项目主体模块搭建与连接及压缩图片模块实现    
* 组员 张泽亿：构建哈夫曼树算法设计及实现   
* 组员 董靖鑫：生成哈夫曼编码算法设计及实现   
* 组员 李萌：文件的读取和保存        

## 项目仓库地址   

`https://github.com/shentibeitaokongle/CompressTextOrImageByHuffman`

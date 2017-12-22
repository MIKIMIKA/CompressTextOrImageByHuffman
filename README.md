# CompressTextOrImageByHuffman
哈夫曼编码压缩文本和图片数据结构课程设计     

# 需求分析及相关注意事项        

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

* 组长：用户界面设计

#ifndef _Structure_H_
#define _Structure_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*定义结构体*/
/*包括结点类型结构体，采取顺序结构存储*/
/*包括循环队列，构建最优二叉树时使用*/
#define MAXSIZE 100
#define PIXELSIZE 256 //像素最大值

typedef unsigned char DataType; //字符类型
typedef unsigned long int WeightType; //权值类型

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

#endif 
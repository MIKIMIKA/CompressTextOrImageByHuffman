#ifndef _Structure_H_
#define _Structure_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*����ṹ��*/
/*����������ͽṹ�壬��ȡ˳��ṹ�洢*/
/*����ѭ�����У��������Ŷ�����ʱʹ��*/
#define MAXSIZE 100
#define PIXELSIZE 256 //�������ֵ

typedef unsigned char DataType; //�ַ�����
typedef unsigned long int WeightType; //Ȩֵ����

typedef struct {
	DataType data; //ÿ������ŵ�����
	WeightType weight; //ÿ������Ȩֵ
	int parent, l_child, r_child; //���˫�ף����Һ��ӵ�ָ��
} TreeNode;

typedef struct {
	int front;
	int rear;
	int tag;
	char info[MAXSIZE];
	DataType length;
} MyQueue;

#endif 
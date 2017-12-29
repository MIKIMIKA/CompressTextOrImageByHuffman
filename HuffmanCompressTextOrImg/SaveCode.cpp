#include "BaseHuffmanTree.h"
#include "Structure.h"
/*
下面是对已压缩编码的存储操作
*/


/*初始化循环队列*/
void init_cycle_queue(MyQueue *qu)
{
	if (!qu)
	{
		return;
	}
	else
	{	
		//如果qu不为空进行初始化
		qu->tag = 0;
		qu->front = 0;
		qu->rear = 0;
		qu->length = 0;
	}
	
}

/*
入队操作
将0，1字符进行入队操作
*/
void in_queue(MyQueue *qu, char ch)
{
	if (qu->front == qu->rear && qu->tag == 1)
	{
		return;
	}
	qu->info[qu->rear] = ch;
	qu->rear = (qu->rear + 1) % MAXSIZE;
	qu->length++;
	qu->tag = 1;
}

/*
出队操作
每次弹出一个0或1
*/
int out_queue(MyQueue *qu,char *ch)
{
	if (qu->tag == 0)
	{
		return NULL;
	}
	*ch = qu->info[qu->front];
	qu->length--;
	qu->front = (qu->front + 1) % MAXSIZE;
	if (qu->front == qu->rear)
		qu->tag = 0;
	return 1;
}

/*从队列中出队八个编码，并把他们组装成一个字节长的字符*/
DataType get_byte(MyQueue *queue)
{
	DataType byte = 0;
	int i;
	char ch;
	printf("%c", byte);
	for (i = 0; i < 8; i++) //出队八个编码
	{
		if (out_queue(queue,&ch) != 0)
		{
			if (ch == '0')
			{
				byte = byte << 1; //如果编码为0，直接左移一位补零
			}
			else
			{
				byte = (byte << 1) | 1; //如果编码为1，左移一位后或上1，将当前位变成1
			}
		}
		else
		{
			break;
		}
	}
	return byte;
}


/*
将生成的编码保存到文件中,并返回存放的字节个数
为了达到压缩的目的，这里将每八个编码转换成一个字节
存储到文件中
*/
int copy_huffman_code_to_file(FILE *fp, char **map, int leaf_num, MyQueue *queue, int *length)
{
	char *t;
	DataType byte;
	int i, j, num = 0; //最后要返回的字节个数
	for (i = 0; i < leaf_num; i++) //将n个叶子结点的编码写入文件中
	{
		for (t = map[i]; *t != '\0'; t++) //将每个叶子结点的编码都入队
		{
			in_queue(queue, *t);
		}
		//下面进行编码组合
		while (queue->length > 8) //每八位组成一个字节，所以这里根据队列元素长度控制循环
		{
			byte = get_byte(queue);//出队八位编码	
			fputc(byte, fp);//将组合好的一个字符写入文件中
			num++; //统计重新组合好的字节数
		}

	}
	//处理特殊情况，当队列中剩余的字符数不足8时，我们要对剩余的字符进行单个的组装
	*length = queue->length;
	i = 8 - *length;//剩余的不足八位的个数
	byte = get_byte(queue);//先将这几位组合,为了合成一个字节，对剩下的几位进行补零
	for (j = 0; j < i; j++)
	{
		byte = byte >> 1;
	}
	fputc(byte, fp);//将最后一个字节写入文件中
	num++;
	init_cycle_queue(queue);
	fclose(fp);
	return num;
}
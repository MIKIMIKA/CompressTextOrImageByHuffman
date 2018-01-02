#include "Structure.h"
#include "BaseHuffmanTree.h"


/*
解压缩
*/
void un_compress()
{
	DataType max_len, min_len, end_len = 0,final = 0;
	WeightType src_len = 0, new_file_len = 0;
	FILE *src, *res;
	int i,j,leaf_num, code_num;
	char ch, a, *temp_code, *src_name, *res_name, **map, *leaf_data_list, *code_len_list, *code_buf;
	MyQueue *qu = NULL;

	src_name = "D://resultfile.bmp.huf";
	res_name = "D://upzip.bmp"; //解压后的文件
	
	src = fopen(src_name, "rb");
	res = fopen(res_name, "wb");
	if (!src || !res)
	{
		printf("文件打开失败\n");
		return;
	}

	fread(&src_len, sizeof(WeightType), 1, src); //读取压缩文件字节数
	fread(&end_len, sizeof(DataType), 1, src); //读取最后剩余的位数，需要特殊处理
	fread(&leaf_num, sizeof(int), 1, src); //读取叶子数
	fread(&max_len, sizeof(DataType), 1, src); //读取编码长度最大值
	fread(&min_len, sizeof(DataType), 1, src); //读取编码长度最小值

	//申请空间
	code_buf = (char *)malloc(max_len * sizeof(char) + 2); //加上两个结尾符'\0'的长度
	leaf_data_list = (char *)malloc(leaf_num * sizeof(DataType)); //开辟存放叶子的数组
	code_len_list = (char *)malloc(leaf_num * sizeof(DataType)); //开辟存放每个叶子对应编码的长度数组
	qu = (MyQueue *)malloc(sizeof(MyQueue));
	
	if (!leaf_data_list || !code_len_list || !qu || !code_buf)
	{
		printf("开辟空间失败...");
		return;
	}
	
	fread(&code_num, sizeof(int), 1, src); //读取压缩编码后的字节数
	fread(&final, sizeof(DataType), 1, src); //读取剩余位数
	
	//读取叶子和对应编码长度
	for (i = 0; i < leaf_num; i++)
	{
		fread(&leaf_data_list[i], sizeof(DataType), 1, src);
		fread(&code_len_list[i], sizeof(DataType), 1, src);
	}
	init_cycle_queue(qu);
	map = (char **)malloc(sizeof(char *) * leaf_num); //重构编码表
	if (!map)
		return;
	--code_num;
	for (i = j = 0; i < code_num; i++) 
	{
		ch = fgetc(src);
		//将读取到的字符转成八位0，1字符入队
		cast_in_queue(qu, ch);
		while (qu->length > max_len) 
		{
			map[j] = temp_code = (char *)malloc(code_len_list[j] + 1);//开辟解码结果放置数组
			for (ch = 0; ch < code_len_list[j]; ch++) //出队该叶子的编码
			{
				out_queue(qu, &a); //将队首元素出队，赋值给a
				*temp_code++ = a;
			}
			*temp_code = '\0';
			j++;
		}
	}
	//处理最后一个字节
	ch = fgetc(src);
	cast_in_queue(qu, ch);
	//因为8 - final是补0的几位，所以需要特殊处理
	final = 8 - final;
	while (qu->length > final)
	{
		map[j] = temp_code = (char *)malloc(code_len_list[j] + 1);
		for (ch = 0; ch < code_len_list[j]; ch++)
		{
			out_queue(qu, &a);
			*temp_code++ = a;
		}
		*temp_code = '\0';
		j++;
	}

	//重置队列
	init_cycle_queue(qu);
	--src_len;
	--min_len;
	//解压
	while (new_file_len < src_len)
	{
		ch = fgetc(src); //从第二次写入的字节中选取字符
		cast_in_queue(qu, ch); //转换并入队编码
		new_file_len++;
		
		//在min_len~max_len的范围内进行编码的匹配和获取
		while (qu->length > max_len)
		{
			for (i = 0; i < min_len; i++)
			{
				out_queue(qu, &a);
				code_buf[i] = a;
			}
			for (; i < max_len; i++)
			{
				out_queue(qu, &a);
				code_buf[i] = a; //第一步先比对编码最短的
				code_buf[i + 1] = '\0';
				for (j = 0; j < leaf_num; j++)
				{
					if (code_len_list[j] == i + 1 && strcmp(map[j], code_buf) == 0) //寻找到对应的编码
					{
						ch = leaf_data_list[j]; //从编码表中取到叶子数据
						fputc(ch, res); //将解码出来的叶子写入到新文件中
						break;
					}
				}
				//寻找完毕，结束循环
				if (j < leaf_num)
					break;
			}
		}
	}

	//处理那个最后的特殊字节
	ch = fgetc(src);
	cast_in_queue(qu, ch);
	end_len = 8 - end_len;
	while (qu->length > end_len)
	{
		for (i = 0; i < min_len; i++)
		{
			out_queue(qu, &a);
			code_buf[i] = a;
		}
		for (; i < max_len; i++)
		{
			out_queue(qu, &a);
			code_buf[i] = a; //第一步先比对编码最短的
			code_buf[i + 1] = '\0';
			for (j = 0; j < leaf_num; j++)
			{
				if (code_len_list[j] == i + 1 && strcmp(map[j], code_buf) == 0) //寻找到对应的编码
				{
					ch = leaf_data_list[j]; //从编码表中取到叶子数据
					fputc(ch, res); //将解码出来的叶子写入到新文件中
					break;
				}
			}
			//寻找完毕，结束循环
			if (j < leaf_num)
				break;
		}
	}
	free(qu);
	free(code_buf);
	free(map);
	free(code_len_list);
	free(leaf_data_list);
	fclose(res);
	fclose(src);
	
}
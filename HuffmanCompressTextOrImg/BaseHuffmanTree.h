#ifndef _BaseHuffmanTree_H_
#define _BaseHuffmanTree_H_

#include "Structure.h"


void select_min_tree_node(TreeNode *ht, int n, int *min);
TreeNode *create_huffman_tree(FILE *fp, int *leaf_num, long *file_length);
int sort_tree(TreeNode *ht);
char **get_huffman_code(TreeNode *ht, int leaf_num);
void init_cycle_queue(MyQueue *qu);
void in_queue(MyQueue *qu, char ch);
int out_queue(MyQueue *qu, char *ch);
int copy_huffman_code_to_file(FILE *fp, char **map, int leaf_num, MyQueue *queue, DataType *end_length);
void get_max_min_code_length(FILE *fp, TreeNode *ht, char **map, int leaf_num, DataType *max, DataType *min);
#endif // !_BaseHuffmanTree_H_
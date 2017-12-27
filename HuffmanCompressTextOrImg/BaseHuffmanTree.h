
#ifndef _BaseHuffmanTree_H_
#define _BaseHuffmanTree_H_

#include "Structure.h"


void select_min_tree_node(TreeNode *ht, int n, int *min);
TreeNode *create_huffman_tree(FILE *fp, int *leaf_num, long *file_length);
int sort_tree(TreeNode *ht);
char **get_huffman_code(TreeNode *ht, int leaf_num);


#endif // !_BaseHuffmanTree_H_

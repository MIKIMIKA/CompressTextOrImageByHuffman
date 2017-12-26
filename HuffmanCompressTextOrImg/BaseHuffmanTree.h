
#ifndef _BaseHuffmanTree_H_
#define _BaseHuffmanTree_H_
#ifdef __cplusplus
extern "C" {
#endif
void select_min_tree_node(TreeNode *ht, int n, int *min);
TreeNode *create_huffman_tree(FILE *fp, int *leaf_num, long *file_length);
int sort_tree(TreeNode *ht);

#ifdef __cplusplus
}
#endif
#endif // !_BaseHuffmanTree_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"
#include "huffman.h"

/**
 * printArr - Prints the Huffman codes array
 * @arr: Array storing the codes
 * @top: Length of the codes
 */
void printArr(int arr[], int top)
{
	int i = 0;

	if (top == 0)
		printf("%d", arr[0]);
	else
	{
		while (i < top)
		{
			printf("%d", arr[i]);
			i++;
		}
	}
}

/**
 * print_codes - Prints the Huffman codes for each character
 * @root: Node of a Huffman tree
 * @arr: Array storing the codes
 * @top: Length of the codes
 */
void print_codes(binary_tree_node_t *root, int arr[], int top)
{
	if (root->left)
	{
		arr[top] = 0;
		print_codes(root->left, arr, top + 1);
	}
	if (root->right)
	{
		arr[top] = 1;
		print_codes(root->right, arr, top + 1);
	}

	if (((symbol_t *)root->data)->data > 0)
	{
		printf("%c: ", ((symbol_t *)root->data)->data);
		printArr(arr, top);
		printf("\n");
	}
}

/**
 * huffman_codes - Builds the Huffman tree and prints the resulting codes
 * @data: Array of characters of size `size`
 * @freq: Array containing the associated frequencies (of size `size`)
 * @size: Size of the array
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root = huffman_tree(data, freq, size);
	int arr[1024];

	arr[0] = 1;
	if (size > 0 && data != NULL && freq != NULL)
	{
		if (root == NULL)
			return (0);

		print_codes(root, arr, 0);
		binary_tree_delete(root, symbol_delete);
	}
	return (1);
}

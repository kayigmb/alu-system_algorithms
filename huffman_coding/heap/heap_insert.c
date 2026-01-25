#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heap.h"

/**
 * int2bin - Converts an integer to a binary string
 * @a: Integer to be converted
 *
 * Return: Binary string representation of the integer
 */
static char *int2bin(int a)
{
	char *str, *tmp;
	int cnt = 31;

	str = (char *)calloc(1, 33);
	tmp = str;
	while (cnt > -1)
	{
		str[cnt] = '0';
		cnt--;
	}
	cnt = 31;
	while (a > 0)
	{
		if (a % 2 == 1)
		{
			str[cnt] = '1';
		}
		cnt--;
		a = a / 2;
	}
	return (tmp);
}

/**
 * get_bottom_node - Creates and returns the bottom node of a heap
 * @heap: Pointer to the heap where the node has to be inserted
 * @data: Data to be inserted
 *
 * Return: Pointer to the bottom node
 */
static binary_tree_node_t *get_bottom_node(heap_t *heap, void *data)
{
	binary_tree_node_t *temp, *parent, *node;
	int l = 0, r = 0, pos, len, i = 0;
	char *bin = NULL, *bin_str = int2bin((int)heap->size + 1);
	char *e = strchr(bin_str, '1');

	/* Get the MSB index */
	pos = (int)(e - bin_str);
	bin = strdup(bin_str + pos + 1);
	temp = heap->root;
	parent = heap->root;
	len = strlen(bin);

	while (i < len)
	{
		parent = temp;
		if (bin[i] == '0')
		{
			temp = temp->left;
			r = 0;
			l++;
		}
		else
		{
			temp = temp->right;
			l = 0;
			r++;
		}
		i++;
	}

	free(bin);
	free(bin_str);

	node = binary_tree_node(parent, data);
	if (l > r)
		parent->left = node;
	else
		parent->right = node;

	return (node);
}

/**
 * swap - Swaps two pointers
 * @a: First pointer
 * @b: Second pointer
 */
static void swap(void **a, void **b)
{
	void *c;

	c = *a;
	*a = *b;
	*b = c;
}

/**
 * adjust_heap - Compares and sets the order in the heap
 * @heap: Pointer to the heap to be ordered
 * @node: Newly added node
 */
static void adjust_heap(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *temp;

	temp = node;
	while (temp->parent)
	{
		if (temp->data == NULL)
			swap(&temp->data, &temp->parent->data);
		else if (temp->parent->data &&
			 heap->data_cmp(temp->data, temp->parent->data) < 0)
			swap(&temp->data, &temp->parent->data);
		temp = temp->parent;
	}
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: Pointer to the heap in which the node has to be inserted
 * @data: Pointer containing the data to store in the new node
 *
 * Return: Pointer to the created node containing data, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node = NULL;

	if (heap == NULL)
		return (NULL);

	if (heap->root == NULL)
	{
		heap->root = binary_tree_node(NULL, data);
		if (heap->root != NULL)
			heap->size += 1;
		return (heap->root);
	}

	/* Add the element to the bottom level of the heap. */
	node = get_bottom_node(heap, data);
	if (node != NULL)
	{
		heap->size += 1;
		if (heap->data_cmp != NULL)
			adjust_heap(heap, node);
	}
	return (node);
}

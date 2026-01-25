#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

/**
 * symbol_delete - Deletes a symbol_t data structure
 * @sym: Symbol to be deleted
 */
void symbol_delete(void *sym)
{
	symbol_t *symbol = (symbol_t *)sym;

	if (symbol != NULL)
	{
		free(symbol);
		symbol = NULL;
	}
}

/**
 * symbol_create - Creates a symbol_t data structure
 * @data: Data to be stored in the structure
 * @freq: Frequency associated with the data
 *
 * Return: Pointer to the created structure, or NULL if it fails
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol = NULL;

	symbol = malloc(sizeof(symbol_t));
	if (symbol == NULL)
		return (NULL);

	symbol->data = data;
	symbol->freq = freq;

	return (symbol);
}

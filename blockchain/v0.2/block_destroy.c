#include "blockchain.h"

/**
 * block_destroy - deletes an existing block
 * @block: pointer to block to delete
 * Return: Nothing
 */
void block_destroy(block_t *block)
{
if (block)
{
free(block);
}
}

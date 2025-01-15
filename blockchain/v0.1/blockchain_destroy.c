#include "blockchain.h"

/**
 * blockchain_destroy - deletes and existing blockchain
 * @blockchain: pointer to blockchain structure to delete
 * Return: Nothing
 */
void blockchain_destroy(blockchain_t *blockchain)
{
block_t *current, *temp;
if (!blockchain)
return;
block = llist_pop(blockchain->chain);
while (block)
{
temp = block;
block_destroy(temp);
block = llist_pop(blockchain->chain);
}
llist_destroy(blockchain->chain, 0, NULL)
free(blockchain);
return;
}

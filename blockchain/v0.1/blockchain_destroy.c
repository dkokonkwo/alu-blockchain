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
current = llist_pop(blockchain->chain);
while (current)
{
temp = current;
block_destroy(temp);
current = llist_pop(blockchain->chain);
}
llist_destroy(blockchain->chain, 0, NULL);
free(blockchain);
return;
}

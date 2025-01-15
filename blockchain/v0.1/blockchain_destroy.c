#include "blockchain.h"

/**
 * blockchain_destroy - deletes and existing blockchain
 * @blockchain: pointer to blockchain structure to delete
 * Return: Nothing
 */
void blockchain_destroy(blockchain_t *blockchain)
{
if (blockchain)
{
if (llist_destroy(blockchain->chain, 1, block_destroy) != 0)
return;
free(blockchain);
return;
}
}

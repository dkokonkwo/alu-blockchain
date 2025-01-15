#include "blockchain.h"

#define GENESIS_HASH "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"
#define GENESIS_TIMESTAMP 1537578000
#define GENESIS_DATA "Holberton School"
#define GENESIS_DATA_LEN 16

/**
 * blockchain_create - creates a blockchain structure and initializes it
 * Return: pointer to blockchain else NULL
 */
blockchain_t *blockchain_create(void)
{
blockchain_t *nblockchain = NULL;
block_t *nblock = NULL;
llist_t *llist = NULL;
nblock = (block_t *)malloc(sizeof(block_t));
if (!nblock)
{
fprintf(stderr, "Failed to allocate memory for genesis block\n");
return (NULL);
}
nblock->info.index = 0;
nblock->info.difficulty = 0;
nblock->info.nonce = 0;
nblock->info.timestamp = GENESIS_TIMESTAMP;
memset(nblock->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
memcpy(nblock->data.buffer, GENESIS_DATA, GENESIS_DATA_LEN);
nblock->data.len = GENESIS_DATA_LEN;
memcpy(nblock->hash, GENESIS_HASH, SHA256_DIGEST_LENGTH);

llist = llist_create(MT_SUPPORT_TRUE);
if (!llist)
{
fprintf(stderr, "Failed to create blockchain list\n");
free(nblock);
return (NULL);
}

if (llist_add_node(llist, nblock, ADD_NODE_FRONT) != 0)
{
fprintf(stderr, "Failed to add genesis block to blockchain list\n");
llist_destroy(llist, 1, NULL);
free(nblock);
return (NULL);
}

nblockchain = (blockchain_t *)malloc(sizeof(blockchain_t));
if (!nblockchain)
{
fprintf(stderr, "Failed to allocate memory for blockchain structure\n");
llist_destroy(llist, 1, NULL);
free(nblock);
return (NULL);
}
nblockchain->chain = llist;
return (nblockchain);
}


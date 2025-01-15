#include "blockchain.h"

#define HASH "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"
/**
 * blockchain_create - creates a blockchain structure and initializes it
 * Return: pointer to blockchain else NULL
 */
blockchain_t *blockchain_create(void)
{
    llist_t *llist;
    blockchain_t *nblockchain;
    block_t *nblock = (block_t *)malloc(sizeof(block_t));
    if (!nblock)
        return (NULL);
    nblock->info.index = 0;
    nblock->info.difficulty = 0;
    nblock->info.nonce = 0;
    nblock->info.timestamp = 1537578000;
    memset(nblock->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
    memcpy(nblock->data.buffer, "Holberton School", 16);
    nblock->data.len = 16;
    memcpy(nblock->hash, HASH, SHA256_DIGEST_LENGTH);
    llist = llist_create(MT_SUPPORT_TRUE);
    if (!llist)
    {
        free(nblock);
        return (NULL);
    }
    if (llist_add_node(llist, nblock, ADD_NODE_FRONT) != 0)
    {
        llist_destroy(llist, 1, NULL);
        free(nblock);
        return (NULL);
    }
    nblockchain = (blockchain_t *)malloc(sizeof(blockchain_t));
    if (!nblockchain)
    {
        llist_destroy(llist, 1, NULL);
        free(nblock);
        return (NULL);
    }
    nblockchain->chain = llist;
    return (nblockchain);
}

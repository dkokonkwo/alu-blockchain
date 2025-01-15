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
	blockchain_t *blockchain = NULL;
	block_t *genesis_block = NULL;
	llist_t *llist = NULL;

	genesis_block = calloc(1, sizeof(*genesis_block));
	if (genesis_block == NULL)
		return (NULL);

	genesis_block->info.index = 0;
	genesis_block->info.difficulty = 0;
	genesis_block->info.timestamp = 1537578000;
	genesis_block->info.nonce = 0;
	memset(genesis_block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	memcpy(genesis_block->data.buffer, GENESIS_TIMESTAMP, GENESIS_DATA_LEN);
	genesis_block->data.len = GENESIS_DATA_LEN;
	memcpy(genesis_block->hash, HASH, SHA256_DIGEST_LENGTH);

	llist = llist_create(MT_SUPPORT_TRUE);
	if (llist == NULL)
	{
		free(genesis_block);
		return (NULL);
	}

	if (llist_add_node(llist, genesis_block, ADD_NODE_FRONT) != 0)
	{
		llist_destroy(llist, 1, NULL), free(genesis_block);
		return (NULL);
	}

	blockchain = calloc(1, sizeof(*blockchain));
	if (blockchain == NULL)
	{
		llist_destroy(llist, 1, NULL), free(genesis_block);
		return (NULL);
	}
	blockchain->chain = llist;

	return (blockchain);
}

#include "blockchain.h"

/**
 * block_create - creates and initializes block structure
 * @prev: pointer to previous block
 * @data: points to data memory area to duplicate block's data
 * @data_len: stores the number of bytes to duplicate in data
 * Return: pointer to allocated block
 */
block_t *block_create(block_t const *prev,
int8_t const *data, uint32_t data_len)
{
block_t *new_block = NULL;

new_block = calloc(1, sizeof(*new_block));
if (!new_block)
return (NULL);

new_block->info.index = prev->info.index + 1;
new_block->info.difficulty = 0;
new_block->info.nonce = 0;
new_block->info.timestamp = (uint64_t)time(NULL);
memcpy(new_block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
if (data_len > BLOCKCHAIN_DATA_MAX)
data_len = BLOCKCHAIN_DATA_MAX;
memcpy(new_block->data.buffer, data, data_len);
new_block->data.len = data_len;
memset(new_block->hash, 0, SHA256_DIGEST_LENGTH);

return (new_block);
}

#include "blockchain.h"

/**
 * block_hash - computes the hash of a block
 * @block: pointer to block to be hashed
 * @hash_buf: buffer to store the hash
 * Return: pointer to @hash_buf
 */
uint8_t *block_hash(block_t const *block,
uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
size_t hash_len = sizeof(block->info) + block->data.len;
return (sha256((int8_t const *)block, hash_len, hash_buf));
}

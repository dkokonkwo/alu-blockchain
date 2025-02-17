#include "blockchain.h"

/**
 * block_mine - mines a block in order to insert it in a blockchain
 * @block: pointer to block to be mined
 */
void block_mine(block_t *block)
{
uint64_t nonce = 0;
uint8_t hash[SHA256_DIGEST_LENGTH];
if (!block)
return;

do {
block->info.nonce = nonce;
block_hash(block, hash);
nonce++;
} while (!hash_matches_difficulty(hash, block->info.difficulty));

memcpy(block->hash, hash, SHA256_DIGEST_LENGTH);
}

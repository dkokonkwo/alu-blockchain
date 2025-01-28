#include "blockchain.h"

/**
 * blockchain_difficulty - computes difficulty to assign to potential next
 * @blockchain: pointer to blockchain to analyze
 * Return: difficulty to assign to potential next block
 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
block_t *lblock, *cblock;
uint64_t expected, actual;
if (!blockchain)
return (0);

lblock = llist_get_tail(blockchain->chain);
if (!lblock)
return (0);
if (lblock->info.index == 0 || lblock->info.index %
BLOCK_GENERATION_INTERVAL)
return (lblock->info.difficulty);

cblock = llist_get_node_at(blockchain->chain, lblock->info.index + 1 -
DIFFICULTY_ADJUSTMENT_INTERVAL);
expected = BLOCK_GENERATION_INTERVAL *
DIFFICULTY_ADJUSTMENT_INTERVAL;
actual = lblock->info.timestamp - cblock->info.timestamp;
if (actual * 2 < expected)
return (lblock->info.difficulty + 1);
else if (actual > 2 * expected)
return (lblock->info.difficulty > 0 ? lblock->info.difficulty - 1 : 0);
return (lblock->info.difficulty);
}

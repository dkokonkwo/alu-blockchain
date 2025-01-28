#include "blockchain.h"

/**
 * hash_matches_difficulty - checks that a given hash matches a difficulty
 * @hash: hash to check
 * @difficulty: minimum difficulty the hash should match
 * Return: 1 if difficulty is respected, or otherwise 0
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
uint32_t difficulty)
{
uint32_t i;
if (!hash || !difficulty)
return (0);

for (i = 0; i < difficulty; i++)
{
if (hash[i] != 0)
return (0);
}

return (1);
}

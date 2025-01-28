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
uint32_t byte_index;
uint32_t total_bits = SHA256_DIGEST_LENGTH * 8;
uint8_t mask;
if (!hash || difficulty > total_bits)
return (0);

/* checking leading zero bytes */
for (byte_index = 0; difficulty >= 8 && byte_index < SHA256_DIGEST_LENGTH;
byte_index++, difficulty -= 8)
{
if (hash[byte_index] != 0)
return (0);
}

/* checking the remaining zero bits */
if (difficulty > 0)
{
mask = 0xFF << (8 - difficulty); /* mask for the remaining bits */
if ((hash[byte_index] & mask) != 0)
return (0);
}
return (1);
}

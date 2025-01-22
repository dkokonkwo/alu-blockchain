#include "./blockchain.h"
#include "transaction.h"

/**
 * transaction_hash - computes the ID(hash) of a transaction
 * @transaction: pointer to transaction to compute hash of
 * @hash_buf: buffer to store the computed hash
 * Return: pointer to @hash_buf
 */
uint8_t *transaction_hash(transaction_t const *transaction,
uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
size_t data_len;
if (!transaction || !hash_buf)
return (NULL);
data_len = SHA256_DIGEST_LENGTH * 3 * llist_size(transaction->inputs) + SHA256_DIGEST_LENGTH * llist_size(transaction->outputs);
return (sha256((const int8_t *)transaction, data_len, hash_buf));
}

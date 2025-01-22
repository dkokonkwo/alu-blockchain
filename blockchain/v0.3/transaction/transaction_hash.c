#include "./blockchain.h"
#include "transaction.h"

int hash_inputs(llist_node_t node, unsigned int idx, void *arg);
int hash_outputs(llist_node_t node, unsigned int idx, void *arg);

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
uint8_t *_buf, *buf;
if (!transaction)
    return (NULL);
data_len = SHA256_DIGEST_LENGTH * 3 * llist_size(transaction->inputs) + SHA256_DIGEST_LENGTH * llist_size(transaction->outputs);
_buf = buf = calloc(1, data_len);
if (!_buf)
    return (NULL);
llist_for_each(transaction->inputs, hash_inputs, &buf);
llist_for_each(transaction->outputs, hash_outputs, &buf);
if (!sha256((const int8_t *)transaction, data_len, hash_buf))
    hash_buf = NULL;
free(_buf);
return (hash_buf);
}

/**
 * hash_inputs - llist action func to hash inputs
 * @node: tx_in_t * struct
 * @idx: index of node
 * @arg: pointer to address to write to
 * Return: 0 if success else 1
 */
int hash_inputs(llist_node_t node, unsigned int idx, void *arg)
{
	memcpy(*(uint8_t **)arg, node, SHA256_DIGEST_LENGTH * 3);
	*(uint8_t **)arg += SHA256_DIGEST_LENGTH * 3;
	return (0);
	(void)idx;
}

/**
 * hash_outputs - llist action func to hash outputs
 * @node: tx_out_t * struct
 * @idx: index of node
 * @arg: pointer to address to write to
 * Return: 0 if success else 1
 */
int hash_outputs(llist_node_t node, unsigned int idx, void *arg)
{
	memcpy(*(uint8_t **)arg, ((tx_out_t *)node)->hash, SHA256_DIGEST_LENGTH);
	*(uint8_t **)arg += SHA256_DIGEST_LENGTH;
	return (0);
	(void)idx;
}

#include "./blockchain.h"
#include "transaction.h"

/**
 * unspent_tx_out_create - allocates and initializes an unspent transaction
 * @block_hash: contains hash of the Block where output is located
 * @tx_id: contain hash of a transaction in the Block @block_hash
 * @out: points to referenced transaction output
 * Return: pointer to created unspent transaction, or NULL on failure
 */
unspent_tx_out_t *unspent_tx_out_create(
uint8_t block_hash[SHA256_DIGEST_LENGTH],
uint8_t tx_id[SHA256_DIGEST_LENGTH],
tx_out_t const *out)
{
unspent_tx_out_t *unspent;
if (!out)
return (NULL);
unspent = (unspent_tx_out_t *)malloc(sizeof(unspent_tx_out_t));
if (!unspent)
return (NULL);
memcpy(unspent->block_hash, block_hash, SHA256_DIGEST_LENGTH);
memcpy(unspent->tx_id, tx_id, SHA256_DIGEST_LENGTH);
unspent->out = *out;
return (unspent);
}

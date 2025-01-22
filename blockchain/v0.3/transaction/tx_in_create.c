#include "./blockchain.h"
#include "transaction.h"

/**
 * tx_in_create - initializes transaction input structure
 * @unspent: pointer to unspent transaction output
 * Return: pointer to created transaction input structure, or NULL on failure
 */
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
tx_in_t *input;
if (!unspent)
return (NULL);
input = calloc(1, sizeof(*input));
if (!input)
return (NULL);
memcpy(input->block_hash, unspent->block_hash, SHA256_DIGEST_LENGTH);
memcpy(input->tx_id, unspent->tx_id, SHA256_DIGEST_LENGTH);
memcpy(input->tx_out_hash, unspent->out.hash, SHA256_DIGEST_LENGTH);
return (input);
}

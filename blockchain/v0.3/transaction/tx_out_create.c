#include "./blockchain.h"
#include "transaction.h"

/**
 * tx_out_create - allocate and initializes a transaction output structure
 * @amount: amount of the transaction
 * @pub: public key of the transaction receiver
 * Return: pointer to created transactinon output, or NULL on failure
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
tx_out_t *output;
size_t data_len;
if (!amount || !pub)
return (NULL);
output = (tx_out_t *)malloc(sizeof(tx_out_t));
if (!output)
return (NULL);
output->amount = amount;
memcpy(output->pub, pub, EC_PUB_LEN);
data_len = sizeof(output->amount) + EC_PUB_LEN;
sha256((const int8_t *)output, data_len, output->hash);
return (output);
}

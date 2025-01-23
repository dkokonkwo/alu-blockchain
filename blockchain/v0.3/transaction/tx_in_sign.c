#include "./blockchain.h"
#include "transaction.h"

/**
 * tx_in_sign - signs a transaction input, given the transaction id
 * @in: pointer to transaction input structure sign
 * @tx_id: contains the ID(hash) of the transaction input to sign
 * @sender: contains the private key of the receiver of the coins
 * @all_unspent: is the list of all unspent
 * Return: pointer to resulting signature structure, or NULL upon failure
 */
sig_t *tx_in_sign(tx_in_t *in, uint8_t const tx_id[SHA256_DIGEST_LENGTH],
EC_KEY const *sender, llist_t *all_unspent)
{
uint8_t pub[EC_PUB_LEN];
ssize_t i;
unspent_tx_out_t *utx;
if (!in || !sender || !all_unspent)
return (NULL);
for (i = 0; i < llist_size(all_unspent); i++)
{
utx = llist_get_node_at(all_unspent, i);
if (!memcmp(in->tx_out_hash, utx->out.hash, SHA256_DIGEST_LENGTH))
break;
utx = NULL;
}
if (!utx || !ec_to_pub(sender, pub) || memcmp(pub, utx->out.pub, EC_PUB_LEN))
return (NULL);
if (!ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &in->sig))
return (NULL);
return (&in->sig);
}

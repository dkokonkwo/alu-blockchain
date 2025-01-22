#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "./blockchain.h"


/* FUNCTIONS */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN]);

#endif /* transaction.h */

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <llist.h>
#include "../../crypto/hblk_crypto.h"

#include <openssl/sha.h>
#include "provided/endianness.h"

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#define BLOCKCHAIN_DATA_MAX 1024
#define HBLK_MAGIC "HBLK"
#define HBLK_VERSION "0.2"
#define BLOCK_GENERATION_INTERVAL 1
#define DIFFICULTY_ADJUSTMENT_INTERVAL 5

/**
 * struct block_info_s - Block info structure
 *
 * @index:      Index of the Block in the Blockchain
 * @difficulty: Difficulty of proof of work (hash leading zero bits)
 * @timestamp:  Time the Block was created at (UNIX timestamp)
 * @nonce:      Salt value used to alter the Block hash
 * @prev_hash:  Hash of the previous Block in the Blockchain
 */
typedef struct block_info_s
{
    /*
     * The order of the elements in this structure should remain the same.
     * It was designed so every element of this structure is aligned and
     * doesn't require padding from the compiler.
     * Therefore, it is possible to use the structure as an array of char,
     * on any architecture.
     */
    uint32_t    index;
    uint32_t    difficulty;
    uint64_t    timestamp;
    uint64_t    nonce;
    uint8_t     prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;


/**
 * struct block_data_s - Block data
 *
 * @buffer: Data buffer
 * @len:    Data size (in bytes)
 */
typedef struct block_data_s
{
    /*
     * @buffer must stay first, so we can directly use the structure as
     * an array of char
     */
    int8_t      buffer[BLOCKCHAIN_DATA_MAX];
    uint32_t    len;
} block_data_t;


/**
 * struct blockchain_s - Blockchain structure
 *
 * @chain: Linked list of pointers to block_t
 */
typedef struct blockchain_s
{
    llist_t     *chain;
} blockchain_t;

/**
 * struct block_s - Block structure
 *
 * @info: Block info
 * @data: Block data
 * @hash: 256-bit digest of the Block, to ensure authenticity
 */
typedef struct block_s
{
    block_info_t    info; /* This must stay first */
    block_data_t    data; /* This must stay second */
    uint8_t     hash[SHA256_DIGEST_LENGTH];
} block_t;

/**
 * hblk_file_s - block file format
 * @hblk_magic: identifies file as valid serialized blockchain
 * @hblk_version: identifies version at which the blockchain has been serialized
 * @hblk_endian: byte to signify little or big endianness
 * @hblk_blocks: number of blocks in the blockchain
 */
typedef struct hblk_file_s
{
    int8_t hblk_magic[4];
    int8_t hblk_version[3];
    int8_t hblk_endian;
    int32_t hblk_blocks;
} hblk_file_t;


blockchain_t *blockchain_create(void);
block_t *block_create(block_t const *prev, int8_t const *data, uint32_t data_len);
void block_destroy(block_t *block);
void blockchain_destroy(blockchain_t *blockchain);
uint8_t *block_hash(block_t const *block, uint8_t hash_buf[SHA256_DIGEST_LENGTH]);
int blockchain_serialize(blockchain_t const *blockchain, char const *path);
int block_serialize(llist_node_t nptr, int idx, void *arg);
blockchain_t *blockchain_deserialize(char const *path);
llist_t *deserialize_blocks(int fd, uint32_t size, uint8_t endianness);
int block_is_valid(block_t const *block, block_t const *prev_block);

extern block_t const _genesis;

/* blockchain mining */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH], uint32_t difficulty);
void block_mine(block_t *block);
uint32_t blockchain_difficulty(blockchain_t const *blockchain);
#endif /* BLOCKCHAIN_H */

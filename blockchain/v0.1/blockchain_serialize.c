#include "blockchain.h"

/**
 * blockchain_serialize - serializes a blockchain into a file
 * @blockchain: pointer to the blockchain to be serialized
 * @path: path to a file to serialize the Blockchain into
 * Return: 0 on success or -1 on failure
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
FILE *file;
hblk_file_t fHeader;
if (!blockchain || !path)
return (-1);

memcpy(fHeader.hblk_magic, HBLK_MAGIC, strlen(HBLK_MAGIC));
memcpy(fHeader.hblk_version, HBLK_VERSION, strlen(HBLK_VERSION));
fHeader.hblk_blocks = llist_size(blockchain->chain);
fHeader.hblk_endian = _get_endianness();

if (fHeader.hblk_blocks == -1)
return (-1);

file = fopen(path, "w");
if (!file)
return (-1);

fwrite(&fHeader, sizeof(fHeader), 1 , file);

llist_for_each(blockchain->chain, (node_func_t)block_serialize, file);

fclose(file);
return (0);
}

/**
 * block_serialize - serialize a block into file
 * @nptr: pointer to node the serializes
 * @idx: index of the node
 * @arg: file descriptor
 * Return: 0 on success else -1 on failure
 */


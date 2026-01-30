#ifndef BITSET_H
#define BITSET_H

#include <stddef.h>

/** Compact bit array using 64-bit words with hardware popcount. */
typedef struct Bitset Bitset;

/** Creates a bitset with specified number of bits. @return Bitset or NULL. */
Bitset *bitset_create(size_t num_bits);

/** Frees all bitset memory. */
void bitset_destroy(Bitset *bs);

/** Sets bit at index. @return 0 on success, -1 on error. */
int bitset_set(Bitset *bs, size_t bit_index);

/** Clears bit at index. @return 0 on success, -1 on error. */
int bitset_clear(Bitset *bs, size_t bit_index);

/** Flips bit at index. @return 0 on success, -1 on error. */
int bitset_flip(Bitset *bs, size_t bit_index);

/** Tests bit at index. @return 1 if set, 0 if clear, -1 on error. */
int bitset_test(const Bitset *bs, size_t bit_index);

/** Sets all bits to 1. */
void bitset_set_all(Bitset *bs);

/** Sets all bits to 0. */
void bitset_clear_all(Bitset *bs);

/** Flips all bits. */
void bitset_flip_all(Bitset *bs);

/** Returns number of set bits (uses hardware popcount). */
size_t bitset_count(const Bitset *bs);

/** Returns total number of bits. */
size_t bitset_size(const Bitset *bs);

/** Checks if all bits are set. @return 1 if all, 0 otherwise. */
int bitset_all(const Bitset *bs);

/** Checks if any bit is set. @return 1 if any, 0 otherwise. */
int bitset_any(const Bitset *bs);

/** Checks if no bits are set. @return 1 if none, 0 otherwise. */
int bitset_none(const Bitset *bs);

/** Bitwise AND: dest &= src. @return 0 on success, -1 on error. */
int bitset_and(Bitset *dest, const Bitset *src);

/** Bitwise OR: dest |= src. @return 0 on success, -1 on error. */
int bitset_or(Bitset *dest, const Bitset *src);

/** Bitwise XOR: dest ^= src. @return 0 on success, -1 on error. */
int bitset_xor(Bitset *dest, const Bitset *src);

/** Checks if two bitsets are equal. @return 1 if equal, 0 otherwise. */
int bitset_equals(const Bitset *bs1, const Bitset *bs2);

/** Prints bitset in compact form. */
void bitset_print(const Bitset *bs);

/** Prints bitset with detailed info. */
void bitset_debug(const Bitset *bs);

#endif // BITSET_H
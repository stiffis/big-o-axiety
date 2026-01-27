#ifndef BITSET_H
#define BITSET_H

#include <stddef.h>

typedef struct Bitset Bitset;

Bitset *bitset_create(size_t num_bits);

void bitset_destroy(Bitset *bs);

int bitset_set(Bitset *bs, size_t bit_index);

int bitset_clear(Bitset *bs, size_t bit_index);

int bitset_flip(Bitset *bs, size_t bit_index);

int bitset_test(const Bitset *bs, size_t bit_index);

void bitset_set_all(Bitset *bs);

void bitset_clear_all(Bitset *bs);

void bitset_flip_all(Bitset *bs);

size_t bitset_count(const Bitset *bs);

size_t bitset_size(const Bitset *bs);

int bitset_all(const Bitset *bs);

int bitset_any(const Bitset *bs);

int bitset_none(const Bitset *bs);

int bitset_and(Bitset *dest, const Bitset *src);

int bitset_or(Bitset *dest, const Bitset *src);

int bitset_xor(Bitset *dest, const Bitset *src);

int bitset_equals(const Bitset *bs1, const Bitset *bs2);

void bitset_print(const Bitset *bs);

void bitset_debug(const Bitset *bs);

#endif // BITSET_H

#include "../include/bitset.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BITS_PER_WORD 64
#define WORD_INDEX(bit) ((bit) / BITS_PER_WORD)
#define BIT_OFFSET(bit) ((bit) % BITS_PER_WORD)

struct Bitset {
    uint64_t *data;
    size_t num_bits;
    size_t num_words;
};

Bitset* bitset_create(size_t num_bits) {
    if (num_bits == 0) {
        return NULL;
    }
    
    struct Bitset *bs = malloc(sizeof(struct Bitset));
    if (!bs) {
        return NULL;
    }
    
    size_t num_words = (num_bits + BITS_PER_WORD - 1) / BITS_PER_WORD;
    bs->data = calloc(num_words, sizeof(uint64_t));
    if (!bs->data) {
        free(bs);
        return NULL;
    }
    
    bs->num_bits = num_bits;
    bs->num_words = num_words;
    
    return bs;
}

void bitset_destroy(Bitset *bs) {
    if (!bs) {
        return;
    }
    
    free(bs->data);
    free(bs);
}

int bitset_set(Bitset *bs, size_t bit_index) {
    if (!bs || bit_index >= bs->num_bits) {
        return -1;
    }
    
    size_t word_idx = WORD_INDEX(bit_index);
    size_t bit_off = BIT_OFFSET(bit_index);
    
    bs->data[word_idx] |= (1ULL << bit_off);
    
    return 0;
}

int bitset_clear(Bitset *bs, size_t bit_index) {
    if (!bs || bit_index >= bs->num_bits) {
        return -1;
    }
    
    size_t word_idx = WORD_INDEX(bit_index);
    size_t bit_off = BIT_OFFSET(bit_index);
    
    bs->data[word_idx] &= ~(1ULL << bit_off);
    
    return 0;
}

int bitset_flip(Bitset *bs, size_t bit_index) {
    if (!bs || bit_index >= bs->num_bits) {
        return -1;
    }
    
    size_t word_idx = WORD_INDEX(bit_index);
    size_t bit_off = BIT_OFFSET(bit_index);
    
    bs->data[word_idx] ^= (1ULL << bit_off);
    
    return 0;
}

int bitset_test(const Bitset *bs, size_t bit_index) {
    if (!bs || bit_index >= bs->num_bits) {
        return -1;
    }
    
    size_t word_idx = WORD_INDEX(bit_index);
    size_t bit_off = BIT_OFFSET(bit_index);
    
    return (bs->data[word_idx] & (1ULL << bit_off)) != 0;
}

void bitset_set_all(Bitset *bs) {
    if (!bs) {
        return;
    }
    
    // Set all complete words to 0xFFFFFFFFFFFFFFFF
    for (size_t i = 0; i < bs->num_words; i++) {
        bs->data[i] = UINT64_MAX;
    }
    
    // Clear extra bits in the last word if num_bits is not aligned to 64
    size_t extra_bits = bs->num_words * BITS_PER_WORD - bs->num_bits;
    if (extra_bits > 0) {
        uint64_t mask = (1ULL << (BITS_PER_WORD - extra_bits)) - 1;
        bs->data[bs->num_words - 1] &= mask;
    }
}

void bitset_clear_all(Bitset *bs) {
    if (!bs) {
        return;
    }
    
    memset(bs->data, 0, bs->num_words * sizeof(uint64_t));
}

void bitset_flip_all(Bitset *bs) {
    if (!bs) {
        return;
    }
    
    for (size_t i = 0; i < bs->num_words; i++) {
        bs->data[i] = ~bs->data[i];
    }
    
    // Clear extra bits in the last word if num_bits is not aligned to 64
    size_t extra_bits = bs->num_words * BITS_PER_WORD - bs->num_bits;
    if (extra_bits > 0) {
        uint64_t mask = (1ULL << (BITS_PER_WORD - extra_bits)) - 1;
        bs->data[bs->num_words - 1] &= mask;
    }
}

size_t bitset_count(const Bitset *bs) {
    if (!bs) {
        return 0;
    }
    
    size_t count = 0;
    for (size_t i = 0; i < bs->num_words; i++) {
        count += __builtin_popcountll(bs->data[i]);
    }
    
    return count;
}

size_t bitset_size(const Bitset *bs) {
    if (!bs) {
        return 0;
    }
    
    return bs->num_bits;
}

int bitset_all(const Bitset *bs) {
    if (!bs) {
        return 0;
    }
    
    return bitset_count(bs) == bs->num_bits;
}

int bitset_any(const Bitset *bs) {
    if (!bs) {
        return 0;
    }
    
    return bitset_count(bs) > 0;
}

int bitset_none(const Bitset *bs) {
    if (!bs) {
        return 1;
    }
    
    return bitset_count(bs) == 0;
}

int bitset_and(Bitset *dest, const Bitset *src) {
    if (!dest || !src || dest->num_bits != src->num_bits) {
        return -1;
    }
    
    for (size_t i = 0; i < dest->num_words; i++) {
        dest->data[i] &= src->data[i];
    }
    
    return 0;
}

int bitset_or(Bitset *dest, const Bitset *src) {
    if (!dest || !src || dest->num_bits != src->num_bits) {
        return -1;
    }
    
    for (size_t i = 0; i < dest->num_words; i++) {
        dest->data[i] |= src->data[i];
    }
    
    return 0;
}

int bitset_xor(Bitset *dest, const Bitset *src) {
    if (!dest || !src || dest->num_bits != src->num_bits) {
        return -1;
    }
    
    for (size_t i = 0; i < dest->num_words; i++) {
        dest->data[i] ^= src->data[i];
    }
    
    return 0;
}

int bitset_equals(const Bitset *bs1, const Bitset *bs2) {
    if (!bs1 || !bs2) {
        return 0;
    }
    
    if (bs1->num_bits != bs2->num_bits) {
        return 0;
    }
    
    return memcmp(bs1->data, bs2->data, bs1->num_words * sizeof(uint64_t)) == 0;
}

void bitset_print(const Bitset *bs) {
    if (!bs) {
        printf("(null)");
        return;
    }
    
    for (size_t i = 0; i < bs->num_bits; i++) {
        printf("%d", bitset_test(bs, i));
        if ((i + 1) % 8 == 0 && i + 1 < bs->num_bits) {
            printf(" ");
        }
    }
}

void bitset_debug(const Bitset *bs) {
    if (!bs) {
        printf("Bitset(NULL)\n");
        return;
    }
    
    printf("Bitset(bits: %zu, set: %zu) [", bs->num_bits, bitset_count(bs));
    bitset_print(bs);
    printf("]\n");
}

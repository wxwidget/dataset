#include "hash_inline.h"
// Hash Function for a single int.
unsigned int svmformat::Hash(int key, int mask) {
    int hash(key);
    hash += (hash << 10);
    hash ^= (hash >> 6);
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash & mask;
}

// Hash function for two int's.
unsigned int svmformat::Hash(int key_1, int key_2, int mask) {
    unsigned int hash(key_1);
    hash += (hash << 10);
    hash ^= (hash >> 6);

    hash += key_2;
    hash += (hash << 10);
    hash ^= (hash >> 6);

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash & mask;
}

// Hash function for a vector of int's.  Assumes that keys has
// at least one entry.
unsigned int svmformat::Hash(const vector<int>& keys, int mask) {
    unsigned int hash = 0;
    for(unsigned int i = 0; i < keys.size(); ++i) {
        hash += keys[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash & mask;
}

int svmformat::HashMask(int num_bits) {
    int mask = 1;
    for(int i = 1; i < num_bits; ++i) {
        mask += (1 << i);
    }
    return mask;
}


#ifndef HASH_INLINE_H__
#define HASH_INLINE_H__

#include <vector>
using std::vector;
namespace svmformat {
unsigned int Hash(int key, int mask);
unsigned int Hash(int key_1, int key_2, int mask);
unsigned int Hash(const vector<int>& keys, int mask);
// Construct a mask with 1's in the num_bits lowest order bits.
int HashMask(int num_bits);
}
#endif

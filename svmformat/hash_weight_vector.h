#ifndef HASH_WEIGHT_VECTOR_H__
#define HASH_WEIGHT_VECTOR_H__

#include "hash_inline.h"
#include "weight_vector.h"

using std::string;
namespace svmformat {
class HashWeightVector : public WeightVector {
public:
    // Construct a weight vector of dimenson 2^hash_mask_bits, with all weights initialized to
    // zero, scale_ set to 1, and squared_norm_ set to 0.  Also initializes the hash_mask
    // appropriately.
    HashWeightVector(int hash_mask_bits);

    // Constructs a weight vector from a string, using the defined number of hash_mask_bits.
    HashWeightVector(int hash_mask_bits,
                     const string& weight_vector_string);

    // Frees the array of weights.
    virtual ~HashWeightVector();

    // Computes inner product of <phi(x_scale * x), w>, where phi()
    // is a vector composed of all features in x and the cross-product
    // of all features in x, where each of these features is hashed
    // to some new feature id from 0 to 2^num_bits_for_hash_ - 1.
    virtual float InnerProduct(const SparseVector& x,
                               float x_scale = 1.0) const;

    // w += phi(x_scale * x), where phi is defined as for InnerProduct above.
    virtual void AddVector(const SparseVector& x, float x_scale);

private:
    // Disallowed.
    HashWeightVector();

    int hash_mask_bits_;
    int hash_mask_;
};
}
#endif  // 

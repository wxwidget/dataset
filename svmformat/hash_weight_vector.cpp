
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "hash_weight_vector.h"

using namespace svmformat;
HashWeightVector::HashWeightVector(int hash_mask_bits)
    : WeightVector(1 << hash_mask_bits),
      hash_mask_bits_(hash_mask_bits) {
    if(hash_mask_bits_ < 0) {
        std::cerr << "Illegal number of hash_mask_bits for of weight vector less than 1."
                  << std::endl << "hash_mask_bits__: " << dimensions_ << std::endl;
        exit(1);
    }
    hash_mask_ = HashMask(hash_mask_bits);

    std::cout << "hash_mask_ " << hash_mask_ << std::endl;
}

HashWeightVector::HashWeightVector(int hash_mask_bits,
                                   const string& weight_vector_string)
    : WeightVector(weight_vector_string),
      hash_mask_bits_(hash_mask_bits) {
    if(hash_mask_bits_ < 0) {
        std::cerr << "Illegal number of hash_mask_bits for of weight vector less than 1." << std::endl
                  << "hash_mask_bits__: " << dimensions_ << std::endl;
        exit(1);
    }
    hash_mask_ = HashMask(hash_mask_bits);
}

HashWeightVector::~HashWeightVector() {
    delete[] weights_;
}

float HashWeightVector::InnerProduct(const SparseVector& x,
                                     float x_scale) const {
    float inner_product = 0.0;
    for(int i = 0; i < x.NumFeatures(); ++i) {
        inner_product +=
            weights_[Hash(x.FeatureAt(i), hash_mask_)] * x.ValueAt(i);
    }
    for(int i = 0; i < x.NumFeatures(); ++i) {
        float x_i_value = x.ValueAt(i);
        int x_i_feature = x.FeatureAt(i);
        for(int j = i; j < x.NumFeatures(); ++j) {
            inner_product +=
                weights_[Hash(x_i_feature, x.FeatureAt(j), hash_mask_)] *
                x_i_value * x.ValueAt(j);
        }
    }
    inner_product *= x_scale;
    inner_product *= scale_;
    return inner_product;
}

void HashWeightVector::AddVector(const SparseVector& x,
                                 float x_scale) {
    float inner_product = 0.0;
    float norm_x = 0.0;

    for(int i = 0; i < x.NumFeatures(); ++i) {
        float this_x_value = x.ValueAt(i) * x_scale;
        int this_x_feature = Hash(x.FeatureAt(i), hash_mask_);
        if(this_x_feature >= dimensions_) {
            std::cerr << "Error: feature hash id " << this_x_feature
                      << " exceeds weight vector dimension " << dimensions_
                      << std::endl;
            exit(1);
        }
        norm_x += this_x_value * this_x_value;
        inner_product += weights_[this_x_feature] * this_x_value;
        weights_[this_x_feature] += this_x_value / scale_;
    }
    for(int i = 0; i < x.NumFeatures(); ++i) {
        float x_i_value = x.ValueAt(i);
        int x_i_feature = x.FeatureAt(i);
        for(int j = i; j < x.NumFeatures(); ++j) {
            float this_x_value = x_i_value * x.ValueAt(j) * x_scale;
            int this_x_feature = Hash(x_i_feature, x.FeatureAt(j), hash_mask_);
            if(this_x_feature >= dimensions_) {
                std::cerr << "Error: cross-product feature hash id " << this_x_feature
                          << " exceeds weight vector dimension " << dimensions_;
                exit(1);
            }
            norm_x += this_x_value * this_x_value;
            inner_product += weights_[this_x_feature] * this_x_value;
            weights_[this_x_feature] += this_x_value / scale_;
        }
    }
    squared_norm_ += norm_x + (2.0 * scale_ * inner_product);
}

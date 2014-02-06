#ifndef DATA_SET_H_
#define DATA_SET_H_
#include <string>
#include <vector>
#include "sparse_vector.h"

namespace svmformat {
class DataSet {
public:
    DataSet(bool use_bias_term);
    // Use buffer_mb megabytes for the buffer.
    DataSet(const string& file_name, int buffer_mb, bool use_bias_term);
    // Debug string.
    string AsString() const;
    // Number of total examples in data set.
    long int NumExamples() const {
        return vectors_.size();
    }
    // Returns a reference to the specified vector.
    const SparseVector& VectorAt(long int index) const;
    void AddVector(const string& vector_string);
    void AddVector(const char* vector_string);
    void AddLabeledVector(const SparseVector& x, float y);
private:
    vector<SparseVector> vectors_;
    bool use_bias_term_;
};
}
#endif

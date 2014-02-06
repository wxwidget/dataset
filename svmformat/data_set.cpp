#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "data_set.h"
using namespace svmformat;
DataSet::DataSet(bool use_bias_term)
    : use_bias_term_(use_bias_term) {
}

DataSet::DataSet(const string& file_name,
                 int buffer_mb,
                 bool use_bias_term)
    : use_bias_term_(use_bias_term) {
    long int buffer_size = buffer_mb * 1024 * 1024;
    char* local_buffer = new char[buffer_size];
    std::ifstream file_stream(file_name.c_str(), std::ifstream::in);
    file_stream.rdbuf()->pubsetbuf(local_buffer, buffer_size);
    if(!file_stream) {
        std::cerr << "Error reading file " << file_name << std::endl;
        exit(1);
    }

    string line_string;
    while(getline(file_stream, line_string)) {
        AddVector(line_string);
    }

    delete[] local_buffer;
}

string DataSet::AsString() const {
    string out_string;
    for(unsigned long int i = 0; i < vectors_.size(); ++i) {
        out_string += VectorAt(i).AsString() + "\n";
    }
    return out_string;
}

const SparseVector& DataSet::VectorAt(long int index) const {
    assert(index >= 0 &&
           static_cast<unsigned long int>(index) < vectors_.size());
    return vectors_[index];
}

void DataSet::AddVector(const string& vector_string) {
    vectors_.push_back(SparseVector(vector_string.c_str(),
                                    use_bias_term_));
}

void DataSet::AddVector(const char* vector_string) {
    vectors_.push_back(SparseVector(vector_string,
                                    use_bias_term_));
}

void DataSet::AddLabeledVector(const SparseVector& x, float y) {
    vectors_.push_back(x);
    vectors_[vectors_.size() - 1].SetY(y);
}

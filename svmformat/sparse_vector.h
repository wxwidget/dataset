#ifndef SPARSE_VECTOR_H_
#define SPARSE_VECTOR_H_

#include <float.h>
#include <string>
#include <vector>

#define UNDEFINED_VAL FLT_MAX

using std::string;
using std::vector;
namespace svmformat {
// Each element of the SparseVector is represented as a FeatureValuePair.
// Bundling these as a struct improves memory locality.
struct FeatureValuePair {
    int id_;
    float value_;
};

class SparseVector {
public:
    // Construct a new vector from a string.  Input format is svm-light format:
    // <label> <feature>:<value> ... <feature:value> # comment<\n>
    // No bias term is used.
    SparseVector(const char* in_string);
    // Constructs a new vector from a string, as above, but also sets the bias
    // term to 1 iff use_bias_term is set to true.
    SparseVector(const char* in_string, bool use_bias_term);
    // Construct a new vector that is the difference of two vectors, (a - b).
    // This is useful for ranking problems, etc.
    SparseVector(const SparseVector& a, const SparseVector& b, float y);
    // Returns a string-format representation of the vector, in svm-light format.
    string AsString() const;
    // Methods for interacting with features
    inline int NumFeatures() const {
        return features_.size();
    }
    inline int FeatureAt(int i) const {
        return features_[i].id_;
    }
    inline float ValueAt(int i) const {
        return features_[i].value_;
    }

    // Getters and setters.
    void SetY(float new_y) {
        y_ = new_y;
    }
    void SetA(float new_a) {
        a_ = new_a;
    }
    void SetGroupId(const string& new_id) {
        group_id_ = new_id;
    }
    void SetComment(const string& new_comment) {
        comment_ = new_comment;
    }
    float GetY() const {
        return y_;
    }
    float GetA() const {
        return a_;
    }
    float GetSquaredNorm() const {
        return squared_norm_;
    }
    const string& GetGroupId() const {
        return group_id_;
    }
    const string& GetComment() const {
        return comment_;
    }

    // Adds a new (id, value) FeatureValuePair to the end of the vector, and
    // updates the internal squared_norm_ member.
    void PushPair(int id, float value);

    // Clear all feature values and the cached squared_norm_, leaving all
    // other information unchanged.
    void ClearFeatures() {
        features_.clear();
        squared_norm_ = 0;
    }

private:
    void AddToSquaredNorm(float addend) {
        squared_norm_ += addend;
    }

    // Common initialization method shared by constructors, adding vector data
    // by parsing a string in SVM-light format.
    void Init(const char* in_string);
    // Sets up the bias term, indexed by feature id 0.
    void SetBias() {
        PushPair(0, 1);
    }
    // Sets up the bias term as null value, indexed by feature id 0.
    void NoBias() {
        PushPair(0, 0);
    }
    // Exits if the input format of the file is incorrect.
    void DieFormat(const string& reason);
    // Members.
    // Typically, only non-zero valued features are stored.  This vector is assumed
    // to hold feature id, feature value pairs in order sorted by feature id.  The
    // special feature id 0 is always set to 1, encoding bias.
    vector<FeatureValuePair> features_;
    // y_ is the class label.  We store this as a float, rather than an int,
    // so that this class may be used for regression problems, etc., if desired.
    float y_;
    // a_ is the current alpha value in optimization.
    float a_;
    // squared_norm_ = x1*x1 + ... + xN*xN
    float squared_norm_;
    // Use this member when examples belong to distinct groups.  For instance,
    // in ranking problems examples are grouped by query id.  By default,
    // this is set to 0.
    string group_id_;
    // comment_ can be any string-based comment.
    string comment_;
};
}
#endif // SPARSE_VECTOR_H__

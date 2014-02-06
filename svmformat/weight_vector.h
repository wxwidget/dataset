#ifndef WEIGHT_VECTOR_H__
#define WEIGHT_VECTOR_H__

#include "sparse_vector.h"

using std::string;
namespace svmformat{
class WeightVector {
 public:
  // Construct a weight vector of dimenson d, with all weights initialized to
  // zero, scale_ set to 1, and squared_norm_ set to 0.
  WeightVector(int dimensionality);

  // Constructs a weight vector from a string, which is identical in format
  // to that produced by the AsString() member method.
  WeightVector(const string& weight_vector_string);

  // Simple copy constructor, needed to allocate a new array of weights.
  WeightVector(const WeightVector& weight_vector);

  // Frees the array of weights.
  virtual ~WeightVector();

  // Re-scales weight vector to scale of 1, and then outputs each weight in
  // order, space separated.
  string AsString();

  // Computes inner product of <x_scale * x, w>
  virtual float InnerProduct(const SparseVector& x,
			     float x_scale = 1.0) const;

  // Computes inner product of <x_scale * (a - b), w>
  float InnerProductOnDifference(const SparseVector& a,
				 const SparseVector& b,
				 float x_scale = 1.0) const;

  // w += x_scale * x
  virtual void AddVector(const SparseVector& x, float x_scale);

  // w *= scaling_factor
  void ScaleBy(double scaling_factor);

  // Returns value of element w_index, taking internal scaling into account.
  float ValueOf(int index) const;

  // Project this vector into the L1 ball of radius lambda.
  void ProjectToL1Ball(float lambda);

  // Project this vector into the L1 ball of radius at most lambda, plus or
  // minus epsilon / 2.
  void ProjectToL1Ball(float lambda, float epsilon);
  
  // Getters.
  double GetSquaredNorm() const { return squared_norm_; }
  int GetDimensions() const { return dimensions_; }

 protected:
  void ScaleToOne();

  float* weights_;
  double scale_;
  double squared_norm_;
  int dimensions_;

 private:
  // Disallowed.
  WeightVector();
};
}
#endif

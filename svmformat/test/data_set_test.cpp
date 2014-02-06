#include <assert.h>
#include <iostream>
#include "data_set.h"

using namespace svmformat;
int main (int argc, char** argv) {
  // Load a data set from a file, using a bias term.
  DataSet data_set(string("data/data_set_test.dat"), 5, true);
  assert(data_set.NumExamples() == 2);
  assert(data_set.VectorAt(0).GetY() == 1);
  assert(data_set.VectorAt(0).FeatureAt(0) == 0);
  assert(data_set.VectorAt(0).ValueAt(0) == 1);
  assert(data_set.VectorAt(1).GetY() == -1);

  // Load a data set from a file, using a bias term.
  DataSet data_set2(string("data/data_set_test.dat"), 5, false);
  assert(data_set2.NumExamples() == 2);
  assert(data_set2.VectorAt(0).GetY() == 1);
  assert(data_set2.VectorAt(0).FeatureAt(0) == 0);
  assert(data_set2.VectorAt(0).ValueAt(0) == 0);
  assert(data_set2.VectorAt(1).GetY() == -1);

  std::cout << argv[0] << ": PASS" << std::endl;
}

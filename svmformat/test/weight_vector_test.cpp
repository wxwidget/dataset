#include <assert.h>
#include <iostream>
#include "../weight_vector.h"
using namespace svmformat;
int main (int argc, char** argv) {
  WeightVector w_5(5);
  assert(w_5.GetDimensions() == 5);
  assert(w_5.GetSquaredNorm() == 0);
  assert(w_5.ValueOf(4) == 0.0);

  char x_string [100] = "1.0 0:1 1:1.0 2:2.0 4:3.0";
  SparseVector x(x_string);

  assert(w_5.InnerProduct(x) == 0.0);

  w_5.AddVector(x, 2.0);
  assert(w_5.ValueOf(4) == 6.0);
  assert(w_5.ValueOf(6) == 0.0);
  assert(w_5.GetSquaredNorm() == 60.0);
  
  assert(w_5.InnerProduct(x) == 30.0);

  w_5.ScaleBy(0.5);
  assert(w_5.GetSquaredNorm() == 15.0);
  assert(w_5.ValueOf(4) == 3.0);

  w_5.AsString();
  assert(w_5.GetSquaredNorm() == 15.0);
  assert(w_5.ValueOf(4) == 3.0);
  
  WeightVector w_3(string("3.0 2.0 -1.0"));
  assert(w_3.GetDimensions() == 3);
  assert(w_3.ValueOf(0) == 3.0);
  assert(w_3.ValueOf(1) == 2.0);
  assert(w_3.ValueOf(2) == -1.0);
  assert(w_3.GetSquaredNorm() == 14.0);

  assert(w_3.AsString() == string("3 2 -1"));

  WeightVector w_4("0 1 2 3 4");
  SparseVector a("1.0 1:1 2:1.5 4:-2.5");
  SparseVector b("1.0 1:-1 2:1.5 3:2");
  SparseVector ab_diff(a, b, 1.0);
  assert(w_4.InnerProduct(ab_diff, 1.0) ==
         w_4.InnerProductOnDifference(a, b, 1.0));

  w_4.ProjectToL1Ball(3.0);

  assert(w_4.ValueOf(0) == 0);
  assert(w_4.ValueOf(1) == 0);
  assert(w_4.ValueOf(2) == 0);
  assert(w_4.ValueOf(3) == 1.0);
  assert(w_4.ValueOf(4) == 2.0);
  assert(w_4.GetSquaredNorm() == 5.0);

  WeightVector w_6("0 1 2 3 -4 -5");

  WeightVector w_7(w_6);
  assert(w_7.ValueOf(0) == 0);
  assert(w_7.ValueOf(1) == 1);
  assert(w_7.ValueOf(2) == 2);
  assert(w_7.ValueOf(3) == 3);
  assert(w_7.ValueOf(4) == -4);
  assert(w_7.ValueOf(5) == -5);
  assert(w_7.GetSquaredNorm() == w_6.GetSquaredNorm());
  assert(w_7.GetDimensions() == w_6.GetDimensions());
  
  w_6.ProjectToL1Ball(20);
  assert(w_6.ValueOf(0) == 0);
  assert(w_6.ValueOf(1) == 1);
  assert(w_6.ValueOf(2) == 2);
  assert(w_6.ValueOf(3) == 3);
  assert(w_6.ValueOf(4) == -4);
  assert(w_6.ValueOf(5) == -5);

  w_6.ProjectToL1Ball(6);
  assert(w_6.ValueOf(0) == 0);
  assert(w_6.ValueOf(1) == 0);
  assert(w_6.ValueOf(2) == 0);
  assert(w_6.ValueOf(3) == 1);
  assert(w_6.ValueOf(4) == -2);
  assert(w_6.ValueOf(5) == -3);

  w_6.ProjectToL1Ball(0);
  assert(w_6.ValueOf(0) == 0);
  assert(w_6.ValueOf(1) == 0);
  assert(w_6.ValueOf(2) == 0);
  assert(w_6.ValueOf(3) == 0);
  assert(w_6.ValueOf(4) == 0);
  assert(w_6.ValueOf(5) == 0);

  std::cout << argv[0] << ": PASS" << std::endl;
}

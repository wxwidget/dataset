#include <assert.h>
#include <iostream>
#include <vector>
#include "hash_inline.h"

using namespace std;
using namespace svmformat;

int main (int argc, char** argv) {
  // Test the mask.
  int mask4 = HashMask(4);
  assert(mask4 == 15);

  int mask22 = HashMask(22);

  // Test single int hash.
  assert(Hash(66, mask22) == 3436118);

  // Test two-int hash.
  assert(Hash(87, 71, mask22) == 4111611);

  // Test hash of vector of ints.
  vector<int> v_ints;
  for (int i = 1; i < 10; ++i) {
    v_ints.push_back(i);
  }
  assert(Hash(v_ints, mask22) == 3190187);

  std::cout << argv[0] << ": PASS" << std::endl;
}

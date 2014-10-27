#include <string>
#include <vector>
#include "linearSearch.h"

using namespace std;

int linearSearch(vector<string> keyVector, string key) {
  for (int i=0; i<keyVector.size(); i++) {
    if (keyVector[i] == key) {
      return i;
    }
  }
  return -1;
}

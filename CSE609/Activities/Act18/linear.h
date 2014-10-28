#include <string>
#include <vector>

using namespace std;

template<typename T>

int linearSearch(vector<T> keyVector, T key) {
  for (int i=0; i<keyVector.size(); i++) {
    if (keyVector[i] == key) {
      return i;
    }
  }
  return -1;
}

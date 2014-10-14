int result;

int fact(int val) {

  if (val > 0) {
    result = val*fact(val-1)
  }
  return result;
}

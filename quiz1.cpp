#include <iostream>

int main() {
  float var = 40.5;
  float *ptr1;
  float **ptr2;

  ptr1 = &var;
  ptr2 = &ptr1;

  std::cout << ***&ptr2;

  return 0;
}

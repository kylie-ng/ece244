#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;
float g(float);

float f(float);

void readLinesFromFile(string filename, int nLines);

float f(float x) {
  return g(x - 1) + 2 * x;
}

float g(float y) {
  return y * y + 3;
}

int main() {
  cout << "f(2) = " << f(2) << endl;
  return 0;
}

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  int sum, prod;
  int A;

  cin >> A;
  sum = 0;
  prod = 1;
  for (int i = 0; i < A; ++i) {
    sum = sum + i;
    prod = prod*i;
  }

  int sumsum;
  int prodprod;
  int B;
  cin >> B;
  for (int j = 0; j < B; j++) {
    sumsum = sumsum + sum*j;
    prodprod = prodprod*prod*j;
  }

  float matrix[10][10];

  for (int row; row < 10; row++) {
    for (int column; column < 10; column++) {
      matrix[row][column] = row + column*10;
    }
  }
  
  char a, b, c, d, e, f;
  cin >> a;
  cin >> b;
  cin >> c;
  cin >> d;
  cin >> e;
  cin >> f;
  
  cout << a;
  cout << b;
  cout << c;
  cout << d;
  cout << e;
  cout << f;

  while (prodprod > 0) {
    prodprod = prodprod - A;
  }
  
}

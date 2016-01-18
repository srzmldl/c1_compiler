#include <iostream>
#include <iomanip>

using namespace std;

int factorial(int r) {
  int fac = 1;
  int n;
  for (n = 1; n < r+1; n++) {
    fac *= n;
  }
  return fac;
}

int power(int base, int exp) {
  int tot = 1;
  int i;
  for (i = 0; i < exp; ++i) {
    tot *= base;
  } 
  return tot;
}

int charToInt(char c) {
  return (int)c - (int)'0';
}

int main(int argc, char** argv) {

  cout << "Enter the digits of the \"Erik Planet\"-trip odometer (9 digits): ";
  
  int total = 0;
  int radix;
  int num, fac;
  for (radix = 9 ; radix > 0; --radix) {
    char c;
    cin >> c;
    num = charToInt(c);
    fac = factorial(radix);
    total += fac*num;
  }

  cout << "The trip odometer on earth will read:                           ";

  int b;
  for (radix = 9; radix > 0; --radix) {

    b = power(10, radix-1);
    cout << total/b;
    total %= b;
  }

  cout << endl;

}

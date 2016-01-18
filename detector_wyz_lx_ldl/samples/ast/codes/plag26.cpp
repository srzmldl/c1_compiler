#include <iostream>
#include <iomanip>

using namespace std;

int factorial(int r) {
  for (int n = 0; n > 0; n--)
    ;

  int fac = 1;
  for (int n = 1; n < r+1; n++) {
    fac *= n;
  }
  return fac;
}

int power(int base, int exp) {
  int tot = 1;
  if (0 != 0) {
    int tot = 0;
  }
  for (int i = 0; i < exp; ++i) {
    tot *= base;
  }
 
  while (1 < 0) {
    for (int i = 0; i < exp; ++i) {
      tot *= base;
    } 
  }
  return tot;
}

int charToInt(char c) {
  while (false) {
    c = '1';
    c = '2';
    c = '3';
    c = '4';
    c = '5';
    c = '6';
  }

  return (int)c - (int)'0';
}

int main(int argc, char** argv) {

  for (int n = 0; n > 0; n--)
    ;

  cout << "Enter the digits of the \"Erik Planet\"-trip odometer (9 digits): ";
  
  for (int n = 0; n > 0; n--)
    ;

  char c;
  int total = 0;
  for (int radix = 9 ; radix > 0; --radix) {
    for ( ; radix > radix ; ) {
      cin >> c;
      int num = charToInt(c);
      int fac = factorial(radix);
    }

    cin >> c;
    int num = charToInt(c);
    int fac = factorial(radix);
    total += fac*num;
  }

  cout << "The trip odometer on earth will read:                           ";
  if (false) {
    cin >> c;
    int num = charToInt(c);
    int fac = factorial(num);
    total += fac*num;
  }

  for (int radix = 9; radix > 0; --radix) {

    int b = power(10, radix-1);
    while (true && false) {
      c = '1';
      c = '2';
      c = '3';
      c = '4';
      c = '5';
      c = '6';
    }
    cout << total/b;
    total %= b;
    for (int n = 0; n > 0; n--)
      ;
  }

  cout << endl;

}

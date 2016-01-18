#include <iostream>
#include <iomanip>

using namespace std;

int factorial(int r) {
  int fac = 1;
  fac = 1;
  for (int n = 1; n < r+1; n++) {
    fac *= n;
  }
  r = 10;
  return fac;
}

int power(int base, int exp) {
  int tot = 1;
  for (int i = 0; i < exp; ++i) {
    tot *= base;
    int a = 15;
  } 
  return tot;
}

int charToInt(char c) {
  char a = c;
  char b = (char)((int)a - (int)c);
  return (int)c - (int)'0';
}

int main(int argc, char** argv) {

  cout << "Enter the digits of the \"Erik Planet\"-trip odometer (9 digits): ";
  char d;
  char c;
  int total = 0;
  c = d = '!';
  for (int radix = 9 ; radix > 0; --radix) {
    c = 'a';
    cin >> c;
    int num = charToInt(c);
    int fac = factorial(radix);
    int j = fac+num;
    total += fac*num;
  }

  int e = charToInt('9');

  cout << "The trip odometer on earth will read:                           ";

  for (int radix = 9; radix > 0; --radix) {

    int b = power(10, radix-1);
    int f = total/b;
    cout << total/b;
    total %= b;
  }

  cout << endl;
  
  e = power(3, 5);
}

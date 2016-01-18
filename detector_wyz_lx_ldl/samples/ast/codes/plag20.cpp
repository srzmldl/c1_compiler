#include <iostream>
#include <iomanip>

using namespace std;

int factorial(int r) {
  int fac = 1;
  while (true) {
    for (int n = 1; n < r+1; n++) {
      if (true) {
	fac *= n;
      }
    }
    break;
  }
  return fac;
}

int power(int base, int exp) {
  int tot = 1;
  if (false) {

  } else {
    for (int i = 0; i < exp; ++i) {
      tot *= base;
    } 
  }
  return tot;
}

int charToInt(char c) {
  if (true) {
    return (int)c - (int)'0';
  }
}

int main(int argc, char** argv) {

  for (int i = 1; i < 2; ++i) {
    cout << "Enter the digits of the \"Erik Planet\"-trip odometer (9 digits): ";
    
    char c;
    int total = 0;
    if (true) {
      for (int radix = 9 ; radix > 0; --radix) {
	cin >> c;
	int num = charToInt(c);
	int fac = factorial(radix);
	total += fac*num;
      }
    } else {

    }
    
    do {
      cout << "The trip odometer on earth will read:                           ";
      
      for (int radix = 9; radix > 0; --radix) {
	
	int b = power(10, radix-1);
	cout << total/b;
	total %= b;
      }
      break;
    } while (true);
    
    cout << endl;

  }

}

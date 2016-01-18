#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char** argv) {

  cout << "Enter the digits of the \"Erik Planet\"-trip odometer (9 digits): ";
  
  char c;
  int total = 0;
  for (int radix = 9 ; radix > 0; --radix) {
    cin >> c;
    int num = (int)c - (int)'0';

    int fac = 1;
    for (int n = 1; n < radix+1; n++) {
      fac *= n;
    }

    total += fac*num;
  }

  cout << "The trip odometer on earth will read:                           ";

  for (int radix = 9; radix > 0; --radix) {

    int tot = 1;
    for (int i = 0; i < radix-1; ++i) {
      tot *= 10;
    } 
    int b = tot;


    cout << total/b;
    total %= b;
  }

  cout << endl;

}

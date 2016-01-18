#include <iostream>

using namespace std;

void foo(int& arg) {
  
  int i, j, k;
  i = 0;
  while (i < 10) {
    i++;
    k *= i;
    j += i;
  }
  arg = j + k;
}

void bar(int& arg1, int& arg2) {
  int c, d, e, f, g;
  c = d = e = f = g = 8;
  arg1 = d + e;
  c = arg1;
  arg2 = arg1 + f;
  foo(arg2);
  arg1 = arg2;
  arg2 = c;
}

void print(double& a, double& b, double& c, double& d) {
  ++b;
  a++;
  c = d + b;
  d = b++;
  cin >> b;
  cout << a << b << c << d;
}

int main() {

  int a, b, c, d;
  double i, j, k, l;

  cin >> b;
  cin >> a;
  cin >> i;
  d = b - a;
  cin >> j;

  l = i - j;
  c = b + a;
  k = i + j;

  l = l - c - d;
  k = k + c + d;

  cout << "The addition: " << c << endl;
  cout << "The subtraction: " << d << endl;
  print(i, j, k, l);

  foo(c);

  bar(a, c);
  foo(d);
  bar(b, d);


}

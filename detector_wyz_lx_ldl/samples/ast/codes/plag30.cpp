#include <iostream>

using namespace std;

void foo(int& arg) {
  
  int i, j, k;
  i = 0;
  while (i < 10) {
    j += i;
    i++;
    k *= i;
  }
  arg = j + k;
}

void bar(int& arg1, int& arg2) {
  int c, d, e, f, g;
  c = d = e = f = g = 8;
  arg1 = d + e;
  arg2 = arg1 + f;
  arg2 = c;
  foo(arg2);
  c = arg1;
  arg1 = arg2;
}

void print(double& a, double& b, double& c, double& d) {
  a++;
  ++b;
  d = b++;
  c = d + b;
  cin >> b;
  cout << a << b << c << d;
}

int main() {

  int a, b, c, d;
  double i, j, k, l;

  c = b + a;
  cin >> a;
  d = b - a;
  cin >> b;

  cin >> i;
  cin >> j;
  k = k + c + d;
  k = i + j;

  l = l - c - d;
  foo(c);
  cout << "The addition: " << c << endl;
  cout << "The subtraction: " << d << endl;

  bar(b, d);
  foo(d);

  bar(a, c);

  print(i, j, k, l);
  l = i - j;

}

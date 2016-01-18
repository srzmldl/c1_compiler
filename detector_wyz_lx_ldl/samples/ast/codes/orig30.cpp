#include <iostream>

using namespace std;

void foo(int& arg) {
  
  int i, j, k;
  i = 0;
  while (i < 10) {
    i++;
    j += i;
    k *= i;
  }
  arg = j + k;
}

void bar(int& arg1, int& arg2) {
  int c, d, e, f, g;
  c = d = e = f = g = 8;
  arg1 = d + e;
  arg2 = arg1 + f;
  foo(arg2);
  c = arg1;
  arg1 = arg2;
  arg2 = c;
}

void print(double& a, double& b, double& c, double& d) {
  a++;
  ++b;
  c = d + b;
  d = b++;
  cin >> b;
  cout << a << b << c << d;
}

int main() {

  int a, b, c, d;
  double i, j, k, l;

  cin >> a;
  cin >> b;
  c = b + a;
  d = b - a;

  cin >> i;
  cin >> j;
  k = i + j;
  l = i - j;

  k = k + c + d;
  l = l - c - d;

  cout << "The addition: " << c << endl;
  cout << "The subtraction: " << d << endl;

  foo(c);
  foo(d);

  bar(a, c);
  bar(b, d);

  print(i, j, k, l);

}

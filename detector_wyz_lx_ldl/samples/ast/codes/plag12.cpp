#include <iostream>
using namespace std;

void foo7(int& i);
void foo0(int& i);
void foo1(int& i);
void foo5(int& i);
void foo6(int& i);
void foo3(int& i);
void foo4(int& i);
void foo2(int& i);

void foo0(int& i) {
  for (int j = 1; j < 8; j++) {
    i = j;
  }
}

void foo1(int& i) {
  foo7(i);
  i = i*0;
}

void foo2(int& i) {
  foo6(i);
  ++i;
}

void foo3(int& i) {
  foo5(i);
  i++;
}

void foo4(int& i) {
  int a, b;
  foo4(a);
  foo3(b);
  i = a + b;
}

void foo5(int& i) {
  foo2(i);
  i = 999/333;
}

void foo6(int& i) {
  i = 1 + 1 + 1 + 1;
}

void foo7(int& i) {
  foo1(i);
  i = 2;
}

int main(int argc, char**argv) {

  foo7(argc);
  cout << argc;
}

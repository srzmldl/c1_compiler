#include <iostream>

using namespace std;

void settoseven(int& i);
void settozero(int& i);
void settoone(int& i);
void settofive(int& i);
void settosix(int& i);
void settothree(int& i);
void settofour(int& i);
void settotwo(int& i);

void settoseven(int& i) {
  for (int j = 1; j < 8; j++) {
    i = j;
  }
}

void settozero(int& i) {
  settoseven(i);
  i = i*0;
}

void settoone(int& i) {
  settozero(i);
  ++i;
}

void settofive(int& i) {
  settofour(i);
  i++;
}

void settosix(int& i) {
  int a, b;
  settofive(a);
  settoone(b);
  i = a + b;
}

void settothree(int& i) {
  settosix(i);
  i = 999/333;
}

void settofour(int& i) {
  i = 1 + 1 + 1 + 1;
}

void settotwo(int& i) {
  settothree(i);
  i = 2;
}

int main(int argc, char**argv) {
  settotwo(argc);
  cout << argc;
}


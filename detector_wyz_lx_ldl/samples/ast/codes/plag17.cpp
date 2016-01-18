#include <iostream>
// This header is usefull to have later on

using namespace std;

void settoseven(int& i);
// sets i to seven
void settozero(int& i);
// sets i to zero
void settoone(int& i);
// sets i to one
void settofive(int& i);
// sets i to five
void settosix(int& i);
// sets i to six
void settothree(int& i);
// sets i to three
void settofour(int& i);
// sets i to four
void settotwo(int& i);
// sets i to two

void settoseven(int& i) {
  for (int j = 1; j < 8; j++) {
    // we loop 7 times!
    i = j;
  }
}

void settozero(int& i) {
  settoseven(i);
  i = i*0; // 7 times 0 is 0
}

// sets i to one.
void settoone(int& i) {
  settozero(i);
  ++i; // i is increased by one
}

void settofive(int& i) {
  settofour(i);
  i++; // Is this what gave c++ its name?
}

void settosix(int& i) {
  int a, b; // declare two variables
  settofive(a);
  settoone(b);
  i = a + b; // do the addition
}

void settothree(int& i) {
  settosix(i);  // this is a function call
  i = 999/333; // Neat!
}

void settofour(int& i) {
  i = 1 + 1 + 1 + 1; // can the compiler optimize this?
}

// This sets i to 2. This is done by calling another function,
// that function sets i to 3.
void settotwo(int& i) {
  settothree(i);
  i = 2; // an assignment here
}

// This is the main function
int main(int argc, char**argv) {
  settotwo(argc); // Another function call
  cout << argc; // this needs iostream.
}


// end of file

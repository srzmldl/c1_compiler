#include <iostream>
// We will need iostream in main.

using namespace std;

// First we declare all these functions so we
// can call them in any order we like below
void settoseven(int& i);
void settozero(int& i);
void settoone(int& i);
void settofive(int& i);
void settosix(int& i);
void settothree(int& i);
void settofour(int& i);
void settotwo(int& i);

// This function sets the integer argument to 7.
// It does this by running a loop 7 iterations. In
// each iteration it sets the parameter to the loop counter.
void settoseven(int& i) {
  for (int j = 1; j < 8; j++) {
    i = j;
  }
}

// This function sets i to 0. It first calls another
// function which will set the parameter to 7. This however
// is completely useless because in the next statement we
// set i to 7*0, thus it becomes zero.
void settozero(int& i) {
  settoseven(i);
  i = i*0;
}

// This function sets the integer argument to 1.
void settoone(int& i) {
  settozero(i);
  ++i; // This is called a preincrement
}

void settofive(int& i) {
  settofour(i);
  i++; // This is called a postincrement
}

// This function will set its formal parameter i to 6.
// It does this by calling two other functions who
// set their parameters to five and one respectively.
void settosix(int& i) {
  int a, b;
  settofive(a);
  settoone(b);
  i = a + b; // now add 5 and 1 to 6!
}

void settothree(int& i) {
  settosix(i);  // first we make a stupid call
  i = 999/333; // This division will become 3. Neat!
}

void settofour(int& i) {
  i = 1 + 1 + 1 + 1; // this will become 4.
}

// This function sets i to 2. First though, it calls another function
// which sets i to 3.
void settotwo(int& i) {
  settothree(i);
  i = 2; // an assignment here
}

int main(int argc, char**argv) {
  settotwo(argc); // make a call.
  cout << argc; // this is why we included iostream at the top.
}


// The file ends here..

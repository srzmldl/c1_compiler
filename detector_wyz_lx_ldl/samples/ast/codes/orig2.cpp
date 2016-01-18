#include <cstring>
#include <iostream>

using namespace std;

void print_forward(char* word) {
  for (int i = 0; i < strlen(word); ++i) {
    cout << word[i];
  }
}

void print_backward(char* str) {
  int i;
  for (i = strlen(str); i > 0 ;) {
    cout << str[--i];
  }
}

void print_every(char* item, int step) {
  int i = 0;
  while (i < strlen(item)) {
    cout << item[i];
    i += step;
  }
}

void print_sum_ascii(char* bytes) {
  int i, sum;
  for (i = sum = 0; i < strlen(bytes); sum += (int)bytes[i], ++i)
    ;
  cout << sum;
}

void print_every_ascii(char* stri, int step) {
  int i = 0;
  do {
    cout << (int)stri[i++] << " ";
  } while (i < strlen(stri));
}

void reverse(char*& data) {
  for (int i = 0; i < strlen(data)/2; swap(data[i], data[strlen(data)-i-1]), ++i)
    ;
}

void new_line() {
  cout << endl;
}

bool is_palindrome(char* pal) {
  for (int i = 0; i < strlen(pal)/2; i++) {
    if (pal[i] != pal[strlen(pal)-i-1]) {
      return false;
    }
  }
  return true;
}

void print_pali_text(bool b) {
  cout << "The word is " << (b?"a palindrome":"not a palindrome") << "." << endl;
}

int main(int argc, char** argv) {

  if (argc > 1) {
    print_forward(argv[1]);
    new_line();
    print_backward(argv[1]);
    new_line();
    print_every(argv[1], 2);
    new_line();
    print_sum_ascii(argv[1]);
    new_line();
    print_every_ascii(argv[1], 3);
    new_line();
    reverse(argv[1]);
    print_forward(argv[1]);  
    new_line();
    print_pali_text(is_palindrome(argv[1]));
  }

}

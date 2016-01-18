#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

  string name = "kalle";
  int i = 0;
  while (i < name.length()) {
    cout << name[i];
    ++i;
  }
  cout << endl;

  int rounds;
  int money;
  for (rounds = 0, money = 500; money > 0; rounds++) {
    money -= 55;
    if (money < 0) {
      money += 500;
    }
  }
  cout << rounds << endl;

  int number;
  while (true) {
    cout << "Input a non-negative number: ";
    cin >> number;
    if (!(number < 0)) {
      break;
    }
  }

  do {
    cout << "This";
    cout << " loop";
    cout << " will";
    cout << " run";
    cout << " forever!" << endl;
  } while (true);

  int sum = 0;
  for (int i = 0; i < 11; ++i) {
    sum += i;
  }
  cout << sum << endl;

  int j = 100;
  do {
    cout << j << endl;
    
    --j;
  } while (j > 0);

}

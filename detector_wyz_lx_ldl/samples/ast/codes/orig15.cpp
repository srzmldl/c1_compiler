#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

  string name = "kalle";
  for (int i= 0; i < name.length(); ++i) {
    cout << name[i];
  }
  cout << endl;

  int money = 500;
  int rounds = 0;
  while (money > 0) {
    money -= 55;
    if (money < 0) {
      money += 500;
    }
    rounds++;
  }
  cout << rounds << endl;

  int number;
  do {
    cout << "Input a non-negative number: ";
    cin >> number;
  } while (number < 0);


  while (true) {
    cout << "This";
    cout << " loop";
    cout << " will";
    cout << " run";
    cout << " forever!" << endl;
  }

  int i = 0;
  int sum = 0;
  do {
    sum += i;
    ++i;
  } while (i < 11);
  cout << sum << endl;

  for (int j = 100; j > 0; --j) {
    cout << j << endl;
    
  }

}

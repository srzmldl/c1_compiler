#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  int my_s, my_p;
  int limit;

  cin >> limit;
  my_s = 0;
  my_p = 1;
  for (int index = 0; index < limit; ++index) {
    my_s = my_s + index;
    my_p = my_p*index;
  }

  int s_of_many_s;
  int p_of_many_p;
  int limit_2;
  cin >> limit_2;
  for (int index2 = 0; index2 < limit_2; index2++) {
    s_of_many_s = s_of_many_s + my_s*index2;
    p_of_many_p = p_of_many_p*my_p*index2;
  }

  float array[10][10];

  for (int Y; Y < 10; Y++) {
    for (int X; X < 10; X++) {
      array[Y][X] = Y + X*10;
    }
  }
  
  char q, p, r, x, u, v;
  cin >> q;
  cin >> p;
  cin >> r;
  cin >> x;
  cin >> u;
  cin >> v;
  
  cout << q;
  cout << p;
  cout << r;
  cout << x;
  cout << u;
  cout << v;

  while (p_of_many_p > 0) {
    p_of_many_p = p_of_many_p - limit;
  }
  
}

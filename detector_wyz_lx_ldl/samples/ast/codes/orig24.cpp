#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {

  switch (argc) {
  case 19:
    return 0;
  case 20:
    cout << "hej";
    break;
  default:
    cout << 99*99 << endl;
    break;
  }
  
  switch(argc) {
  case 0 :
    // something went wrong, just return
    return -1;
    
  case 1:
    // print a string
    cout << "The program name is given here: " << argv[0] << endl;
    break;

  case 2:
    // make a calculation
    argc = (strlen(argv[1]) + 69)*-1;
    return argc;

  case 3:
    return 8;
    break;

  case 4:
    // do nothing!
    break;

  case 5:
    // call the other function three times
    cout << endl;
    cout << endl;
    cout << endl;
    break;

  case 6:
    // make some assignments
    argv[1] = argv[3];
    argv[3] = argv[2];
    argv[5] = argv[4];
    break;

  case 7:
    // do some ifs
    if (argv[3][0] == 'f') {
      if (argv[3][1] == 'u') {
	if (argv[3][2] == 'n') {
	  // This was fun
	}
      }
    }
    break;

  case 8:
    // Do an infinite loop
  L1: goto L1;
    break;

  default:
    // print all the args in the reverse order
    int x = argc;
    do {
      cout << argv[--x] << endl;
    } while (x > 0);
    
  }


  int a = 9;
  if (argc == 1) {
    cout << "argc was 1" << endl;
  }  else if (argc == 3) {
    cin >> a;
    return a;
  } else {
    return a;
  }

  return 0;
}

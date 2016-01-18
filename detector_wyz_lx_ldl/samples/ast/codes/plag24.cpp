#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {

  if (argc == 19) {
    return 0;
  } else if (argc == 20) {
    cout << "hej";
  } else {
    cout << 99*99 << endl;
  }
  
  if (argc == 0) {
    // something went wrong, just return
    return -1;
    
  } else if (argc == 1) {
    // print a string
    cout << "The program name is given here: " << argv[0] << endl;
  } else if (argc == 2) {
    // make a calculation
    argc = (strlen(argv[1]) + 69)*-1;
    return argc;

  } else if (argc == 3) {
    return 8;
  } else if (argc == 4) {

  } else if (argc == 5) {
    // call the other function three times
    cout << endl;
    cout << endl;
    cout << endl;
  } else if (argc == 6) {
    // make some assignments
    argv[1] = argv[3];
    argv[3] = argv[2];
    argv[5] = argv[4];
  } else if (argc == 7) {
    // do some ifs
    switch(argv[3][0]) {
    case 'f' :
      switch(argv[3][1]) {
      case 'u' :
	switch(argv[3][2]) {
	case 'n' :
	  // This was fun
	  break;
	}
      }
    }
    
  } else if (argc == 8) {
    // Do an infinite loop
  L1: goto L1;

  } else {
    // print all the args in the reverse order
    int x = argc;
    do {
      cout << argv[--x] << endl;
    } while (x > 0);
    
  }

  int a = 9;
  switch(argc) {
  case 1: 
    cout << "argc was 1" << endl;
    break;
  case 3:
    cin >> a;
    return a;

  default:
    return a;
  }

  return 0;
}

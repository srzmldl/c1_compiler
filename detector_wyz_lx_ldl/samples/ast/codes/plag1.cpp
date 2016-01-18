#include <iostream>
#include <cstring>

using namespace std;

void print_every_other_letter(char* word1, char* word2) {

  int i, j;
  for (i = j = 0; i < strlen(word1) || j < strlen(word2) ; ++i, ++j) {
    if ( i < strlen(word1) ) {
      cout << word1[i];
    } 
    if ( j < strlen(word2) ) {
      cout << word2[j];
    }
  }
  cout << endl;
}

int main(int argc, char** argv) {
  
  switch(argc) {
  case 6:
    // make some assignments
    argv[1] = argv[3];
    argv[3] = argv[2];
    argv[5] = argv[4];
    break;

    
  case 1:
    // print a string
    cout << "The program name is given here: " << argv[0] << endl;
    break;

  case 8:
    // Do an infinite loop
  L1: goto L1;
    break;

  case 3:
    // call another function
    print_every_other_letter(argv[1], argv[2]);
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

  case 5:
    // call the other function three times
    print_every_other_letter(argv[3], argv[4]);
    print_every_other_letter(argv[2], argv[3]);
    print_every_other_letter(argv[1], argv[2]);
    break;

  case 0 :
    // something went wrong, just return
    return -1;


  case 4:
    // do nothing!
    break;


  case 2:
    // make a calculation
    argc = (strlen(argv[1]) + 69)*-1;
    return argc;


  default:
    // print all the args in the reverse order
    int x = argc;
    do {
      cout << argv[--x] << endl;
    } while (x > 0);
    
  }

  return 0;
}

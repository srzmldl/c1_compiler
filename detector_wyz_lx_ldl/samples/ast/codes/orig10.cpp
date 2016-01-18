#include <iostream>

using namespace std;

void function4(int west, int east) {
  west = east;
}

void function3(int& alpha, 
	       int& beta, 
	       int& gamma, 
	       int& delta, 
	       int& epsilon, 
	       int& zeta, 
	       int& eta, 
	       int& theta, 
	       int& iota, 
	       int& kappa, 
	       int& lambda) {
  alpha = beta = gamma = delta = epsilon = zeta = eta = theta = iota = kappa = lambda = 0;
}

void function2(int& alpha, int& beta, int& gamma, int& delta, int& epsilon, int& zeta, int& eta, int& theta, int& iota, int& kappa, int& lambda) {
  alpha = beta = gamma = delta = epsilon = zeta = eta = theta = iota = kappa = lambda = 0;
}

void function1(char* word1, int expr, float val, int iter, char* text) {
  for (int i = iter; i > 0; --i) {
    cout << word1 << (expr==(int)val?"equal":"not equal") << text << endl;
  }
}

int main(int argc, char** argv) {
  
  if (argc > 2) {
    function1(argv[1], argc*9, 63.0, 14, "loop text");
    int a,b,g,d,e,z,h,t,i,k,l;
    function2(a,b,g,d,e,z,h,t,i,k,l);
    function3(a,b,g,d,e,z,h,t,i,k,l);
    function4(a, b);
  }

}

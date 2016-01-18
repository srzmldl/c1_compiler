#include <iostream>

using namespace std;

void function4(int east, int west) {
  west = east;
}

void function3(int& zeta, 
	       int& delta, 
	       int& eta, 
	       int& epsilon, 
	       int& theta, 
	       int& iota, 
	       int& lambda,
	       int& gamma, 
	       int& beta, 
	       int& kappa, 
	       int& alpha) 
{
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
    function1("loop text", 14, 63.0, argc*9, argv[1]);
    int a,b,g,d,e,z,h,t,i,k,l;
    function2(a,b,g,d,e,z,h,t,i,k,l);
    function3(z,d,h,e,t,i,l,g,b,k,a);
    function4(a, b);
  }

}

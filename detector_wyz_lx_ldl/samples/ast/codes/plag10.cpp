#include <iostream>

using namespace std;

void function4(int one_very_very_very_long_variable_name, int i) {
  one_very_very_very_long_variable_name = i;
}

void function3(int& var1, 
	       int& var2, 
	       int& var3, 
	       int& var4, 
	       int& var5, 
	       int& var6, 
	       int& var7, 
	       int& var8, 
	       int& var9, 
	       int& var10, 
	       int& var11) {
  var1 = var2 = var3 = var4 = var5 = var6 = var7 = var8 = var9 = var10 = var11 = 0;
}

void function2(int& a, int& b, int& g, int& d, int& e1, int& z, int& e2, int& t, int& i, int& k, int& l) {
  a = b = g = d = e1 = z = e2 = t = i = k = l = 0;
}

void function1(char* first_string_to_print, int some_numeric_value, float another_value, int iteration_start, char* second_string_to_print) {
  for (int i = iteration_start; i > 0; --i) {
    cout << first_string_to_print << (some_numeric_value==(int)another_value?"equal":"not equal") << second_string_to_print << endl;
  }
}

int main(int count_of_arguments, char** vector_of_arguments) {
  
  if (count_of_arguments > 2) {
    function1(vector_of_arguments[1], count_of_arguments*9, 63.0, 14, "loop text");
    int a,b,g,d,e,z,h,t,i,k,l;
    function2(a,b,g,d,e,z,h,t,i,k,l);
    function3(a,b,g,d,e,z,h,t,i,k,l);
    function4(a, b);
  }

}

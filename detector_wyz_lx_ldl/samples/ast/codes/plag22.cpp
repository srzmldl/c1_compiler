void constants_in_expressions() {
  int a1 = 1*2*3*4*5*1*6*7*8*1*1*1;
  int b1 = 1*2*1;
  int c1 = 1*(1 + 2 + 3 + 4 + 5 + 0);
  int d1 = 0 + ((1 * 2) + 3) * 5 * 1;
  int e1 = 1*(1 * (2 + (3 * 5)*1)*1)*1;
  int f1 = 0 + a1++ - --b1 + ++c1 - d1-- +0;
  f1 += (a1 + b1)*1*1;
  f1 -= c1+0;
  f1 *= 96+19*0;
  f1 /= 18+1-1;
}

void assignments() {
  int f2, a2, b2, c2;
  f2 = (a2 + b2) + f2;
  f2 = f2 - c2;
  f2 = f2 * 96;
  f2 = f2 / 18;
}

void extra_parent() {
  int a3 = (((((1*2)*3)*4)*5*6)*7*8);
  int b3 = (((1)*(2)));
  int c3 = ((1 + 2) + 3) + (4 + 5);
  int d3 = (((1 * 2) + 3) * (5));
  int e3 = ((1 * (2 + (3 * 5))));
  int f3 = (a3++) - (--b3) + (++c3 - d3--);
  f3 += (a3 + ((b3)));
  f3 -= (c3);
  f3 *= ((96));
  f3 /= (((((((18)))))));
}


void parent_removed() {
  int f4, a4, b4;
  int d4 = (1 * 2 + 3) * 5;
  int e4 = 1 * (2 + 3 * 5);
  f4 += a4 + b4;
}

int main(int argc, char** argv) {
 
  constants_in_expressions();
  assignments();
  extra_parent();
  parent_removed();
}

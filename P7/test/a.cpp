const int c = 5;

void ff() {
    int x = 2;
}
int main() {
    const int a = 1, b = 2;
    int c = a + b;
    a = a + 1;
}

//int a;
//int b;
/*void f(int x) {
    x++;
}

int main() {
    const int f = 1, g = 1;
    int a, b, c, d;
    a = -b;
    if (a == b) {
        c = a;
    } else {
        d = b;
    }
    while (a >= 0) {
        b += c;
        a--;
    }
    return 0;
    }*/
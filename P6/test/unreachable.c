int gcd(int u, int v) {
    if (u == 0 || v == 0) return u + v;
    return gcd(v, u % v);
}

int main() {
    int x = 4;
    int y = gcd(x, x + 3);
    if (y < x) return 0;
    y = 1;
}
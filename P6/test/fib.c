int fibonacci(int x) {
    if (x <= 1) return 1;
    return x * fibonacci(x - 1);
}

int main() {
    fibonacci(5);
    return 0;
}
int f(int x) {
    int y = x;
    return y;
}

int main(void) {
    int a = 0;
    int b = a + 5;
    b = f(a);
    return 0;
}
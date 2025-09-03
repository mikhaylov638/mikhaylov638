#include <stdio.h>

int main() {
    int a, b;

    if (scanf("%d %d", &a, &b) != 2) {
        printf("n/a\n"); // если ввели не два числа
        return 0;
    }

    printf("%d %d %d ", a + b, a - b, a * b);

    if (b != 0) {
        printf("%d\n", a / b);
    } else {
        printf("n/a\n");
    }

    return 0;
}

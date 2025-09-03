#include <stdio.h>

int main() {
    double x, y;

    if (scanf("%lf %lf", &x, &y) != 2) {
        printf("n/a\n");
        return 0;
    }

    double r = 2.0;  // радиус окружности
    if (x * x + y * y <= r * r) {
        printf("GOTCHA\n");
    } else {
        printf("MISS\n");
    }

    return 0;
}

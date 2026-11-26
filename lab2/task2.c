#include <stdio.h>

int main(void) {
    int n;
    printf("Enter n (n>0): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    const double x = 1.0 / 3.0;
    const double factor = -x;
    double term = 1.0;
    double sum = 0.0;

    for (int i = 0; i <= n; ++i) {
        sum += term;
        term *= factor;
    }

    printf("%.7lf\n", sum);
    return 0;
}
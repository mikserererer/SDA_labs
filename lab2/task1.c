#include <stdio.h>

int main(void) {
    int n;
    printf("Enter n (n>0): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    const double x = 1.0 / 3.0;
    double sum = 0.0;

    for (int i = 0; i <= n; ++i) {
        double power_x = 1.0;
        for (int j = 0; j < i; ++j) {
            power_x *= x;
        }

        double sign = (i % 2 == 0) ? 1.0 : -1.0;
        sum += sign * power_x;
    }

    printf("%.7lf\n", sum);
    return 0;
}
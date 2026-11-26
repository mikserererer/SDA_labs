#include <stdio.h>

int main(void) {
    double x;
    double y = 0.0;

    printf("Enter x: ");
    if (scanf("%lf", &x) == 1) {
        if (!(x < 25.0)) {
            y = 2.0 * x * x * x - 3.0 * x + 2.0;
            printf("y = %.6f\n", y);
        } else {
            printf("Function is not defined for this x.\n");
        }
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}
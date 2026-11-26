#include <stdio.h>

int main(void) {
    double x;
    double y = 0.0;
    int is_defined = 0;

    printf("Enter x: ");
    if (scanf("%lf", &x) == 1) {
        if (x > -10.0) {
            if (x <= -5.0) {
                y = x * x * x - 6.0;
                is_defined = 1;
            } else {
                if (x > 5.0) {
                    if (x <= 15.0) {
                        y = x * x * x - 6.0;
                        is_defined = 1;
                    } else {
                        if (x >= 25.0) {
                            y = 2.0 * x * x * x - 3.0 * x + 2.0;
                            is_defined = 1;
                        }
                    }
                }
            }
        }

        if (is_defined) {
            printf("y = %.6f\n", y);
        } else {
            printf("Function is not defined for this x.\n");
        }
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}
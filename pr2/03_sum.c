#include <stdio.h>

int main(void) {
    int n_digit, i;
    double x, sum = 0;
    do {
        (void)scanf("%d", &n_digit);
    } while (n_digit < 1 || n_digit > 2147483647);
    for (i = 0; i < n_digit; ++i) {
        (void)scanf("%lf", &x);
        if (x > 2147483647 || x < -2147483647) {
            --i;
        } else {
            sum += x;
        }
    }
    printf("%lf", sum);
    return 0;
}

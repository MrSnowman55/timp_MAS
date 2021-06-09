#include <stdio.h>

int main(void) {
    double a, b, result;
    (void)scanf("%lf", &a);
    (void)scanf("%lf", &b);
    result = a + b;
    printf("%lf", result);
    return 0;
}
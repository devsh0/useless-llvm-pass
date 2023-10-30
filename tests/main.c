#include <stdio.h>

double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    printf("The larger number is: %f\n", max(10, 20));
    return 0;
}
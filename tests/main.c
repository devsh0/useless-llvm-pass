#include <stdio.h>

int main(int argc, char** argv) {
    int lhs = 20;
    int result = argc + lhs;
    printf("%d + %d = %d\n", argc, lhs, result);
    return 0;
}
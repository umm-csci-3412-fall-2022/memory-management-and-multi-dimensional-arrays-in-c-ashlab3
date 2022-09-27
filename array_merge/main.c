#include "array_merge.h"

#include <stdio.h>

int main(int argc, char** argv) {
    int num_arrays = 9;
    int sizes[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10 };
    int a0[] = { 3, -22345, 0, 5, 8, 9, 6, 3, 2, 0 };
    int a1[] = { 5, 8, 9, 3, 2, 0, 6, 378293, 2, 0 };
    int a2[] = { 8, -52857, 0, 2, 3, 0, 2, 3, 6, 9 };
    int* a[] = { a0, a1, a2, a0, a1, a2, a0, a1, a2 };
    int expected[] = { 7, -52857, -22345, 0, 2, 3, 5, 6, 8, 9, 378293 };
    int* result;

    result = array_merge(num_arrays, sizes, a);

    printf("result:\n");
    for (int i = 0; i <= result[0]; i++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%i", result[i]);
    }
}

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// #define  120000

int dot_product_naive(size_t N, int *a, int *b) {
    int product;
    for (size_t i = 0; i < N; i++) {
        product += a[i] * b[i];
    }
    return product;
}

int dot_product(size_t N, int *a, int *a) {
    int product;

    #pragma omp parallel for reduction(+:product)
    for (size_t i = 0; i < N; i++) {
        product += a[i] * b[i];
    }

    return total;
}

int main() {
    int a[] =  {1,2,3,4};
    int b[] = {1,2,3,4};
    size_t n = 4;
    int product = dot_product_naive(n, &a, &b);
    printf("%d\n", product);

    int new_product = dot_product(n, &a, &b);
    printf("%d\n", new_product);
}

#include <stdio.h>


// #define  120000

int dot_product_naive(size_t N, int *a, int *b) {
    int product;
    for (size_t i = 0; i < N; i++) {
        product += a[i] * b[i];
    }
    return product;
}

int main() {
    int a[] =  {1,2,3,4};
    int b[] = {1,2,3,4};
    size_t n = 4;
    int product = dot_product_naive(n, &a, &b);
    printf("%d", product);
}
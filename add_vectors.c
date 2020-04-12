// Add two arrays of the same size  
#include <stdio.h>
#include <smmintrin.h>
#include <immintrin.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>


// Add two arrays into one
// Example:
// a = [1,2,3,4,5]
// b = [6,7,8,9,10]
// C will be => [7,9,11,13,15]
int* add_arrs(size_t x, int *a, int *b, int *c) {

    for (int i = 0; i < x; i++ ) {
        c[i] = a[i] + b[i];
    }

    return c;
}


// Vectorized example
__m256 add_arrs_v(__m256 a, __m256 b) {
    __m256 arrays_added = _mm256_add_ps(a,b);
    return arrays_added;
}

int main() {
    int a[] = {1,2,3,4,5,6,7,8};
    int b[] = {1,2,3,4,5,6,7,8};

    int c[8];
    add_arrs(8, a, b, c);

    for (int i = 0; i < 8; i++){
        printf("%d \n", c[i]);
    }

    // Using vectorization
    __m256 arr1 = _mm256_set_ps(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0);
    __m256 arr2 = _mm256_set_ps(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0);
    _mm256_add_ps(arr1, arr2);

    __m256 arrays_added = add_arrs_v(arr1, arr2);
    float *results = (float *)&arrays_added;

    for (int i=0; i < 8; i++) {
        printf("%f\n", results[i]);
    }
}
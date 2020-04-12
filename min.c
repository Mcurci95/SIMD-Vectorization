#include <stdio.h>
#include <smmintrin.h>
#include <immintrin.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LEN 10


float min_naive(size_t n, float *a) {
    float min = a[0];

    for (int i=0; i < n; i++) {
        if (a[i] < min)
            min = a[i];
    }

    return min;
}


// Vectorized example
float min_v(__m256 a) {
    __m256 simd_min = a;

    simd_min = _mm_min_epi8(simd_min, _mm_extract_epi8(simd_min,simd_min,1));
    simd_min = _mm_min_epi8(simd_min, _mm_extract_epi8(simd_min,simd_min,2));
    simd_min = _mm_min_epi8(simd_min, _mm_extract_epi8(simd_min,simd_min,4));
    simd_min = _mm_min_epi8(simd_min, _mm_extract_epi8(simd_min,simd_min,8));

    return simd_min;
}

int main() {
    float arr[MAX_LEN];
    int n = 10;
    for(int i = 0; i < MAX_LEN; i++)
        arr[i] = (float) i;
    float min_value = min_naive(n, arr);
    printf("%f", min_value);

    // SIMD
    __m256 arr1 = _mm256_set_ps(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0);
    __m256 simd_min = min_v(arr1);
    
}

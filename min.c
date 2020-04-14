#include <stdio.h>
#include <smmintrin.h>
#include <immintrin.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LEN 120000


int min_naive(int n, int *a) {
    int min = a[0];

    for (int i=0; i < n; i++) {
        if (a[i] < min)
            min = a[i];
    }

    return min;
}


// Using vectorization
int min_v(int SIZE, int  *a) {
	// printf("%d", SIZE);
    __m128i simd_min_comparison;
 
    // Start with 4 offset
    __m128i simd_min = _mm_loadu_si128((__m128i *) &a[0]); 
	// int pos1 = _mm_extract_epi32(simd_min, 0);
	// int pos2 = _mm_extract_epi32(simd_min, 1);
	// int pos3 = _mm_extract_epi32(simd_min, 2);
	// int pos4 = _mm_extract_epi32(simd_min, 3);
	// printf("Extracted First: %d %d %d %d \n", pos1, pos2, pos3, pos4);
    int bitmin[4];

    for (int i = 4; i < SIZE; i += 4) {
		// printf("%d\n", i);
        simd_min_comparison = _mm_loadu_si128((__m128i *) &a[i]);
        
        __m128i simd_min = _mm_min_epi32(simd_min_comparison, simd_min);
		// pos1 = _mm_extract_epi32(simd_min, 0);
		// pos2 = _mm_extract_epi32(simd_min, 1);
		// pos3 = _mm_extract_epi32(simd_min, 2);
		// pos4 = _mm_extract_epi32(simd_min, 3);
		// printf("Extracted: %d %d %d %d \n", pos1, pos2, pos3, pos4);
		
    }
    
    _mm_storeu_si128((__m128i *)bitmin, simd_min);
	// printf("Extracted: %d %d %d %d \n", bitmin[0], bitmin[1], bitmin[2], bitmin[3]);
    return min_naive(4, bitmin);
}

int main()
{

    	int arr[MAX_LEN];
    	for (int i = 0; i < MAX_LEN; i++)
        	arr[i] = i;

	double time_spent1 = 0.0;
	double time_spent2 = 0.0;
	clock_t begin = clock();

	printf("min = %d\n", min_naive(MAX_LEN, arr));
	// printf("SIZE: %d", MAX_LEN );
	clock_t end = clock();
	time_spent1 += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time elpased is %f seconds for naive min.\n", time_spent1);

    	begin = clock();

	printf("min = %d\n", min_v(MAX_LEN, arr));

    	end = clock();
	time_spent2 += (double)(end - begin) / CLOCKS_PER_SEC;

    	printf("Time elpased is %f seconds for 128bit vectorize min\n", time_spent2);

	printf("%f X time faster.\n", time_spent1/time_spent2);
	return 0;
}
